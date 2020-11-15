#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void buildMaxHeap(int arr[], int n);
void heapify(int arr[], int n, int i);

int main(int argc, char **argv){
  int size, n, j, k = 0;
  char c;

  // Read heap size from file
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%d", &size);

  // Array of heap values
  int arr[size];

  // Find numbers of vertices. Runs in O(E) time.
  for(int i = 0; i < size; ++i){
    fscanf(fp, "%d", &n);
    arr[i] = n;
  }

  while(1){
    c = fgetc(fp);
    if(c==EOF){
      break;
    } else if(c == 'E'){
      printf("Extract Max\n");
    } else if(c == 'I'){
      c = fgetc(fp);
      fscanf(fp, "%d", &j);
      printf("Insert key %d\n", j);
    } else if(c == 'D'){
      c = fgetc(fp);
      fscanf(fp, "%d", &j);
      printf("Delete key %d\n", j);
    } else if(c == 'C') {
      c = fgetc(fp);
      fscanf(fp, "%d", &j);
      c = fgetc(fp);
      fscanf(fp, "%d", &k);
      printf("Change key at A[%d] to %d\n", j, k);
    } 
  }
  fclose(fp);

  buildMaxHeap(arr, size);
  for(int i = 0; i < size; ++i){
    printf("%d ", arr[i]);
  }
  printf("\n");
}


void buildMaxHeap(int arr[], int n){ 
  // Index of last non-leaf node 
  int startIndex = n / 2 - 1; 

  // Perform reverse level order traversal 
  // from last non-leaf node and heapify 
  // each node 
  for (int i = startIndex; i >= 0; i--) { 
    heapify(arr, n, i); 
  } 
} 

void heapify(int arr[], int n, int i){ 
  int largest = i; // Initialize largest as root 
  int l = 2 * i + 1; // left = 2*i + 1 
  int r = 2 * i + 2; // right = 2*i + 2 

  // If left child is larger than root 
  if (l < n && arr[l] > arr[largest]) 
    largest = l; 

  // If right child is larger than largest so far 
  if (r < n && arr[r] > arr[largest]) 
    largest = r; 

  // If largest is not root 
  if (largest != i) { 
    int first = arr[i];
    int second = arr[largest];
    arr[i] = second;
    arr[largest] = first;

    // Recursively heapify the affected sub-tree 
    heapify(arr, n, largest); 
  } 
} 