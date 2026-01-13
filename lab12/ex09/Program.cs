using ex09.Services;
using System.ServiceModel.Syndication;
using System.Threading.Tasks.Dataflow;

namespace ex09
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            string feedUrl = "https://www.wired.com/feed/rss";

            // Fetch feed items
            var fetchBlock = new TransformBlock<string, IEnumerable<SyndicationItem>>(
                url =>
                {
                    Console.WriteLine($"Fetching feed: {url}");
                    return RSSFeedService.GetFeedItems(url);
                }
            );

            // Flatten to individual items
            var flattenBlock = new TransformManyBlock<IEnumerable<SyndicationItem>, SyndicationItem>(
                items => items ?? Enumerable.Empty<SyndicationItem>()
            );

            // Extract categories
            var extractCategoriesBlock = new TransformManyBlock<SyndicationItem, string>(
                item =>
                {
                    return item.Categories.Select(c => c.Name);
                }
            );

            // Convert to uppercase and ensure uniqueness
            HashSet<string> uniqueCategories = new HashSet<string>();
            object lockObj = new object();

            var uppercaseBlock = new TransformBlock<string, string>(
                category =>
                {
                    return category.ToUpper();
                }
            );

            var collectBlock = new ActionBlock<string>(
                category =>
                {
                    lock (lockObj)
                    {
                        uniqueCategories.Add(category);
                    }
                }
            );

            // Link blocks
            var linkOptions = new DataflowLinkOptions { PropagateCompletion = true };
            fetchBlock.LinkTo(flattenBlock, linkOptions);
            flattenBlock.LinkTo(extractCategoriesBlock, linkOptions);
            extractCategoriesBlock.LinkTo(uppercaseBlock, linkOptions);
            uppercaseBlock.LinkTo(collectBlock, linkOptions);

            // Post feed URL
            await fetchBlock.SendAsync(feedUrl);
            fetchBlock.Complete();

            // Wait for completion
            await collectBlock.Completion;

            // Display unique categories using ActionBlock
            var displayBlock = new ActionBlock<string>(
                category =>
                {
                    Console.WriteLine(category);
                }
            );

            Console.WriteLine("\nUnique categories (uppercase):");
            foreach (var category in uniqueCategories.OrderBy(c => c))
            {
                await displayBlock.SendAsync(category);
            }

            displayBlock.Complete();
            await displayBlock.Completion;
        }
    }
}