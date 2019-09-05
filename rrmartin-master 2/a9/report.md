Author: Ryan Martin


Assignment 09 Response: Multi-Threading


Which is bigger, the TypeIndex or the OffsetIndex? Why?

In this program, the OffSet Index contains 22,197 entries; whereas, the Type Index contains only 10 entries. The reason why the Offset index is so much larger is because the Offset Index queries differently than the Type Index. Essentially, the Type Index contains less entries because it uses a Linked List of movie structs in the SetOfMovies, and the OffsetIndex uses MovieSet, which basically just stores the DocIds and RowIds of where the movies are stored on the disk.  

Which will be faster to query, the OffsetIndexer or the TypeIndex? For what kinds of queries? Why?

The type Index will be faster to query because it contains less entries through its utilization of the linked list, which is contained in the hashtable.

Which will be faster to build, the TypeIndex or the OffsetIndex? Why?

The type Index will be faster to build because it contains less	\
ntries through its utilization of the linked list, which is cont\
ined in	the hashtable.

Multi-Threaded Parser Comparison:

After changing the ParseTheFiles method to ParseTheFiles_MT, the multithreaded implementation gave surprising results. In conducting this experiment, we expected the multithreaded implementation to parse the files much faster; however, the timer actually indicated that the multiple threads parsed the files slower.

The OffsetIndex took .089073 seconds to execute with the multithreader, but it took only .077155 seconds to excute without a multithreader. The TypeIndex too .024043 seconds with a multithreader and .018831 seconds without a multithreader.

Usually, in practice, multithreading is faster because all threads that are within one single process share the same heap of memory and contain their own data structures to execute. This means that the threads share the same data but have different functions, which creates a divide-and-conquer advantage because the program can delegate different tasks to different threads. Concurrency and parallelism also play a role in this, which was why we had to use mutex to implement the multi-threaded parser function.

Because we had to use mutex and because we were running off of only one CPU, our implementation of the multithread was basically trivial. Since we could not fully take advantage of using different threads, our program was actually better running serially. 