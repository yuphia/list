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
    };

enum errorsList
{
    NO_ERROR,
    LIST_DESTRUCTED,
    CALLOC_ERROR,
    POINTER_ERROR,
    OVERFLOW_ERROR,
    LOG_ERROR,
    FATAL_ERROR
};

struct errorMap
{
    int map;
    bool listDestructed; // << 2
    bool callocError; // Always treated outside of verificator
    bool pointerError; // << 1
    bool overflowError; // << 3
    bool logError;
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

errorsList verificatorList (List *list, errorMap* verificatorMap);

bool dumpList (errorMap* verificatorMap, errorInfo info, List* list);
errorsList dumpDotList (errorMap* verificatorMap, errorInfo info);

#endif