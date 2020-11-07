#Machine Problem 2

In this program you will read a file specifying a directed graph G as a list of edges. Each edge u → v is listed on one line as u v. The input file simply lists the edges in arbitrary order as pairs of vertices, with each edge on a separate line. The vertices are numbered in order from 1 to the total number of vertices. The program outputs the out-degree sequence for GSCC in increasing order.

For example for the input below:

2 1

3 2

1 3

1 5

3 4

4 5

6 7

5 6

7 4

3 11

2 8

8 9

10 8

9 10

9 4

9 7

10 11

7 11

6 11

the corresponding output is:

0 1 2 3

You should be able to implement this program to run in linear time (time proportional to the total number of vertices plus the total number of edges in the input graph).

At the top of your program, explain in a comment why your algorithm run in linear time.