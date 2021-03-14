#include <stddef.h>

#ifndef LIST_INCLUDED
#define LIST_INCLUDED

#define T List_T

/*
 * The typedef define the type 'List_T' as an opaque pointer to a 'struct
 * List_T'. This definition is legal because of the existence of separate
 * namespaces for structure, union and enumeration tags and variables, functions
 * and type names.
 */
typedef struct T *T;

// the Deallocator function will be used to free
// any field of the element,
// the Deallocator function SHOULD NEVER free the element itself
typedef void (*Deallocator)(void *);

// the Comparator function compares two different
// elements using custom logic,
// returning -1 if the first is lower than the second,
// returning +1 if the first is greater than the second,
// returning 0 otherwise
typedef int (*Comparator)(void *, void *);

// the Duplicator function will be used to clone
// the elements when is necessary,
// for example inside the filter function
// to create a completely separated filtered list,
// it must return entities having the same type of the originary list
typedef void *(*Duplicator)(void *);

// a wild fold appears
typedef void *(*Reducer)(void *, void *);

// the Projection function transform an element
// into another without restrictions
typedef void *(*Projection)(void *);

// the Predicate function checks if an element satisfies
// a predicate,
// returning +1 if yes,
// returning 0 otherwise
typedef int (*Predicate)(void *);

// used to do something to each entity
// the ForEachCallback function SHOULD NEVER free the element itself
typedef void (*ForEachCallback)(void *);

// create a new generic list
extern T List_create(Comparator, Duplicator, Deallocator);

// destroy a list
extern void List_free(T *, int);

// get the comparator
Comparator List_getComparator(T);

// get the duplicator
Duplicator List_getDuplicator(T);

// get the deallocator
Deallocator List_getDeallocator(T);

// insert a non NULL element into the head of the list
extern void List_insertHead(T, void *);

// insert a non NULL element into the tail of the list
extern void List_insertTail(T, void *);

// insert a non NULL element respecting the chosen order
// 0 DESCENDING - 1 ASCENDING
extern void List_insertOrdered(T, void *, int);

// return the element from the head of the list,
// without removing it
extern void *List_pickHead(T);

// return the element from the tail of the list,
// without removing it
extern void *List_pickTail(T);

// find an element and return it without removing
// the element from the list
extern void *List_findPick(T, Predicate);

// remove and return an element from the head of the list,
// without freeing it
extern void *List_extractHead(T);

// remove and return element from the tail of the list,
// without freeing it
extern void *List_extractTail(T);

// find an element and return it,
// but the function removes the element from the list
extern void *List_findExtract(T, Predicate);

// remove an element from the head of the list,
// free the element
extern void List_deleteHead(T);

// remove an element from the tail of the list
// free the element
extern void List_deleteTail(T);

// find an element, remove it from the list,
// free the element
extern void List_findDelete(T, Predicate);

// check if an element satisfies a predicate
extern int List_any(T, Predicate);

// check if all elements satisfy a predicate
extern int List_all(T, Predicate);

// get the number of elements that are inside the list
extern size_t List_length(T);

// reverse the list
extern void List_reverse(T);

void *List_reduce(T, Reducer, void *);

T List_map(T, Projection, Comparator, Duplicator, Deallocator);

T List_filter(T, Predicate, int);

void List_forEach(T, ForEachCallback);

void List_forEach_right(T, ForEachCallback);

#undef T
#endif