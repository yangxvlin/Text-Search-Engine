/* * * * * * *
 * Module for functions that solve the coding tasks from assignment 1
 * 
 * created for COMP20007 Design of Algorithms - Assignment 1, 2018
 * by Matt Farrugia <matt.farrugia@unimelb.edu.au>
 */

#ifndef QUERY_H
#define QUERY_H

#include "index.h"

/*                         DO NOT CHANGE THIS FILE
 * 
 * DO NOT modify function prototypes: you must implement these functions exactly
 * DO NOT add your own function prototypes or other definitions; put additional
 * definitions in query.c instead
 *
 * We will test your assignment with an unmodified version of this file. Any
 * changes you make will be lost. This may lead to compile errors.
 */

// see Assignment Task 1: Accumulator array-based approach
void print_array_results(Index *index, int n_results, int n_documents);

// see Assignment Task 2: Multi-way merge-based approach
void print_merge_results(Index *index, int n_results);

#endif
