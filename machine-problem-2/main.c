/*
  To explain the run-time of my program, I'll break it down into stages and give the time complexity of each stage.

  1. Reading the file to find number of vertices = O(E)
  2. Creating and filling graph = O(V + E)
  3. First DFS = O(V + E)
  4. Creating transpose graph = O(V + E)
  5. Creating utility graph = O(V + E)
  6. Second DFS = O(V + E)
  7. For loop that builds out-degree array = O(V + E)
  8. Sorting out-degree array with counting sort = O(V)
  9. Freeing all memory for all graphs = O(V + E)

  Therefore, the highest time complexity of any operation in the program is O(V + E).
  So the time complexity is O(V + E).
  I apologize for some code at the end that's not the most readable (Finding out-degrees and second DFS). I got a little lazy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdjListNode { 
  int dest; 
  struct AdjListNode* next; 
}; 

struct AdjList { 
  struct AdjListNode *head;  
}; 

struct Graph { 
  int *visited;
  int *finishTime;
  struct AdjList *vertices; 
}; 

void printGraph(struct AdjList *vertices, int numVertices);
struct AdjListNode *newAdjListNode(int num);
void DFS(struct Graph *graph, int vertex);
void findGSCC(struct Graph *graph, struct Graph *transposeGraph, struct Graph *GSCC, int vertex);
struct Graph *createGraph(int numVertices);
struct Graph *getTranspose(struct Graph *graph, int numVertices);
void freeGraph(struct Graph **graph, int numVertices);

int main(int argc, char **argv) {
  int numVertices, u, v, currentComponent = 0;

  FILE *fp = fopen(argv[1], "r");
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
  
  // Create an array of adjacency lists
  struct Graph *graph = createGraph(numVertices);

  // Fill graph with the input file
  fp = fopen(argv[1], "r");
  while(fscanf(fp, "%d %d", &u, &v) == 2){
    struct AdjListNode *newNode = newAdjListNode(v);
    newNode->next = graph->vertices[u-1].head;
    graph->vertices[u-1].head = newNode;
  }
  fclose(fp);
  fp = NULL;
  
  // First run of DFS will find the finishing times for each vertex
  for(int i = 1; i <= numVertices; ++i){
    if(graph->visited[i - 1] == 0){
      DFS(graph, i);
    }
  }
  
  // Creates the transpose graph of the above graph
  struct Graph *transposeGraph = getTranspose(graph, numVertices);
  graph->finishTime[0] += 1;

  // This graph actually serves no purpose other than utilizing the arrays it contains
  struct Graph *GSCC = createGraph(numVertices);
  GSCC->finishTime[0] = 1;

  // Second run of DFS will go through the transpose graph to find SCCs as well as setup some arrays that will help find out degrees of those SCCs.
  while(graph->finishTime[0] <= numVertices){
    findGSCC(graph, transposeGraph, GSCC, graph->finishTime[graph->finishTime[0]]);
    ++GSCC->finishTime[0];
  }

  // unsortedAnswer array will contain the out-degrees of all of the SCCs in no particular order.
  int numComponents = GSCC->finishTime[0] - 1;
  GSCC->finishTime[0] = 0;
  int unsortedAnswer[numComponents];
  memset(unsortedAnswer, 0, sizeof(unsortedAnswer));

  // Goes through vertices of original graph and finds out-degrees of all SCCs, storing them in the unsortedAnswer array.
  for(int i = 0; i < numVertices; ++i){
    currentComponent = GSCC->visited[i];
    struct AdjListNode *temp = graph->vertices[i].head;
    while(temp != NULL){
      int adjComponent = GSCC->visited[temp->dest - 1];
      if(GSCC->finishTime[adjComponent] != currentComponent && adjComponent != currentComponent){
        ++unsortedAnswer[currentComponent - 1];
        GSCC->finishTime[adjComponent] = currentComponent;
      }
      temp = temp->next;
    }
  }

  // Uses counting-sort to sort the array of out-degrees in O(V) time.
  int countingSort[numVertices];
  memset(countingSort, 0, sizeof(countingSort));

  for(int i = 0; i < numComponents; ++i){
    countingSort[unsortedAnswer[i]] += 1;
  }

  for(int i = 0; i < numVertices; ++i){
    countingSort[i + 1] = countingSort[i] + countingSort[i + 1];
  }

  int sortedAnswer[numComponents];
  memset(sortedAnswer, 0, sizeof(sortedAnswer));

  for(int i = 0; i < numComponents; ++i){
    sortedAnswer[countingSort[unsortedAnswer[i]] - 1] = unsortedAnswer[i];
  }

  // Prints out the sorted array of out-degrees for all SCCs.
  for(int i = 0; i < numComponents; ++i){
    printf("%d ", sortedAnswer[i]);
  }
  printf("\n");

  // Frees all allocated memory
  freeGraph(&graph, numVertices);
  freeGraph(&transposeGraph, numVertices);
  freeGraph(&GSCC, numComponents);
}

// Print all vertices and their adjacent vertices
void printGraph(struct AdjList *vertices, int numVertices) {
  for(int i = 0; i < numVertices; ++i) {
    struct AdjListNode *iterator = vertices[i].head;
    if(iterator != NULL){
      printf("Vertex %d: ", i+1);
      while(iterator != NULL){
        printf("%d ", iterator->dest);
        iterator = iterator->next;
      }
      printf("\n");
    } else {
      printf("Vertex %d:\n", i+1);
    }
  }
  printf("\n");
}

// Returns a pointer to a new adjacency list node with the passed in integer 
struct AdjListNode *newAdjListNode(int num) { 
  struct AdjListNode *newNode = malloc(sizeof(struct AdjListNode)); 
  newNode->dest = num; 
  newNode->next = NULL; 
  return newNode; 
} 

// First DFS. Runs in O(V + E) time.
void DFS(struct Graph *graph, int vertex) {
  struct AdjListNode *adjList = graph->vertices[vertex-1].head;
  struct AdjListNode *temp = adjList;

  graph->visited[vertex-1] = 1;

  while (temp != NULL) {
    int adjVertex = temp->dest;

    if (graph->visited[adjVertex - 1] == 0) {
      DFS(graph, adjVertex);
    }
    temp = temp->next;
  }
  graph->finishTime[graph->finishTime[0]] = vertex;
  graph->finishTime[0] -= 1;
}

// Creates a new graph in O(E) time.
struct Graph *createGraph(int numVertices){
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->vertices = malloc(numVertices * sizeof(struct AdjList)); 
  graph->visited = malloc(numVertices * sizeof(int));
  graph->finishTime = malloc((numVertices + 1) * sizeof(int));

  // Set head pointer to NULL
  for (int i = 0; i < numVertices; ++i) {
    graph->vertices[i].head = NULL; 
    graph->visited[i] = 0;
    graph->finishTime[i] = 0;
  } 
  graph->finishTime[numVertices] = 0; 
  graph->finishTime[0] = numVertices;

  return graph;
}

// Creates and returns the transpose graph of the passed in graph. Runs in O(E) time.
struct Graph *getTranspose(struct Graph *graph, int numVertices){
  struct Graph *transposeGraph = createGraph(numVertices);
  struct AdjListNode *temp = NULL;
  for(int i = 0; i < numVertices; ++i){
    temp = graph->vertices[i].head;
    while(temp != NULL){
      struct AdjListNode *newNode = newAdjListNode(i + 1);
      newNode->next = transposeGraph->vertices[temp->dest - 1].head;
      transposeGraph->vertices[temp->dest - 1].head = newNode;
      temp = temp->next;
    }
  }
  return transposeGraph;
}  

// Second DFS. Runs in O(V + E) time. Takes in the graph to find GSCC from, its transpose graph, and the vertex to start from.
void findGSCC(struct Graph *graph, struct Graph *transposeGraph, struct Graph *GSCC, int vertex) {
  struct AdjListNode *adjList = transposeGraph->vertices[vertex-1].head;
  struct AdjListNode *temp = adjList;

  transposeGraph->visited[vertex-1] = 1;
  graph->finishTime[graph->finishTime[0]] = 0;
  graph->finishTime[0] += 1;

  GSCC->visited[vertex-1] = GSCC->finishTime[0];

  while (temp != NULL) {
    int adjVertex = temp->dest;

    if (transposeGraph->visited[adjVertex - 1] == 0) {
      findGSCC(graph, transposeGraph, GSCC, adjVertex);
    }
    temp = temp->next;
  }
}

// Free all of the allocated memory in a graph and set graph pointer to null.
void freeGraph(struct Graph **graph, int numVertices){
  free((*graph)->visited);
  free((*graph)->finishTime);
  struct AdjListNode* temp;

  for(int i = 0; i < numVertices; ++i){
    while((*graph)->vertices[i].head != NULL){
      temp = (*graph)->vertices[i].head;
      (*graph)->vertices[i].head = (*graph)->vertices[i].head->next;
      free(temp);
    }
  }

  free(*graph);
  *graph = NULL;
}