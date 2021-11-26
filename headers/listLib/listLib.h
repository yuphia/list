#ifndef LISTLIB_H

#define LISTLIB_H 1

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

#define listAt(i) *(list->data + i)
#define listNextAt(i) *(list->next + i)
#define listPrevAt(i) *(list->prev + i)

typedef int data_t;

struct List
    {
    data_t* data;
    int*    next;
    int*    prev;

    size_t head;
    size_t tail;                

    size_t capacity;
    size_t size; 
    };

enum errorsList
{
    NO_ERROR,
    LIST_DESTRUCTED,
    CALLOC_ERROR,
    POINTER_ERROR,
    OVERFLOW_ERROR,
    LOG_ERROR
};

struct errorMap
{
    bool listDestructed;
    bool callocError;
    bool pointerError;
    bool overflowError;
    bool logError;
};

struct errorInfo 
{
    char* funcName;
    int line;
    char* file;
};

errorsList listCtor (List *list, data_t firstValue);
errorsList listPrinter (List *list);
errorsList listFillEmpty (List *list); //LIST HAS TO BE SORTED!!!
errorsList listDtor (List *list);
errorsList verificatorList (List *list, errorMap* verificatorMap);
errorsList dumpList (errorMap* verificatorMap, errorInfo info);
errorsList dumpListDot (errorMap* verificatorMap, errorInfo info);
#endif