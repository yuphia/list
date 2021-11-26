#ifndef LISTLIB_CPP

#define LISTLIB_CPP 1

#include "listLib.h"
#include "dump.h"
#include "logs.h"

errorsList listCtor (List *list, data_t firstValue)
{
    if (list == nullptr)
        return POINTER_ERROR;
    errorsList tempErr = NO_ERROR;

    list->data = (data_t*)calloc (5, sizeof (data_t));
    if (list->data == nullptr)
    {
        tempErr = CALLOC_ERROR;
        return tempErr;
    }

    list->next = (int*)calloc (5, sizeof (int));
    if (list->next == nullptr)
    {
        tempErr = CALLOC_ERROR;
        return tempErr;
    }

    list->prev = (int*)calloc (5, sizeof (int));
    if (list->prev == nullptr)
    {
        tempErr = CALLOC_ERROR;
        return tempErr;
    }

    listAt(1) = firstValue;
    listNextAt(1) = 0;
    listPrevAt(1) = 0;

    list->head = 1;
    list->tail = 1; 

    list->capacity = 5;
    list->size = 2; 

    listFillEmpty (list);

    return NO_ERROR;
}

errorsList listPrinter (List *list)
{
    if (list == nullptr)
        return POINTER_ERROR;

    printf ("data   next    prev\n");

    for (size_t i = 0; i < list->capacity; i++)
    {
        printf ("%4d   %4d   %4d\n", 
                listAt(i), listNextAt(i), listPrevAt(i));        
    }    

    return NO_ERROR;
}

errorsList listFillEmpty (List *list) //LIST HAS TO BE SORTED!!!
{
    if (list == nullptr)
        return POINTER_ERROR;

    for (size_t i = list->size; i < list->capacity; i++)
    {
        listNextAt(i) = -1;
        listPrevAt(i) = -1;
    }

    return NO_ERROR;
}

/*errorsList listInsertToBack (List *list, data_t data)
{
    if (list == nullptr)
        return POINTER_ERROR;

    
}*/

errorsList listDtor (List *list)
{
    list->data, list->next, list->prev = nullptr;
    
    list->head = -1;
    list->tail = -1;

    list->capacity = -1;
    list->size = -1;

    return NO_ERROR;
}

errorsList verificatorList (List *list, errorMap* verificatorMap)
{
    const struct errorMap nullifierMap = {};
    *verificatorMap = nullifierMap;
    
    if (list == nullptr)
    {
        verificatorMap->pointerError = 1;
        return NO_ERROR;
    }

    if (list->data == nullptr ||
        list->next == nullptr ||
        list->prev == nullptr ||
        list->head     == -1  ||
        list->capacity < 0    ||
        list->size     < 0    ||
        list->tail     == -1)
    {
        verificatorMap->listDestructed = 1;        
        return NO_ERROR;
    }

    if (list->capacity < list->size)
    {
        verificatorMap->overflowError = 1;
    }    

    return NO_ERROR;        
}

errorsList dumpList (errorMap* verificatorMap, errorInfo info)
{
    LogFile logs = {nullptr, 1};
    fprintf ("");         
}

#endif

