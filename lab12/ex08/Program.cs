using ex08.Services;
using System.ServiceModel.Syndication;
using System.Threading.Tasks.Dataflow;

namespace ex08
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            // Define RSS feed URLs
            string[] feedUrls = new string[]
            {
                "https://devblogs.microsoft.com/dotnet/feed/",
                "https://www.microsoft.com/microsoft-365/blog/feed/",
                "https://feeds.feedburner.com/TechCrunch/",
                "https://www.wired.com/feed/rss"
            };

            // Create pipeline blocks
            var fetchBlock = new TransformBlock<string, IEnumerable<SyndicationItem>>(
                url =>
                {
                    Console.WriteLine($"Fetching feed: {url}");
                    return RSSFeedService.GetFeedItems(url);
                },
                new ExecutionDataflowBlockOptions { MaxDegreeOfParallelism = 4 }
            );

            var flattenBlock = new TransformManyBlock<IEnumerable<SyndicationItem>, SyndicationItem>(
                items => items ?? Enumerable.Empty<SyndicationItem>()
            );

            var displayBlock = new ActionBlock<SyndicationItem>(
                item =>
                {
                    Console.WriteLine($"Title: {item.Title.Text}");
                }
            );

            // Link blocks
            var linkOptions = new DataflowLinkOptions { PropagateCompletion = true };
            fetchBlock.LinkTo(flattenBlock, linkOptions);
            flattenBlock.LinkTo(displayBlock, linkOptions);

            // Post URLs to fetch block
            foreach (var url in feedUrls)
            {
                await fetchBlock.SendAsync(url);
            }

            // Signal completion
            fetchBlock.Complete();

            // Wait for pipeline to complete
            await displayBlock.Completion;

            Console.WriteLine("\nAll feeds processed.");
        }
    }
}