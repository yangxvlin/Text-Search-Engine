/* name: XuLin Yang, 
   student id: 904904, 
   time: 2018-3-19 21:34:21, 
   description: comp20007 assignment1 
                binary min-heap of (key=float, data=int) module c code*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "heap.h"
#include "index.h"

#define LCHILD(x) (2 * x + 1)
#define RCHILD(x) (LCHILD(x) + 1)
#define PARENT(x) ((x - 1) / 2)

struct data{
    float priority; /* priority of item in min-heap */
    int item; /* item to store data value we want */
};

struct heap {
	Data *data; /* array of cells of min-heap */
    int max_size; /* max number of cells can be stored in min-heap */
    int cur_size; /* current size of min-heap being used */
};

// helper function prototype

/* swap two Data type item */
static void swap(Data *a, Data *b);

/* compare two float number 1:a<b 0:a==b, -1:a>b */
static int cmp(float a, float b);

/* bubble an item up in the heap */
static void siftup(Heap *h, int i);

/* bubble an item down in the heap */
static void siftdown(Heap *h, int i);

/* find smaller children of a parent return 0 if no childs*/
static int min_child(Heap *h, int i);

/* create a new heap with size = max_size */
Heap *new_heap(int max_size) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    assert(heap);

    heap->max_size = max_size;
    heap->cur_size = 0;

    heap->data = (Data*)malloc(sizeof(Data) * max_size);
    assert(heap->data);
    return heap;
}

/* insert item at the end of heap and siftup it */
void heap_insert(Heap *h, float key, int data) {
    assert(h!=NULL);
    assert(h->cur_size < h->max_size);
    
    h->data[h->cur_size].priority = key;
    h->data[h->cur_size].item = data;
    h->cur_size ++;

    siftup(h, h->cur_size-1);
    return;
}

/* insert item at the start of heap and siftdown it */
void heap_overwrite_head(Heap *h, float key, int data) {
    assert(h!=NULL);

    /* this simplify the operation remove head of min-heap then insert at start
       which contains siftdown+siftup to only insert at start then siftdown */
    h->data[0].priority = key;
    h->data[0].item = data;

    siftdown(h, 0);
    return;
}

/* remove and return last item in heap */
int heap_remove_min(Heap *h) {
    assert(h!=NULL);
    assert(h->cur_size>0);

    int res = h->data[0].item;

    /* swap first and last item */
    swap(&(h->data[0]), &(h->data[h->cur_size - 1]));
    h->cur_size -= 1;

    siftdown(h, 0);

    return res;
}

/* return last item in heap */
int heap_peek_min(Heap *h) {
    assert(h!=NULL);
    assert(h->cur_size>0);
    return h->data[0].item;
}

/* return last item's priority in heap */
float heap_peek_key(Heap *h) {
    assert(get_heap_size(h));
    return h->data[0].priority;
}

/* destoroy the heap */
void free_heap(Heap *h) {
    assert(h!=NULL);

    free(h->data);
    h->data = NULL;
    free(h);
    h = NULL;
    return;
}

/* bubble an item down in the heap */
static void siftdown(Heap *h, int i) {
    assert(h!=NULL);
    int child = min_child(h, i);

    /* keep moving down */
    while (child && (cmp(h->data[i].priority, h->data[child].priority) == 1)) {
        swap(&(h->data[i]), &(h->data[child]));
        i = child;
        child = min_child(h, i);
    }
	
	return;
}

/* find smaller children of a parent return 0 if no childs*/
static int min_child(Heap *h, int i) {
    assert(h!=NULL);

	if (LCHILD(i) >= h->cur_size) {
		/* no children */
		return 0;
	} else if ((RCHILD(i) >= h->cur_size) ||
               (h->data[LCHILD(i)].priority < h->data[RCHILD(i)].priority)) {
		/* only has left child or left child is smallest child */
		return LCHILD(i);
	} else {
		/* right child exists and is smallest child */
		return RCHILD(i);
	}
}

/* bubble an item up in the heap */
static void siftup(Heap *h, int i) {
    assert(h!=NULL);

    /* keep moving up */
    while ((cmp(h->data[PARENT(i)].priority, h->data[i].priority) == 1)) {
        swap(&(h->data[i]), &(h->data[PARENT(i)]));
        i = PARENT(i);
    }
}

/* swap two Data type item */
static void swap(Data *a, Data *b) {
    assert(a!=NULL && b!=NULL);
    Data tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

/* compare two float number 1:a<b 0:a==b, -1:a>b */
static int cmp(float a, float b) {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}

/* return the currrent size used in heap */
int get_heap_size(Heap *h) {
    return h->cur_size;
}

/* print data array in heap */
void print_heap(Heap *h, int n) {
	assert(h != NULL);

	int i;
	for (i = 0; i < n; i++) {
		printf("%6d %.6f\n", h->data[i].item, h->data[i].priority);
	}
    return;
}

/* design of algorithm is fun */