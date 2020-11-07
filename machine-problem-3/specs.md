#Machine Problem 3

This program first build a MAX-HEAP A of size n.  The first line of the input line specifies the size of the heap n, followed by the n values A[1] through A[n].  For simplicity all the values are integers. The remainder of the input file consists of additional commands to perform on the heap. Each command is given on one line as follows:

E:  means extract max

I v: means insert new key v

C i v: change key at A[i] to v

D i: delete key at A[i]

 

After performing all the commands, the program then outputs the final content of the heap on one line.  The test files will be such that the final array is small enough to fit on one line with numbers separated by a single space. For example for the following input:

 

5

1

2

3

4

5

I 7

E

C 3 9

E

D 2

 

The output is:

 

5 1 2

 

All the heap operations should be implemented using the cyclic-shift idea as discussed in lectures.

Write each of the heap operations (BUILD-MAX-HEAP, INSERT, MAX-HEAPIFY, HEAP-CHANGE-KEY, and DELETE)  as a separate function. Add a small comment at the beginning

of each function to explain how it works. HEAP-CHANGE-KEY (A,i,key) changes A[i] to key and then restore heap property : either have to use MAX-HEAPIFY or

HEAP-INCREASEE-KEY.  DELETE(A,i) deletes the value at A[i] from heap. It should be implemented  as follows:

1. set key = A[n], where n is size of heap.

2. n = n-1;

3. call HEAP-CHANGE-KEY (A,i,key)