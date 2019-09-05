//Edited by Ryan Martin

# A8: Indexing multiple movie files

Here's a quick overview 

I will likely make some tweaks and **will** add an HTLL.a library for you to use. 

[Docs!!](html/index.html) (After you download, open html/index.html in your browser)


```FileParser```:
Responsible for reading in a file, checking for errors, and parse out movies.


```Movie```:
A struct holding all the Movie info (id, title, type, genre, etc.)


```MovieIndex```:
A hashtable that indexes movies according to specified field. Basically wraps a hashtable with functionality specific to adding/removing/destroying with MovieSets. The key is the description for the document set, and the value is the document set.


```MovieReport```:
Responsible for printing out a report given a MovieIndex, to the command line or file.


```MovieSet```:
A set of Movies that are connected somehow: they have the same value for a given field. If the field is Year, all the movies in the set are made in the same year. It consists of a description and a LinkedList of Movies.

The basic tasks you need to complete:

* Modify main to accept flags on input and do the right thing.
* Modify Movie struct to hold an array of genres
* Modify MovieSet to ensure no duplicates of movies
* Bulk up tests

To do this, go through each file, and identify the "TODO" tags (An easy way to do this might be to use grep). 

While you're going through the TODO tags, you'll see some questions where we ask you what to put somewhere. Collect those, and put them (with answers) in your README.md file for this assignment. (In MovieIndex, FileParser). 

## TODOs: 

### To write code: 
* example_indexer.c:33:  // TODO: Parse command-line args to index based on the correct field (see getopt) 
* example_indexer.c:38:  // TODO: Output report to file, rather than terminal (see MovieReport.h)
* FileCrawler.c:37:  // TODO: use namelist to find all the files and put them in map.
* FileParser.c:144:  // TODO: Check that there is at least one movie 
* main.c:30:  // TODO: Read a specified row from a specified file into Movie.
* main.c:53:  // TODO: This function pretty much runs the queries. 
* main.c:75:    // TODO: What to do with the filename?
* main.c:87:      // TODO: What to do with the filename?
* Movie.c:31:  // TODO: Populate/Initialize movie. 
* Movie.c:41:  // TODO: Destroy properly
* Movie.c:95:  // TODO: Change such that genres is an array (or linkedlist), not just a string.
* Movie.h:43:  //  char *genres;  // TODO: Make this an array (or linked list) of char*s
* MovieIndex.c:185:        // TODO: What to do if there are multiple genres?
* MovieIndex.c:193:  // TODO: How do we put the movie in the index?
* MovieIndex.c:215:      // TODO: how to deal with multiple genres??
* MovieReport.c:44:  // TODO: Implement this function.
* MovieReport.c:51:  // TODO: Implement this. You might utilize OutputReport. (Optional. Change test if needed to not do this)
* test_suite_a4.cc:126:  // TODO: check the right thing for correct genre

### To answer in README: 

* FileParser.c:135:  // TODO: How big to make this hashtable? How to decide? What to think about?\

When we are concerned with the size of the hashtable, we are really just concerned with how many buckets or slots it has. Generally, a table should be an array with a length that is larger than the number of keys that will be in the hashtable. You do not want to make the length of the array too much larger than the number of keys, though, because you will be wasting space, but you also do not want to make the length of the hashtable smaller than the number of keys. If you do, you will have to create a larger table and rehash the entries when it gets full.

From my research, a good rule of of thumb is to create a hashtable with an array approximately 1.3 times larger than the number of keys. So, length = 1.3(number of keys).

* FileParser.c:154:      // TODO: What to do if there is a collision?

When a collision happens, multiple keys will map to the same integer, then elements of different keys will be stored in the same slot of the hashtable. There are many ways to solve this problem, but one way involves seperate chaining to solve collisions. This is done by creating a list of keys that map to the same value.

* main.c:95:  // TODO: Now that you have all the search results, print them out nicely.
* MovieIndex.c:50:  // TODO: How big to make this hashtable? How to decide? What to think about?

The size of the array in the hashtable should be 1.3 times the number of keys. This will allow enough space to be accomodated for all the collections, as well as accountinf for collision without using up too much space.

* MovieIndex.c:87:  // TODO: How to choose this number? What are the pros and cons of choosing the wrong number?

Choosing a wrong number that is too big  much means that you will use too much space. Whereas, choosing a number that is too small means  that you will most-likely have to re-hash entries.   

Note to grader:

All tests pass in this assignment except for the MovieIndexer.c. That's 4/5 tests. 