#ifndef LISTLIB_H

#define LISTLIB_H 1

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

#define listAt(i) *(list->data + i)
#define listNextAt(i) *(list->next + i)
#define listPrevAt(i) *(list->prev + i)

typedef int data_t;

const size_t START_LIST_CAPACITY = 10;

struct List
    {
    data_t* data;
    int*    next;
    int*    prev;

    size_t head;
    size_t tail;                

    size_t capacity;
    size_t size;

    size_t free;

    bool isSorted = 1; 
    };

enum errorsList
{
    NO_ERROR,
    LIST_DESTRUCTED,
    CALLOC_ERROR,
    REALLOC_ERROR,
    POINTER_ERROR,
    OVERFLOW_ERROR,
    DATA_DEAD,
    NEXT_DEAD,
    PREV_DEAD,
    LOG_ERROR,
    FATAL_ERROR
};

struct errorMap
{
    int map;
};

struct errorInfo 
{
    int line;
    const char* funcName;    
    const char* file;
};

errorsList listCtor (List *list, data_t firstValue);
errorsList listPrinter (List *list, FILE* const stream);
errorsList listFillEmpty (List *list); //LIST HAS TO BE SORTED!!!
errorsList listDtor (List *list);

errorsList listInsertAfter (List *list, size_t place, data_t val);
errorsList listInsertAfterTail (List *list, data_t val);
errorsList listInsertBeforeHead (List* list, data_t val);
errorsList listInsertBefore (List* list, size_t place, data_t val);
errorsList listDeleteElement (List *list, size_t place);

errorsList listSwap (List *list, size_t n1, size_t n2);
errorsList listSort (List *list);
errorsList listRealloc (List *list, size_t newSize);
errorsList listSwapTailHead (List *list);

errorsList listReverseSwap (List* list, size_t n);
errorsList listReverse (List* list);

errorsList listPrintLogic (List *list, FILE* stream);

errorsList verificatorList (List *list, errorMap* verificatorMap);

void dumpDotListNodeFree (List* list, size_t physicalSpace, FILE* dotFile);
void dumpDotListNodeNotFree (List* list, size_t physicalSpace, FILE* dotFile);
void dumpDotEndGraph (FILE* dotFile);
void dumpDotSetupGraphNotFree (FILE* dotFile);
void dumpDotSetupGraphFree (FILE* dotFile);
void dumpDotConnectNotFree (List* list, FILE* dotFile);
void endDotFree (FILE* dotFile);
void dumpDotConnectFree (List* list, FILE* dotFile);

bool dumpList (errorMap* verificatorMap, errorInfo info, List* list);
errorsList dumpDotList (List* list);

#endif