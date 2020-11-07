/*
  The first while loop in the program runs in O(E) time, reading the input file and counting finding the max vertex, aka the number of vertices.
  
  The second while loop also runs in O(E) time and reads the file again to build an unordered adjacency list. 

  The three for loops that run after the second while loop are implementing Counting Sort. The first and third loops run in O(V) time, but
  the second loop appears to run in O(V^2). I was having difficulty coming up with a way to insert vertices into the adjacency list in ascending order,
  and I saw that counting sort ran in linear time. However, I believe that it is only linear for 1 dimensional arrays, and a two dimensional array scales 
  up the complexity. 

  The last for loop that prints the adjacency list should run in O(V) time.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int numVertices = 0;
  int u = 0;
  int v = 0;

  FILE *fp;
  fp = fopen(argv[1], "r");

  // Find numbers of vertices. Runs in O(E) time.
  while(fscanf(fp, "%d %d", &u, &v) == 2){
    if(u > numVertices){
      numVertices = u;
    } 
    if(v > numVertices){
      numVertices = v;
    }
  }
  fclose(fp);
  fp = NULL;

  // Builds unordered adjacency list and runs while loop in O(E) time. 
  // The unordered adjacency list will store the number of adjacent vertices in index 0.
  int ul[numVertices][numVertices];

  memset(ul, 0, sizeof(ul));

  fp = fopen(argv[1], "r");
  while(fscanf(fp, "%d %d", &u, &v) == 2){
    ul[u-1][ul[u-1][0]+1] = v;
    ++ul[u-1][0];
    ul[v-1][ul[v-1][0]+1] = u;
    ++ul[v-1][0];
  }
  fclose(fp);
  fp = NULL;

  // Sorts list using Counting Sort
  int count[numVertices][numVertices + 1];
  int finalList[numVertices][numVertices];

  memset(count, 0, sizeof(count));

  for(int i = 0; i < numVertices; ++i){ // O(V))
    for(int n = 1; n <= ul[i][0]; ++n){
      count[i][ul[i][n]] = 1;
    }
  }

  for(int i = 0; i < numVertices; ++i){ // O(V^2)
    for(int n = 1; n <= numVertices; ++n){
      count[i][n] += count[i][n-1];
    }
  }

  for(int i = 0; i < numVertices; ++i){ // O(V)
    for(int n = 0; n < ul[i][0]; ++n){
      finalList[i][count[i][ul[i][n+1]] - 1] =  ul[i][n+1];
    }
  }

  // Prints adjacency list and runs in O(V) time
  for(int i = 0; i < numVertices; ++i){
    for(int n = 0; n < ul[i][0]; ++n){
      printf("%d ", finalList[i][n]);
    }
    printf("\n");
  }

  return 0;
}