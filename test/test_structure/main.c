#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"

typedef struct
{
    int age;
    char *name;
} Person;

void print(void *vp)
{
    Person *p = vp;

    printf("AGE: %d --- ", p->age);
    printf("NAME: %s\n", p->name);
}

int compare_person(void *vp1, void *vp2)
{
    Person *p1 = vp1;
    Person *p2 = vp2;

    int cn = strcmp(p1->name, p2->name);

    if (cn == 0)
    {
        return p1->age - p2->age;
    }

    return cn;
}

void* duplicate_person(void *vp)
{
    Person *p = vp;
    Person *p1 = malloc(sizeof(*p1));

    if (p1 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    p1->age = p->age;
    p1->name = strndup(p->name, strlen(p->name));

    return p1;
}

void free_person(void *vp)
{
    Person *p = vp;
    free(p->name);
}
#define DEBUG_NUMBER(N, M) \
    printf("%d should be %d\n", N, M);

#define DEBUG_P_NUMBER(P, N) \
    DEBUG_NUMBER(*P, N);

#define DEBUG_POINTER(P, V) \
    printf("%p should be %p\n", P, V);

int findAgeThree(void *vp)
{
    Person *p = vp;
    return p->age == 3;
}

int findNameBarbara(void *vp)
{
    Person *p = vp;
    return strcmp(p->name, "Barbara") == 0;
}

int ageLessThanTen(void *vp)
{
    Person *p = vp;
    return p->age < 10;
}

int isAgeEven(void *vp)
{
    Person *p = vp;
    return p->age % 2 == 0;
}

int isAgeOdd(void *vp)
{
    return isAgeEven(vp) == 0;
}

void *times2Age(void *vp)
{
    Person *p = vp;
    Person *dp = malloc(sizeof(*dp));
    if (dp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    dp->age = p->age * 2;
    dp->name = strndup(p->name, strlen(p->name));
    return dp;
}

void *minus1Age(void *vp)
{
    Person *p = vp;
    Person *dp = malloc(sizeof(*dp));
    if (dp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    dp->age = p->age - 1;
    dp->name = strndup(p->name, strlen(p->name));
    return dp;
}

void *sumAges(void *acc, void *vp)
{
    int *currSum = acc;
    Person *p = vp;
    *currSum += p->age;
    return acc;
}

void *productAges(void *acc, void *vp)
{
    int *currProd = acc;
    Person *p = vp;
    *currProd *= p->age;
    return acc;
}

int main()
{

    List_T people = List_create(compare_person, duplicate_person, free_person);

    Person *p1 = malloc(sizeof(*p1));
    Person *p2 = malloc(sizeof(*p2));
    Person *p3 = malloc(sizeof(*p3));
    Person *p4 = malloc(sizeof(*p4));
    Person *p5 = malloc(sizeof(*p5));

    p1->age = 1;
    p1->name = malloc(1000);
    scanf("%s", p1->name);

    p2->age = 2;
    p2->name = malloc(1000);
    scanf("%s", p2->name);

    p3->age = 3;
    p3->name = malloc(1000);
    scanf("%s", p3->name);

    p4->age = 4;
    p4->name = malloc(1000);
    scanf("%s", p4->name);

    p5->age = 5;
    p5->name = malloc(1000);
    scanf("%s", p5->name);

    // -----------------------------------

    // List_insertHead(people, p1);
    // List_insertHead(people, p2);
    // List_insertHead(people, p3);
    // List_insertHead(people, p4);
    // List_insertHead(people, p5);

    // -----------------------------------

    // List_insertOrdered(people, p1, 0);
    // List_insertOrdered(people, p2, 0);
    // List_insertOrdered(people, p3, 0);
    // List_insertOrdered(people, p4, 0);
    // List_insertOrdered(people, p5, 0);

    // -----------------------------------

    // List_insertOrdered(people, p1, 1);
    // List_insertOrdered(people, p2, 1);
    // List_insertOrdered(people, p3, 1);
    // List_insertOrdered(people, p4, 1);
    // List_insertOrdered(people, p5, 1);

    // -----------------------------------

    List_insertTail(people, p1);
    List_insertTail(people, p2);
    List_insertTail(people, p3);
    List_insertTail(people, p4);
    List_insertTail(people, p5);

    // -----------------------------------

    // puts("--------------------------------------------");

    // Person *p_1 = List_pickHead(people);
    // print(p_1);
    // Person *p_5 = List_pickTail(people);
    // print(p_5);
    // p_1 = List_pickHead(people);
    // p_5 = List_pickTail(people);
    // print(p_1);
    // print(p_5);

    // Person *p_3 = List_findPick(people, findAgeThree);
    // print(p_3);
    // p_3 = List_findPick(people, findAgeThree);
    // print(p_3);
    // Person *p_B = List_findPick(people, findNameBarbara);
    // DEBUG_POINTER(p_B, NULL);
    // puts("--------------------------------------------");

    // List_forEach(people, print);

    // -----------------------------------

    // puts("--------------------------------------------");

    // Person *p_1 = List_extractHead(people);
    // print(p_1);
    // Person *p_5 = List_extractTail(people);
    // print(p_5);

    // DEBUG_NUMBER((int)List_length(people), 3)

    // Person *p_2 = List_extractHead(people);
    // Person *p_4 = List_extractTail(people);
    // print(p_2);
    // print(p_4);

    // DEBUG_NUMBER((int)List_length(people), 1)

    // Person *p_3 = List_findExtract(people, findAgeThree);
    // print(p_3);
    // p_3 = List_findExtract(people, findAgeThree);
    // DEBUG_POINTER(p_3, NULL);

    // Person *p_B = List_findExtract(people, findNameBarbara);
    // DEBUG_POINTER(p_B, NULL);

    // DEBUG_NUMBER((int)List_length(people), 0)
    // puts("--------------------------------------------");

    // -----------------------------------
    // List_extractHead(people);
    // DEBUG_NUMBER((int)List_length(people), 4)
    // List_extractHead(people);
    // DEBUG_NUMBER((int)List_length(people), 3)
    // List_extractHead(people);
    // DEBUG_NUMBER((int)List_length(people), 2)
    // List_extractHead(people);
    // DEBUG_NUMBER((int)List_length(people), 1)
    // List_extractHead(people);
    // DEBUG_NUMBER((int)List_length(people), 0)
    // List_extractHead(people);
    // List_extractHead(people);
    // DEBUG_NUMBER((int)List_length(people), 0)
    // -----------------------------------

    // List_extractTail(people);
    // DEBUG_NUMBER((int)List_length(people), 4)
    // List_extractTail(people);
    // DEBUG_NUMBER((int)List_length(people), 3)
    // List_extractTail(people);
    // DEBUG_NUMBER((int)List_length(people), 2)
    // List_extractTail(people);
    // DEBUG_NUMBER((int)List_length(people), 1)
    // List_extractTail(people);
    // DEBUG_NUMBER((int)List_length(people), 0)
    // List_extractTail(people);
    // List_extractTail(people);
    // DEBUG_NUMBER((int)List_length(people), 0)

    // -----------------------------------

    // puts("--------------------------------------------");

    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 4)
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 3)
    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 2)
    // List_deleteTail(people);

    // DEBUG_NUMBER((int)List_length(people), 1)

    // List_findDelete(people, findAgeThree);
    // List_findDelete(people, findNameBarbara);

    // List_deleteTail(people);
    // List_deleteTail(people);
    // List_deleteTail(people);
    // List_deleteHead(people);
    // List_deleteHead(people);
    // List_deleteHead(people);

    // DEBUG_NUMBER((int)List_length(people), 0)
    // puts("--------------------------------------------");

    // -----------------------------------
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 4)
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 3)
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 2)
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 1)
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 0)
    // List_deleteTail(people);
    // List_deleteTail(people);
    // DEBUG_NUMBER((int)List_length(people), 0)
    // -----------------------------------

    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 4)
    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 3)
    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 2)
    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 1)
    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 0)
    // List_deleteHead(people);
    // List_deleteHead(people);
    // DEBUG_NUMBER((int)List_length(people), 0)

    // -----------------------------------

    // DEBUG_NUMBER(List_any(people, findAgeThree), 1);
    // DEBUG_NUMBER(List_any(people, findNameBarbara), 0);

    // DEBUG_NUMBER(List_all(people, ageLessThanTen), 1);
    // DEBUG_NUMBER(List_all(people, findAgeThree), 0);

    // List_forEach(people, print);

    // -----------------------------------

    // List_forEach(people, print);
    // List_forEach_right(people, print);

    // -----------------------------------

    List_T oddPeople = List_filter(people, isAgeOdd, 0);
    List_forEach(oddPeople, print);
    puts("--------------------------------------------");
    List_T evenPeople = List_filter(people, isAgeEven, 0);
    List_forEach(evenPeople, print);
    puts("--------------------------------------------");

    List_free(&oddPeople, 0);
    List_free(&evenPeople, 0);

    oddPeople = List_filter(people, isAgeOdd, 1);
    List_forEach(oddPeople, print);
    puts("--------------------------------------------");
    evenPeople = List_filter(people, isAgeEven, 1);
    List_forEach(evenPeople, print);
    puts("--------------------------------------------");

    List_free(&oddPeople, 1);
    List_free(&evenPeople, 1);

    // -----------------------------------

    // List_T timesTwoPeople = List_map(people, times2Age, List_getComparator(people), List_getDuplicator(people), List_getDeallocator(people));
    // List_forEach(timesTwoPeople, print);
    // List_T minusOnePeople = List_map(people, minus1Age, List_getComparator(people), List_getDuplicator(people), List_getDeallocator(people));
    // List_forEach(minusOnePeople, print);

    // List_free(&timesTwoPeople, 1);
    // List_free(&minusOnePeople, 1);

    // -----------------------------------
    // int *s = malloc(sizeof(*s));
    // if(s != NULL) {
    //     *s = 0;
    //     List_reduce(people, sumAges, s);
    //     DEBUG_P_NUMBER(s, 15);
    // }

    // int *p = malloc(sizeof(*p));
    // if(p != NULL) {
    //     *p = 1;
    //     List_reduce(people, productAges, p);
    //     DEBUG_P_NUMBER(p, 120);
    // }

    // free(s);
    // free(p);

    // -----------------------------------

    // List_forEach(people, print);

    // List_reverse(people);

    // List_forEach_right(people, print);

    // -----------------------------------

    List_free(&people, 1);

    return 0;
}