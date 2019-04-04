/* name: XuLin Yang, 
   student id: 904904, 
   time: 2018-3-19 21:34:21, 
   description: comp20007 assignment1 task 1 & 2 c code*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "query.h"
#include "list.h"
#include "heap.h"
#include "index.h"

#define INT_TO_FLOAT(x) (x * 1.0) /* convert int type data to float type */
#define FLOAT_TO_INT(x) ((int) x) /* convert float type data to int type */
#define IS_NULL(x) (x == NULL) /* return True is x is NULL */

#define ZERO 0.0 /* initial score for each document */

// helper function prototype

/* recursively print the minimum data set in the min heap */
static void print_result(Heap *h);

/* initialize the array with 0.0 */
static void initialize_float_array(float *arr, int n_documents);

/* traverse through document_list and sum scroe for each document */
static void traverse_document_list(float *arr, int n_documents, Index *index);

/* directly insert at end when heap is not full
   overwrite heap head with a bigger record when heap is full */
static void insert_into_heap(Heap *h, int n_results, float score, int id);

/* use min heap based priority queue to find top k scored document */
static void topk(float *arr, int n_results, int n_documents, Heap *h);

/* initialise id_heap to order docu_lists based on the list->heads' docu_id */
static void initialize_id_heap(Heap *id_heap, List **tmp, Index *index);

/* repeatedly pop a data set from id heap and sum total scores for each docu */
static void multi_way_merge_topk(Heap *id_heap, Heap *priority_queue,
                                 List **tmp, int n_results);



// see Assignment spec: 'Task 1: Array-based accumulation approach'
void print_array_results(Index *index, int n_results, int n_documents) {
	if (n_results > 0) {

		/* float array used to store score for each document */
		float score_arr[n_documents];

		/* min heap based priority queue with 'n_results' cells 
		with {key=score : item=document_id}*/
		Heap *priority_queue = new_heap(n_results);

		/* step 1 build array*/
		initialize_float_array(score_arr, n_documents);

		/* step 2 sum score for each document*/
		traverse_document_list(score_arr, n_documents, index);	

		/* step 3 topk scored document selection*/
		topk(score_arr, n_results, n_documents, priority_queue);

		/* output */
	    print_result(priority_queue);

		/* destroy malloced heap */
		free_heap(priority_queue);
	}
	return;
}

/* initialize the array with 0.0 */
static void initialize_float_array(float *arr, int n_documents) {
	int i;
	for (i = 0; i < n_documents; i++) {
		*(arr + i) = ZERO;
	}
	return;
}

/* traverse through document_list and sum scroe for each document */
static void traverse_document_list(float *arr, int n_documents, Index *index) {
	Node *tmp; /* temporary node pointer for document list */
	int i;

	/* loop every record and add score for the specific document */
	for (i = 0; i < index->num_terms; i++) {
		tmp = (index->doclists[i])->head;

		while (!IS_NULL(tmp)) {
			*(arr + ((Document*)(tmp->data))->id) +=\
				((Document*)(tmp->data))->score;
			tmp = tmp->next;
		}
	}
	return;
}

/* directly insert at end when heap is not full or
   overwrite heap head with a bigger record when heap is full else do nothing*/
static void insert_into_heap(Heap *h, int n_results, float score, int id) {
	/* score <= 0.0 document is unwanted */
	if (score) {
		/* insert first k non-0.0 document directly into priority queue */
		if (get_heap_size(h) < n_results) {
			heap_insert(h, score, id);

		/* only insert when bigger scored document found 
			compared to smallest data record in priority queue */
		} else if (score > heap_peek_key(h)) {
			heap_overwrite_head(h, score, id);
		}
	}

	return;
}

/* use min heap based priority queue to find top k scored document */
static void topk(float *arr, int n_results, int n_documents, Heap *h) {
	int i;

	/* process through all documents */
	for (i = 0; i < n_documents; i++) {
		if (arr[i]) {
			insert_into_heap(h, n_results, arr[i], i);
		}
	}
	return;
}

/* recursively print the minimum data set in the min heap */
static void print_result(Heap *h) {
	int n = get_heap_size(h);

	while (get_heap_size(h) > 0) {
		heap_remove_min(h);
	}
	print_heap(h, n);
	return;
}

// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {
	if (n_results > 0) {
		/* min heap based priority queue with size = 'n_results'
		has {key=score : item=document_id}*/
		Heap *priority_queue = new_heap(n_results);

		/* min heap based priority queue with size = 'index->max_terms'
		   cells has {key=document_id : item=document_list's index} */
		Heap *id_heap = new_heap(index->max_terms);

		/* temporary pointer used to access document lists */
		List **tmp = index->doclists;

		/* step 1 id heap built */
		initialize_id_heap(id_heap, tmp, index);

		/* step 2 repeatedly retrieve a document from id heap and
		accumulate total scores for each document */
		multi_way_merge_topk(id_heap, priority_queue, tmp, n_results);

		/* output */
		print_result(priority_queue);

		/* destroy malloced heap */
		free_heap(priority_queue);
		free_heap(id_heap);
	}
	return;
}

/* initialise id_heap to order docu_lists based on the list->heads' docu_id */
static void initialize_id_heap(Heap *id_heap, List **tmp, Index *index) {
	int i;

	/* insert list->head's index and item into id_heap if it exists */
	for (i = 0; i < index->num_terms; i++) {
		if (tmp[i]->head != NULL) {
			/* key = docu_id, item = doc_list's index */
			heap_insert(id_heap,
				INT_TO_FLOAT(((Document*)(tmp[i]->head->data))->id), i);
		}
	}
	return;
}

/* repeatedly pop a data set from id heap and sum total scores for each docu */
static void multi_way_merge_topk(Heap *id_heap, Heap *priority_queue,
                                List **tmp, int n_results) {
	int processing, pop_id;
	float processing_score = 0.0;

	/* traverse all the document id */
	while (get_heap_size(id_heap) > 0) {
		processing = FLOAT_TO_INT(heap_peek_key(id_heap));
		processing_score = 0.0;

		/* sum score for one document */
		while (get_heap_size(id_heap) &&
		        (FLOAT_TO_INT(heap_peek_key(id_heap)) == processing)) {
			pop_id = heap_remove_min(id_heap);

			processing_score += ((Document*)(tmp[pop_id]->head->data))->score;

			/* step next in doculist[] */
			if (tmp[pop_id]->head->next != NULL) {
				tmp[pop_id]->head = tmp[pop_id]->head->next;
				heap_insert(id_heap,
				    INT_TO_FLOAT(((Document*)(tmp[pop_id]->head->data))->id),
				    pop_id);
			}
		}

		/* one document's score is sum */
		insert_into_heap(priority_queue, n_results,
		                 processing_score, processing);		
	}

	return;
}

/* design of algorithm is fun */
