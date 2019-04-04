/* name: XuLin Yang, 
   student id: 904904, 
   time: 2018-3-19 21:34:21, 
   description: comp20007 assignment1 
   binary min-heap of (key=float, data=int) module c-header file */

#ifndef HEAP_H
#define HEAP_H

typedef struct data Data;
typedef struct heap Heap;

/* create a new heap with size = max_size */
Heap *new_heap(int max_size);

/* insert item at the end of heap and siftup it */
void heap_insert(Heap *h, float key, int data);

/* insert item at the start of heap and siftdown it */
void heap_overwrite_head(Heap *h, float key, int data);

/* remove and return last item in heap */
int heap_remove_min(Heap *h);

/* return last item in heap */
int heap_peek_min(Heap *h);

/* return last item's priority in heap */
float heap_peek_key(Heap *h);

/* destoroy the heap */
void free_heap(Heap *h);

/* return the currrent size used in heap */
int get_heap_size(Heap *h);

/* print data array in heap */
void print_heap(Heap *h, int n);

#endif