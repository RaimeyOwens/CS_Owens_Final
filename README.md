# CS_Owens_Final
Rize course Computer Systems. Final Project. Log File Analysis. 

# Description of project
Log file analysis is the process of auditing raw server log files to track interactions between search engine bots and a website. It is important because this process helps find technical problems and performance issues that can then be fixed. What I will actually build is a C program that counts word frequencies in text. This project benefits from systems-level optimization because performance is heavily influenced by memory allocation patterns, data structure choices, and cache efficiency. I was interested in doing this because of the tokenizing the text aspect of this project. I want to be an AI programmer in the future, and sometime with this it is important to know how to tokenize text for things like Natural Processing Languages or TF-IDF Vectorization. Last semester I worked a little bit with these things to try to create an AI chatbot for a company, so I am interested to look more into it from a system developer standpoint. 

# Focus/goal in terms of what is optimal
The specific performance problem that occurs in this process is slow processing times. This happens when it has to handle large text files containing many words. As the file increases, the program has to continue tokenizing strings, searching for words that exist, and update frequency counts. This can become inefficient, especially as the scale increases. At the software level, the problem could be the use of simple data structures (in this case, arrays used for storing word counts). When looking for frequent words, it would have to search through the list all the way through to find out if the word is unique or not. Also, frequent dynamic memory allocation for storing strings can maybe have fragmentation which might slow the execution.  At the hardware level, the performance issue can show up due to cache utilization and inefficient memory access patterns. Operations that are string-heavy and pointer-based structures could have scattered memory access. This would reduce spatial locality, thus increasing cache misses. Overall, these inefficiencies can make the program performance exponentially slower as the input size continues to scale upwards. 

Because I am looking at performance speed, the primary performance metric for this project will be total execution time. This will probably be measured in milliseconds. Ideally, the main optimization goal is to have at least two-times improvement in runtime compared to the baseline test implementation (emphasizing performance on large scales mainly). A secondary goal I can have is to reduce the number of dynamic memory allocations. We are going to have a timing function (like getTime()) to measure the execution time for each run. To make the test data more reliable, we will run it a couple of times and get the average runtime. This should hopefully make it more accurate and reduce variability. To be fair, the benchmarks will also be performed on the same dataset and have consistent conditions between the baseline and optimized versions. 

# Baseline Implementation 
The baseline implementation design for this project will read a log file line by line, split each line into individual words, and then store each word along with its frequency count. It will use a simple array for the data structure. In this array, it will contain a word string and an integer counter. For every new word encountered, the program will do a linear search to see if the word already exists (in the optimized version, it will NOT be a linear search as this is not the most optimal way to do it). If the word exists in the array, then the count is incremented, and if not a new entry in the array is created. This code will be simple, but not the most efficient way to solve this problem.

# Optimization 
In my project, I will reduce memory allocation by replacing per-word malloc calls with a preallocated memory pool. Instead of allocating a new node for every unique word, the program will reserve a large contiguous block of memory at startup. By doing this, we can reduce heap fragmentation, eliminate allocation overhead, and make the memory usage more predictive. 
I can replace the baseline linked list with a hash table implementation using a contiguous array. This would probably reduce lookup time making the time complexity change from O(n) to now O(1) on average. This will eliminate pointer chasing between scattered nodes in memory. Having all entries be stored in a single array allows for improved spatial locality. This makes the CPU cache be more able to store multiple entries per cache line which reduces cache misses during word lookups. To reduce overhead inside the main processing loop we need to minimize unnecessary function calls and keep hot-path logic inline where possible. Critical operations (like string comparison) will be simplified to reduce stack overhead. This will improve instructions throughout and reduce CPU pipeline stalls caused by excessive branching or function call overhead. Lastly, I can improve cache efficiency by ensuring that the hash table and associated data structures are stored contiguously in memory. If I do so, this would increase spatial locality, which allows for multiple entries to be loaded into a single cache line. Also, sequential probing in case of collision will be better with CPU prefetching behavior. This is because it will reduce cache miss penalties

# How to test and run files
Create a text file yes "hello world this is a performance test" | head -n 100000 > big.txt
After I edit I need to compile: gcc baseline.c -o baseline   AND     gcc -O2 optimized.c -o optimized
If I want to manually add lines I can type in text and then press ctrl d to enter all of the text

Test and check for optimization on files (like the big.txt one I created)
 ./baseline < big.txt
 ./optimized < big.txt
 *** To just run it normally you would do something like ./optimized only.

 # Expected Output Example
Enter text (press Ctrl+D when done):

Word Frequencies:
a: 100000
hello: 100000
is: 100000
test: 100000
performance: 100000
world: 100000
this: 100000

Total unique words: 7
Execution time: 0.042532 seconds