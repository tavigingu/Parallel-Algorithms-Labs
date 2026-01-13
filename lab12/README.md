# Lab 12 - Task.Factory.StartNew and System.Threading.Tasks.Dataflow

## Exercise 1 - Task.Factory.StartNew

Analyzed Task.Factory.StartNew with TaskCreationOptions.AttachedToParent.

**Output:**
```
Parent task has finished!
Child task has finished!
Main thread exiting...
```

**Key Points:**
- `TaskCreationOptions.AttachedToParent` ensures child task completes before parent is considered complete
- `TaskCreationOptions.DenyChildAttach` prevents child tasks from attaching to parent
- `Task.Run()` uses TaskScheduler.Default, while `Task.Factory.StartNew()` allows custom TaskScheduler

## Exercise 2 - Parallel Graph Traversal

Implemented parallel social network graph processing using dynamic task creation.

**Output (sample):**
```
Processing [Emma Johnson] 1/7
Processing [Emma Johnson] 2/7
Processing [Emma Johnson] 3/7
...
Processing [William Thompson] 1/9
Processing [Benjamin Foster] 1/6
Processing [Ava Turner] 1/5
...
```

## Exercise 3 - Parallel Directory Analysis

Implemented parallel analysis of files and directories.

**Usage:**
```bash
dotnet run <directory_path>
```

**Features:**
- Counts files and folders recursively
- Calculates total file size
- Finds last written file with timestamp
- Uses parallel task creation for subdirectories

## Exercise 4 - Buffering Blocks

### BufferBlock<T>
- Used `TryReceive()` to safely consume all items
- Calling `Complete()` signals no more items will be added

**Output:**
```
Received: 0
Received: 1
Received: 2
...
Received: 9
```

### BroadcastBlock<T>
- Second `Post()` overwrites the previous value
- All receivers get the same (most recent) value

**Output:**
```
Battery sufficiently charged!
Battery sufficiently charged!
...
```

### WriteOnceBlock<T>
- Only accepts first value
- Subsequent `SendAsync()` calls are ignored
- All `ReceiveAsync()` calls return the same first value

**Output:**
```
5
5
5
```

## Exercise 5 - Execution Blocks

### ActionBlock<TInput>
- Performs actions on input without returning output
- Perfect for side effects (logging, printing, etc.)

### TransformBlock<TInput, TOutput>
- Transforms input to output (e.g., ToUpper())

**Output:**
```
ONE
TWO
THREE
...
TWENTY
```

### TransformManyBlock<TInput, TOutput>
- One input produces multiple outputs
- Modified to handle negative numbers using `Math.Abs()`

**Output:**
```
1 2 3 4 5 6 
0 
1 0 0 2 0 
1 2 3 
1 2 3 4
```

## Exercise 6 - Grouping Blocks

### BatchBlock<T>
Groups items into batches of specified size.

**Output:**
```
Group 1: 
        Emma Johnson
        William Thompson
        Mia Taylor
Group 2: 
        Liam Adams
        Charlotte Lewis
        Noah Brooks
...
```

### JoinBlock<T1, T2>
Pairs items from two sources.

**Output:**
```
Toyota Camry: 25000$
Ford Mustang: 35000$
Honda Accord: 27000$
...
```

### BatchedJoinBlock<T1, T2>
Creates batches of paired items and finds cheapest car in each batch.

**Output:**
```
Batch 1:
  Toyota Camry: 25000$
  Cheapest car in batch: Toyota Camry - 25000$
...
```

## Exercise 7 - Dataflow Pipeline

Implemented resource crafting system with Wood, Stone, and Iron.

**Key Points:**
- Setting `Greedy = false` in JoinBlock makes it non-greedy
- Non-greedy blocks wait for all inputs before consuming
- Prevents deadlocks in complex pipelines
- More efficient resource usage

## Exercise 8 - RSS Feed Pipeline

Implemented parallel RSS feed processing using Dataflow blocks:
- `TransformBlock` fetches feeds in parallel (MaxDegreeOfParallelism = 4)
- `TransformManyBlock` flattens items
- `ActionBlock` displays titles
- `PropagateCompletion = true` cascades completion signal

**Features:**
- Parallel fetching of multiple feeds
- Automatic flattening of results
- Clean pipeline architecture

## Exercise 9 - RSS Categories Extraction

Implemented category extraction with unique uppercase values:
- Fetches RSS feed
- Extracts all categories from posts
- Converts to uppercase
- Ensures uniqueness with HashSet
- Displays sorted results

**Pipeline:**
```
FetchBlock -> FlattenBlock -> ExtractCategoriesBlock -> UppercaseBlock -> CollectBlock -> DisplayBlock
```

**Features:**
- Each category appears only once
- All names in uppercase
- Sorted alphabetically
- Thread-safe collection with lock
