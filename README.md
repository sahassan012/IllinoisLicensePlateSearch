# Illinois License Plate Search
## About
This program uses hashing to efficiently process fines against cars with specialized Illinois license plates. It uses an implementation of a hashtable data structure and a hash function to yield O(1) retrieval of total fines associated with a given specialized plate. 

## How it works
User is prompted to enter a hash table size which the hashing algorithm uses to build the hash table. The user also enters a .txt filename parse through data (license plates and each fine).

#### Input File
The input is a text file that contains N > 0 where N is a multiple of 2: a ticket fine and then a license plate. 
Here is an example:
```console
20
A 1
35
B 99
100
ZZZZZ 1
80
A 1
250
ABCDEF 3
75
007
99
A 1234
```

The first two lines mean that the owner of license plate "A 1" received a fine of $20.

#### Output File
The program will output a file that contains the license plates in alphabetical order with one line for each valid license plate obtained from the input file. The number of total fines associated with the license plate is followed.
```console
Here is an example:
"007" $75
"A 1" $100
"ABCDEF 3" $250
"B 99" $35
"ZZZZZ 1" $100
```

Once program is run, it starts by prompting user for two values: hashtable size and filename. 
For example:
```console
$ Enter hastable size> 150000
$ Enter base filename> tickets1
```
The input file is base filename with ".txt" appended.
The output file is base filename with "-output.txt" appended.

Once this is entered, the program will read from the input file, sort, and store into the hashtable.
```console
Reading 'tickets1.txt'...
Sorting...
Writing 'tickets1-output.txt'...
```
Finally, it will display some "Hashing Stats" that will help identify the statistics of the hashing algorithm.
```console
**Hashing Stats**
Probes: 6
Stores: 6
Elements: 5
```
## How to run(from command-line)
