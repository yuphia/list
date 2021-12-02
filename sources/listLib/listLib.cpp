#ifndef LISTLIB_CPP

#define LISTLIB_CPP 1

#include "listLib/listLib.h"
#include "listLib/dump.h"
#include "logs/logs.h"



errorsList listCtor (List *list, data_t firstValue)
{
    //errorInfo bebra = {1, 2, 3};

    if (list == nullptr)
        return POINTER_ERROR;
    errorsList tempErr = NO_ERROR;

    list->data = (data_t*)calloc (START_LIST_CAPACITY,
                                  sizeof (data_t));
    if (list->data == nullptr)
    {
        
        tempErr = CALLOC_ERROR;
        return tempErr;
    }

    list->next = (int*)calloc (START_LIST_CAPACITY,
                               sizeof (int));
    if (list->next == nullptr)
    {
        tempErr = CALLOC_ERROR;
        return tempErr;
    }

    list->prev = (int*)calloc (START_LIST_CAPACITY, 
                               sizeof (int));
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

    list->capacity = START_LIST_CAPACITY;
    list->size = 2; 

    list->free = 2;

    listFillEmpty (list);

    DUMP_LIST();
    return NO_ERROR;
}

errorsList listPrinter (List *list, FILE* const stream)
{
    if (list == nullptr)
        return POINTER_ERROR;

    fprintf (stream, "data    next    prev\n");

    for (size_t i = 0; i < list->capacity; i++)
    { 
        fprintf (stream ,"%4d   %4d   %4d\n", 
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
        if (i < list->capacity - 1)
            listNextAt(i) = i + 1;
        else
            listNextAt(i) = 0;

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
    DUMP_LIST();

    free (list->data);
    free (list->next);
    free (list->prev);

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

    verificatorMap->map = 0;

    if (list == nullptr)
    {
        verificatorMap->pointerError = 1;
        verificatorMap->map |= 0b1;
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
        verificatorMap->map |= 0b10; 
    }

    if (list->capacity < list->size)
    {
        verificatorMap->map |= 0b100;
        verificatorMap->overflowError = 1;
    }    

    return NO_ERROR;        
}

errorsList listInsertAfter (List *list, size_t place, data_t val)
{   
    DUMP_LIST();
  
    /*if (list->size == list->capacity)
    {
        ;
    }*/
  
    if (place == list->tail)
    {
        errorsList tempErr = listInsertAfterTail (list, val);
        return tempErr;
    } 
    
    size_t insertPlace = list->free;
    list->free = listNextAt (insertPlace);

    listAt (insertPlace) = val;

    listNextAt (insertPlace) = listNextAt (place);
    listNextAt (place) = insertPlace;

    listPrevAt (insertPlace) = place;
    listPrevAt (listNextAt (insertPlace)) = insertPlace;

    DUMP_LIST_END_OF_FUNC(); 

    return NO_ERROR;
}

errorsList listInsertAfterTail (List *list, data_t val)
{
    DUMP_LIST();
   
    /*if (list->size == list->capacity)
    {
        ;
    }*/
   
    size_t insertPlace = list->free;
    list->free = listNextAt (insertPlace);

    listAt (insertPlace) = val;
    listPrevAt (insertPlace) = list->tail;
    listNextAt (insertPlace) = 0;

    listNextAt (list->tail) = insertPlace;

    list->tail = insertPlace;

    DUMP_LIST_END_OF_FUNC ();
    return NO_ERROR;
}

errorsList listInsertBeforeHead (List* list, data_t val)
{
    DUMP_LIST();
    
    /*if (list->size == list->capacity)
    {
        ;
    }*/

    size_t insertPlace = list->free;
    list->free = listNextAt (insertPlace);

    listAt (insertPlace) = val;
    listNextAt (insertPlace) = list->head;
    listPrevAt (insertPlace) = 0;

    listPrevAt (list->head) = insertPlace;

    list->head = insertPlace;

    DUMP_LIST_END_OF_FUNC ();
    return NO_ERROR;
}

errorsList listInsertBefore (List* list, size_t place, data_t val)
{
    DUMP_LIST();

    /*if (list->size == list->capacity)
    {
        ;
    }*/
   
    if (place == list->head)
    {
        errorsList tempErr = listInsertBeforeHead (list, val);
        return tempErr;
    }

    size_t insertPlace = list->free;
    list->free = listNextAt (insertPlace);

    listAt (insertPlace) = val;
    listNextAt (insertPlace) = place;
    listPrevAt (insertPlace) = listPrevAt (place);
    
    listPrevAt (place) = insertPlace;        
    listNextAt (listPrevAt (insertPlace)) = insertPlace;

    DUMP_LIST_END_OF_FUNC();

    return NO_ERROR;
}

bool dumpList (errorMap* verificatorMap, errorInfo info, List* list)
{
    static LogFile logs = {nullptr, 1, nullptr, NO_ERROR_LOG};
    static size_t dumpCounter = 1;

    bool errorState = true;

    logs.err = openLogs (&logs);
    if (logs.err != 0)
        printf ("Logs are dead, couldn't open\n");

    PRINT_SPLITTER();
    fprintf (logs.logPointer, "[dump #%zu]\n", dumpCounter);   

    if (verificatorMap->map & 0b100)
    {
        PRINT_LOGS ("Error Detected! Error OVERFLOW_ERROR.\n"
                    "Somehow the current number of elements is larger than capcity of the buffer\n"
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n");    

        errorState = false;        
    }
    
    if (verificatorMap->map & 0b10)
    {
        PRINT_LOGS ("Error Detected! Error LIST_DESTRUCTED.\n"
                    "The data structure has already been destructed\n"
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n");   
        errorState = false;        
    }

    if(verificatorMap->map == 0)
    {
        PRINT_LOGS ("No Errors Detected, everything is ok\n"
                    "Dumping the elements:\n\n");

        fprintf (logs.logPointer,
                    "In file: %s\n"
                    "In function: %s\n"
                    "In Line: %d\n\n", 
                    info.file, info.funcName, info.line);

        listPrinter (list, logs.logPointer);
    }
    PRINT_SPLITTER();

    logs.err = closeLogs (&logs);
    if (logs.err != 0)
    {
        printf ("Logs are dead, error when closing\n");
        return LOG_ERROR;
    }

    dumpCounter++;
    return errorState;      
}

errorsList dumpDotList (errorMap* verificatorMap, errorInfo info)
{

    return NO_ERROR;
}

//void printError ()

#endif

