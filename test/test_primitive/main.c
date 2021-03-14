#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int compareNumbers(void *vn1, void *vn2)
{
    int *pn1 = vn1;
    int *pn2 = vn2;
    return *pn1 - *pn2;
}

void *duplicateNumber(void *vn)
{
    int *pn = vn;
    int *pnd = malloc(sizeof(*pnd));
    if (pnd == NULL)
    {
        exit(EXIT_FAILURE);
    }
    *pnd = *pn;
    return pnd;
}

void print(void *vn)
{
    int *pn = vn;
    printf("%d\n", *pn);
}

#define DEBUG_NUMBER(N, M) \
    printf("%d should be %d\n", N, M);

#define DEBUG_P_NUMBER(P, N) \
    DEBUG_NUMBER(*P, N);

#define DEBUG_POINTER(P, V) \
    printf("%p should be %p\n", P, V);

int findThree(void *vnp)
{
    int *np = vnp;
    return *np == 3;
}

int findSix(void *vnp)
{
    int *np = vnp;
    return *np == 6;
}

int lessThanTen(void *vnp)
{
    int *np = vnp;
    return *np < 10;
}

int isEven(void *vnp)
{
    int *np = vnp;
    return *np % 2 == 0;
}

int isOdd(void *vnp)
{
    return isEven(vnp) == 0;
}

void *times2(void *vnp)
{
    int *np = vnp;
    int *dp = malloc(sizeof(*dp));
    if (dp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    *dp = *np * 2;
    return dp;
}

void *minus1(void *vnp)
{
    int *np = vnp;
    int *mp = malloc(sizeof(*mp));
    if (mp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    *mp = *np - 1;
    return mp;
}

void *sum(void *acc, void *vnp)
{
    int *currSum = acc;
    int *np = vnp;
    *currSum += *np;
    return acc;
}

void *product(void *acc, void *vnp)
{
    int *currProd = acc;
    int *np = vnp;
    *currProd *= *np;
    return acc;
}

int main()
{

    List_T numbers = List_create(compareNumbers, duplicateNumber, NULL);

    int *n1 = malloc(sizeof(*n1));
    int *n2 = malloc(sizeof(*n2));
    int *n3 = malloc(sizeof(*n3));
    int *n4 = malloc(sizeof(*n4));
    int *n5 = malloc(sizeof(*n5));

    *n1 = 1;
    *n2 = 2;
    *n3 = 3;
    *n4 = 4;
    *n5 = 5;

    // -----------------------------------

    // List_insertHead(numbers, n1);
    // List_insertHead(numbers, n2);
    // List_insertHead(numbers, n3);
    // List_insertHead(numbers, n4);
    // List_insertHead(numbers, n5);

    // -----------------------------------

    // List_insertOrdered(numbers, n1, 0);
    // List_insertOrdered(numbers, n2, 0);
    // List_insertOrdered(numbers, n3, 0);
    // List_insertOrdered(numbers, n4, 0);
    // List_insertOrdered(numbers, n5, 0);

    // -----------------------------------

    // List_insertOrdered(numbers, n1, 1);
    // List_insertOrdered(numbers, n2, 1);
    // List_insertOrdered(numbers, n3, 1);
    // List_insertOrdered(numbers, n4, 1);
    // List_insertOrdered(numbers, n5, 1);

    // -----------------------------------

    List_insertTail(numbers, n1);
    List_insertTail(numbers, n2);
    List_insertTail(numbers, n3);
    List_insertTail(numbers, n4);
    List_insertTail(numbers, n5);

    // -----------------------------------

    // int *n_1 = List_pickHead(numbers);
    // int *n_5 = List_pickTail(numbers);
    // n_1 = List_pickHead(numbers);
    // n_5 = List_pickTail(numbers);

    // DEBUG_P_NUMBER(n_1, 1);
    // DEBUG_P_NUMBER(n_5, 5);

    // int *n_3 = List_findPick(numbers, findThree);
    // n_3 = List_findPick(numbers, findThree);
    // int *n_6 = List_findPick(numbers, findSix);

    // DEBUG_P_NUMBER(n_3, 3);
    // DEBUG_POINTER(n_6, NULL);

    // List_forEach(numbers, print);

    // -----------------------------------

    // int *n_1 = List_extractHead(numbers);
    // int *n_5 = List_extractTail(numbers);

    // DEBUG_P_NUMBER(n_1, 1);
    // DEBUG_P_NUMBER(n_5, 5);

    // int *n_3 = List_findExtract(numbers, findThree);
    // int *n_6 = List_findExtract(numbers, findSix);

    // DEBUG_P_NUMBER(n_3, 3);
    // DEBUG_POINTER(n_6, NULL);

    // DEBUG_NUMBER((int)List_length(numbers), 2);

    // List_forEach(numbers, print);

    // -----------------------------------

    // List_deleteHead(numbers);
    // List_deleteTail(numbers);
    // List_deleteHead(numbers);
    // List_deleteTail(numbers);

    // DEBUG_NUMBER((int)List_length(numbers), 1);

    // List_findDelete(numbers, findThree);
    // List_findDelete(numbers, findSix);

    // DEBUG_NUMBER((int)List_length(numbers), 0);

    // -----------------------------------

    // DEBUG_NUMBER(List_any(numbers, findThree), 1);
    // DEBUG_NUMBER(List_any(numbers, findSix), 0);

    // DEBUG_NUMBER(List_all(numbers, lessThanTen), 1);
    // DEBUG_NUMBER(List_all(numbers, findThree), 0);

    // List_forEach(numbers, print);

    // -----------------------------------

    // List_forEach(numbers, print);
    // List_forEach_right(numbers, print);

    // -----------------------------------

    // List_T oddNumbers = List_filter(numbers, isOdd, 1);
    // List_forEach(oddNumbers, print);
    // List_T evenNumbers = List_filter(numbers, isEven, 1);
    // List_forEach(evenNumbers, print);

    // List_free(&oddNumbers, 1);
    // List_free(&evenNumbers, 1);

    // oddNumbers = List_filter(numbers, isOdd, 0);
    // List_forEach(oddNumbers, print);
    // evenNumbers = List_filter(numbers, isEven, 0);
    // List_forEach(evenNumbers, print);

    // List_free(&oddNumbers, 0);
    // List_free(&evenNumbers, 0);

    // -----------------------------------

    // List_T timesTwoNumbers = List_map(numbers, times2, List_getComparator(numbers), List_getDuplicator(numbers), List_getDeallocator(numbers));
    // List_forEach(timesTwoNumbers, print);
    // List_T minusOneNumbers = List_map(numbers, minus1, List_getComparator(numbers), List_getDuplicator(numbers), List_getDeallocator(numbers));
    // List_forEach(minusOneNumbers, print);

    // List_free(&timesTwoNumbers, 1);
    // List_free(&minusOneNumbers, 1);

    // -----------------------------------
    // int *s = malloc(sizeof(*s));
    // if(s != NULL) {
    //     *s = 0;
    //     List_reduce(numbers, sum, s);
    //     DEBUG_P_NUMBER(s, 15);
    // }

    // int *p = malloc(sizeof(*p));
    // if(p != NULL) {
    //     *p = 1;
    //     List_reduce(numbers, product, p);
    //     DEBUG_P_NUMBER(p, 120);
    // }

    // free(s);
    // free(p);

    // -----------------------------------

    List_forEach(numbers, print);

    // List_reverse(numbers);

    // List_forEach_right(numbers, print);

    // -----------------------------------

    List_free(&numbers, 1);

    return 0;
}