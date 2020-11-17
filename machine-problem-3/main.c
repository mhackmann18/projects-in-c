#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void swap(int arr[], int index1, int index2);
void printHeap(int arr[]);
void insert(int heap[], int val);
int *buildMaxHeap(int arr[], int size);
void maxHeapify(int arr[], int index);
void heapChangeKey(int heap[], int index, int val);
void delete(int heap[], int index);

int main(int argc, char **argv){
  int size, n, j, k = 0;
  char c;

  // Read heap size from file
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%d", &size);
  // Get all of the node values from the input and store them in an array
  int arr[size];
  for(int i = 0; i < size; ++i){
    fscanf(fp, "%d", &n);
    arr[i] = n;
  }

  // Build a max heap from the array of node values
  int *heap = buildMaxHeap(arr, size);

  while(1){
    c = fgetc(fp);
    if(c==EOF){
      break;
    } else if(c == 'E'){
      delete(heap, 1);
    } else if(c == 'I'){
      c = fgetc(fp);
      fscanf(fp, "%d", &j);
      insert(heap, j);
    } else if(c == 'D'){
      c = fgetc(fp);
      fscanf(fp, "%d", &j);
      delete(heap, j);
    } else if(c == 'C') {
      c = fgetc(fp);
      fscanf(fp, "%d", &j);
      c = fgetc(fp);
      fscanf(fp, "%d", &k);
      heapChangeKey(heap, j, k);
    } 
  }
  fclose(fp);
  
  printHeap(heap);
}

void delete(int heap[], int index){
  int lastNode = heap[heap[0]];
  heap[0] -= 1;
  heapChangeKey(heap, index, lastNode);
}

void heapChangeKey(int heap[], int index, int val){
  heap[index] = val;
  maxHeapify(heap, index);
}

void maxHeapify(int heap[], int index){
  int rightIndex = 2 * index + 1;
  int leftIndex = 2 * index;
  // if both child nodes exist
  if(rightIndex <= heap[0] && leftIndex <= heap[0]){
    if(heap[rightIndex] > heap[index] || heap[leftIndex] > heap[index]){
      if(heap[rightIndex] >= heap[leftIndex]){
        swap(heap, index, rightIndex);
        maxHeapify(heap, rightIndex);
      } else {
        swap(heap, index, leftIndex);
        maxHeapify(heap, leftIndex);
      }
    }
  // if only the left child node exists
  } else if(leftIndex <= heap[0]){
    if(heap[leftIndex] > heap[index]){
      swap(heap, leftIndex, index);
      maxHeapify(heap, leftIndex);
    }
  }
  if(index != 1){
    maxHeapify(heap, index - 1);
  }
}

// Takes an array of integers and returns a max heap with each integer as a key
int *buildMaxHeap(int arr[], int size){
  static int heap[1001];
  heap[0] = 0;

  for(int i = 0; i < size; ++i){
    heap[i+1] = arr[i];
    heap[0] += 1;
  }

  maxHeapify(heap, size);

  return heap;
}

// Inserts a new node with the passed in value into the heap
void insert(int heap[], int val){
  // Update heap size
  heap[0] += 1;

  int i = heap[0];

  // Add new node with value to end of heap
  heap[i] = val;

  // If the element being inserted isn't the only element in the heap
  if(i != 1){
    // Get the parent node of the new node
    int parent = i / 2;

    // Keep moving the new node up the heap until it's in its correct position or it's at the top of the heap
    while(heap[i] > heap[parent] && i != 1){
      swap(heap, i, parent);
      i = parent;
      parent = i / 2;
    }
  } 
}

// Prints out the values of an array
void printHeap(int arr[]){
  for(int i = 1; i <= arr[0]; ++i){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// Takes in an array and the indeces of two nodes to be swapped, and swaps their positions.
void swap(int arr[], int index1, int index2){
  int newNode1Val = arr[index2];
  int newNode2Val = arr[index1];

  arr[index1] = newNode1Val;
  arr[index2] = newNode2Val;

  //printf("Swapped %d and %d\n", arr[index2], arr[index1]);
}