#Machine Problem 1

In this program you will read a file specifying an undirected graph as a list of edges and output the same graph as an adjacency list such that the list of neighbors of each vertex is in increasing order. The input file simply lists the edges in arbitrary order as pairs of vertices, with each edge on a separate line.  The vertices are numbered in order from 1 to the total number of vertices. For example the input of the complete graph on 4 vertices may look like:

1 2

2 3

3 1

4 1

2 4

4 3

and the corresponding output lists is:

2 3 4

1 3 4

1 2 4

1 2 3

The first line in the output lists the neighbors of vertex 1, the second line lists the neighbors of vertex 2, and so on.

For this and all future programs,  you will submit your program as ONE C file uploaded to Canvas.

You should be able to implement this program to run in linear time (time proportional to the total number of vertices plus the total number of edges in the graph. HINT: You do not have to use a sorting algorithm to sort vertices in increasing order! Include in a comment at the top of you program a discussion of how efficient your algorithm is.