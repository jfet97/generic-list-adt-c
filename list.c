#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"
#include "macroj.h"

#define T List_T

struct Node
{
    void *element;
    struct Node *next;
    struct Node *prev;
} Node;

struct T
{
    struct Node *head;
    struct Node *tail;
    size_t length;
    Comparator comparator;
    Duplicator duplicator;
    Deallocator deallocator;
} ListEntity;

// -------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// CREATE OR DELETE A NODE

static struct Node *Node_create(void *element, struct Node *next, struct Node *prev)
{
    struct Node *newNode = malloc(sizeof(*newNode));

    CHECK_POINTER_RETURN_NULL(newNode);

    newNode->element = element;
    newNode->next = next;
    newNode->prev = prev;

    return newNode;
}

static void Node_free(struct Node **nodePtr, int freeElement)
{
    CHECK_POINTER_RETURN_VOID(*nodePtr);

    if (freeElement == 1)
    {
        free((*nodePtr)->element);
    }
    free(*nodePtr);
    *nodePtr = NULL;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// CREATE / DELETE A LIST

static int defaultComparator(void *x, void *y)
{
    return x == y;
}

static void *defaultDuplicator(void *x)
{
    return x;
}

T List_create(Comparator c, Duplicator du, Deallocator de)
{
    T newList = malloc(sizeof(*newList));

    CHECK_POINTER_RETURN_NULL(newList);

    newList->length = 0;
    newList->head = NULL;
    newList->tail = NULL;
    newList->comparator = c ? c : defaultComparator;
    newList->duplicator = du ? du : defaultDuplicator;
    newList->deallocator = de;

    return newList;
}

static void List__free(struct Node **nodePtr, Deallocator d, int freeElement)
{
    IF_NOT_NULL(
        *nodePtr,
        List__free(&(*nodePtr)->next, d, freeElement);
        if (freeElement == 1) {
            IF_NOT_NULL(d, d((*nodePtr)->element););
        });
    Node_free(nodePtr, freeElement);
}

void List_free(T *listPtr, int freeElement)
{
    CHECK_POINTER_RETURN_VOID(listPtr);
    CHECK_POINTER_RETURN_VOID(*listPtr);

    if ((*listPtr)->length != 0)
    {
        List__free(&(*listPtr)->head, (*listPtr)->deallocator, freeElement);
    }

    free(*listPtr);
    *listPtr = NULL;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// RETRIEVE COMPARATOR / DEALLOCATOR

Comparator List_getComparator(T list)
{
    return list->comparator;
}

Duplicator List_getDuplicator(T list)
{
    return list->duplicator;
}

Deallocator List_getDeallocator(T list)
{
    return list->deallocator;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// INSERT REPLACING THE HEAD / TAIL

void List_insertHead(T list, void *element)
{ // O(1)

    CHECK_POINTER_RETURN_VOID(list);
    CHECK_POINTER_RETURN_VOID(element);

    struct Node *newNode = Node_create(element, list->head, NULL);

    CHECK_POINTER_RETURN_VOID(newNode);

    size_t listLength = List_length(list);

    if (listLength == 0)
    {
        list->tail = newNode;
    }
    else
    {
        list->head->prev = newNode;
    }

    list->head = newNode;
    list->length++;
}

void List_insertTail(T list, void *element)
{ // O(1)

    CHECK_POINTER_RETURN_VOID(list);
    CHECK_POINTER_RETURN_VOID(element);

    struct Node *newNode = Node_create(element, NULL, list->tail);

    CHECK_POINTER_RETURN_VOID(newNode);

    if (list->tail != NULL)
    {
        // list->tail == NULL <=> list.length == 0
        list->tail->next = newNode;
    }
    else
    {
        list->head = newNode;
    }

    list->tail = newNode;
    list->length++;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// INSERT MAINTAINING AN ORDER

static void List__insertOrdered(struct Node **nodePtr, void *element, Comparator c, int order)
{
    void *currentElement = (*nodePtr)->next->element;

    int compareResult = c(currentElement, element);

    int shouldIInsertBeforeCurrentElement = (compareResult >= 0 && order == 1) || (compareResult < 0 && order == 0);

    if (shouldIInsertBeforeCurrentElement)
    {
        struct Node *newNode = Node_create(element, (*nodePtr)->next, *nodePtr);
        CHECK_POINTER_RETURN_VOID(newNode);
        (*nodePtr)->next->prev = newNode;
        (*nodePtr)->next = newNode;
    }
    else
    {
        List__insertOrdered(&(*nodePtr)->next, element, c, order);
    }
}

void List_insertOrdered(T list, void *element, int order)
{
    CHECK_POINTER_RETURN_VOID(list);
    CHECK_POINTER_RETURN_VOID(element);

    Comparator c = list->comparator;

    size_t listLength = List_length(list);
    if (listLength == 0)
    {
        List_insertHead(list, element);
        return;
    }

    int compareResultH = c(list->head->element, element);
    // the list has at least one element
    if ((compareResultH < 0 && order == 0) || (compareResultH >= 0 && order == 1))
    {
        List_insertHead(list, element);
        return;
    }

    int compareResultT = c(list->tail->element, element);
    if ((compareResultT >= 0 && order == 0) || (compareResultT < 0 && order == 1))
    {
        List_insertTail(list, element);
        return;
    }

    // the list has at least two elements
    // and the new one hasn't to be inserted as the first one nor as the last one
    struct Node **firstNodePtr = &(list->head);
    List__insertOrdered(firstNodePtr, element, c, order);

    list->length++;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// PICK AN ELEMENT FROM THE HEAD / TAIL

void *List_pickHead(T list)
{
    CHECK_POINTER_RETURN_NULL(list);

    return list->head->element;
}

void *List_pickTail(T list)
{
    CHECK_POINTER_RETURN_NULL(list);

    return list->tail->element;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// FIND AND PICK AN ELEMENT

static struct Node *List__findNode(struct Node *node, Predicate f)
{
    CHECK_POINTER_RETURN_NULL(node);

    if (f(node->element) == 1)
    {
        return node;
    }
    else
    {
        return List__findNode(node->next, f);
    }
}

static void *List__find(struct Node *node, Predicate f)
{
    struct Node *foundNode = List__findNode(node, f);

    CHECK_POINTER_RETURN_NULL(foundNode);

    return foundNode->element;
}

void *List_findPick(T list, Predicate f)
{
    CHECK_POINTER_RETURN_NULL(list);
    return List__find(list->head, f);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// EXTRACT AN ELEMENT FROM THE HEAD / TAIL

void *List_extractHead(T list)
{
    CHECK_POINTER_RETURN_NULL(list);

    // empty list
    CHECK_POINTER_RETURN_NULL(list->head);

    size_t listLength = List_length(list);
    struct Node *nodeToExtract = list->head;
    void *elementToRet = nodeToExtract->element;

    if (listLength == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    if (listLength > 1)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    Node_free(&nodeToExtract, 0);

    list->length--;

    return elementToRet;
}

void *List_extractTail(T list)
{
    // O(1)
    CHECK_POINTER_RETURN_NULL(list);

    // empty list
    CHECK_POINTER_RETURN_NULL(list->tail);

    size_t listLength = List_length(list);
    struct Node *nodeToExtract = list->tail;
    void *elementToRet = nodeToExtract->element;

    if (listLength == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    if (listLength > 1)
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    Node_free(&nodeToExtract, 0);

    list->length--;

    return elementToRet;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// FIND AND EXTRACT AN ELEMENT

void *List_findExtract(T list, Predicate f)
{
    CHECK_POINTER_RETURN_NULL(list);

    struct Node *nodeToExtract = List__findNode(list->head, f);

    CHECK_POINTER_RETURN_NULL(nodeToExtract);

    void *elementToRet = nodeToExtract->element;

    if (nodeToExtract == list->head)
    {
        return List_extractHead(list);
    }

    if (nodeToExtract == list->tail)
    {
        return List_extractTail(list);
    }

    nodeToExtract->next->prev = nodeToExtract->prev;
    nodeToExtract->prev->next = nodeToExtract->next;

    Node_free(&nodeToExtract, 0);

    list->length--;

    return elementToRet;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// DELETE HEAD / TAIL

void List_deleteHead(T list)
{
    CHECK_POINTER_RETURN_VOID(list);

    // empty list
    CHECK_POINTER_RETURN_VOID(list->head);

    size_t listLength = List_length(list);
    struct Node *nodeToRemove = list->head;

    if (listLength == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    if (listLength > 1)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    IF_NOT_NULL(
        list->deallocator,
        list->deallocator(nodeToRemove->element););

    Node_free(&nodeToRemove, 1);

    list->length--;
}

void List_deleteTail(T list)
{
    CHECK_POINTER_RETURN_VOID(list);

    // empty list
    CHECK_POINTER_RETURN_VOID(list->tail);

    size_t listLength = List_length(list);
    struct Node *nodeToRemove = list->tail;

    if (listLength == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    if (listLength > 1)
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    IF_NOT_NULL(
        list->deallocator,
        list->deallocator(nodeToRemove->element););

    Node_free(&nodeToRemove, 1);

    list->length--;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// FIND AND DELETE AN ELEMENT

void List_findDelete(T list, Predicate f)
{
    CHECK_POINTER_RETURN_VOID(list);

    struct Node *nodeToRemove = List__findNode(list->head, f);

    CHECK_POINTER_RETURN_VOID(nodeToRemove);

    if (nodeToRemove == list->head)
    {
        List_deleteHead(list);
        return;
    }

    if (nodeToRemove == list->tail)
    {
        List_deleteTail(list);
        return;
    }

    nodeToRemove->next->prev = nodeToRemove->prev;
    nodeToRemove->prev->next = nodeToRemove->next;

    IF_NOT_NULL(
        list->deallocator,
        list->deallocator(nodeToRemove->element););

    Node_free(&nodeToRemove, 1);

    list->length--;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// CHECK IF AN ELEMENT SATISFIES A PREDICATE

int List_any(T list, Predicate f)
{
    CHECK_POINTER_RETURN(list, 0);
    return List__find(list->head, f) != NULL;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// CHECK IF ALL ELEMENTS SATISFY A PREDICATE

static int List__all(struct Node *node, Predicate f)
{
    CHECK_POINTER_RETURN(node, 1);

    if (f(node->element) == 1)
    {
        return List__all(node->next, f);
    }
    else
    {
        return 0;
    }
}

int List_all(T list, Predicate f)
{
    CHECK_POINTER_RETURN(list, 1);
    return List__all(list->head, f);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// GET THE LENGTH

size_t List_length(T list)
{
    CHECK_POINTER_RETURN(list, (size_t)0);
    return list->length;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// REVERSE THE LIST

static struct Node *List__reverse(struct Node *node)
{
    // READ node == read current node address

    struct Node *self = node;

    struct Node *futureHead = NULL;
    struct Node *futureSelfNext = NULL;
    struct Node *futureSelfPrev = NULL;

    if (self->next == NULL)
    {
        // in this case self is the address of
        // the old last element aka the new head
        futureHead = self;

        futureSelfNext = self->prev;
        futureSelfPrev = NULL;
    }
    else
    {
        // reverse the remaining list
        futureHead = List__reverse(self->next);

        // self->next is the address of
        // the old next element that is going
        // to be the previous element

        futureSelfNext = self->prev;
        futureSelfPrev = self->next;
    }

    // rotate pointers
    self->next = futureSelfNext;
    self->prev = futureSelfPrev;

    // propagate back the address of the new head
    return futureHead;
}

void List_reverse(T list)
{
    if (List_length(list) <= 1)
    {
        return;
    }

    // there are at least 2 elements
    struct Node *newTail = list->head;
    list->head = List__reverse(list->head);
    list->tail = newTail;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// REDUCE - FILTER - MAP

void *List_reduce(T list, Reducer reducer, void *initialValue)
{
    void *accumulator = initialValue;

    struct Node *runner = list->head;
    while (runner != NULL)
    {
        accumulator = reducer(accumulator, runner->element);
        runner = runner->next;
    }
    return accumulator;
}

T List_map(T list, Projection projection, Comparator c, Duplicator du, Deallocator de)
{
    T newList = List_create(c, du, de);

    struct Node *runner = list->head;
    while (runner != NULL)
    {
        void *newValue = projection(runner->element);
        List_insertTail(newList, newValue);
        runner = runner->next;
    }

    return newList;
}

T List_filter(T list, Predicate predicate, int useDuplicator)
{
    T newList = List_create(list->comparator, list->duplicator, list->deallocator);

    struct Node *runner = list->head;
    while (runner != NULL)
    {
        int res = predicate(runner->element);
        if (res == 1)
        {
            void *toInsert = useDuplicator ? list->duplicator(runner->element) : runner->element;
            List_insertTail(newList, toInsert);
        }
        runner = runner->next;
    }

    return newList;
}

void List_forEach(T list, ForEachCallback callback)
{
    struct Node *runner = list->head;
    while (runner != NULL)
    {
        callback(runner->element);
        runner = runner->next;
    }
}

void List_forEach_right(T list, ForEachCallback callback)
{
    struct Node *runner = list->tail;
    while (runner != NULL)
    {
        callback(runner->element);
        runner = runner->prev;
    }
}
