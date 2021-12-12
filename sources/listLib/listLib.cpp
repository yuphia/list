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

        listAt (i) = 0;
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
        verificatorMap->map |= 0b1;
        return NO_ERROR;
    }

    if (list->data == nullptr &&
        list->next == nullptr &&
        list->prev == nullptr &&
        list->head     == -1  &&
        list->capacity < 0    &&
        list->size     < 0    &&
        list->tail     == -1)
    {
        verificatorMap->map |= 0b10; 
        return NO_ERROR;
    }

    if (list->data == nullptr)
    {
        verificatorMap->map |= 0b1000;
    }
    
    if (list->next == nullptr)
    {
        verificatorMap->map |= 0b10000;
    }
    
    if (list->prev == nullptr)
    {
        verificatorMap->map |= 0b100000;
    }

    if (list->capacity < list->size)
    {
        verificatorMap->map |= 0b100;
    }    

    return NO_ERROR;        
}

errorsList listInsertAfter (List *list, size_t place, data_t val)
{   
    DUMP_LIST();
      
    if (list->size == list->capacity)
    {
        errorsList tempErr = listRealloc (list, 2);
        if (tempErr != NO_ERROR)
            return tempErr;
    }
  
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

    list->isSorted = 0;

    list->size++;

    DUMP_LIST_END_OF_FUNC(); 

    return NO_ERROR;
}

errorsList listInsertAfterTail (List *list, data_t val)
{
    DUMP_LIST();
       
    if (list->size == list->capacity)
    {
        errorsList tempErr = listRealloc (list, 2);
        if (tempErr != NO_ERROR)
            return tempErr;
    }  

    size_t insertPlace = list->free;
    list->free = listNextAt (insertPlace);

    listAt (insertPlace) = val;
    listPrevAt (insertPlace) = list->tail;
    listNextAt (insertPlace) = 0;

    listNextAt (list->tail) = insertPlace;

    list->tail = insertPlace;

    list->size++;

    DUMP_LIST_END_OF_FUNC ();
    return NO_ERROR;
}

errorsList listInsertBeforeHead (List* list, data_t val)
{
    DUMP_LIST();
    
    if (list->size == list->capacity)
    {
        errorsList tempErr = listRealloc (list, 2);
        if (tempErr != NO_ERROR)
            return tempErr;
    }

    size_t insertPlace = list->free;
    list->free = listNextAt (insertPlace);

    listAt (insertPlace) = val;
    listNextAt (insertPlace) = list->head;
    listPrevAt (insertPlace) = 0;

    listPrevAt (list->head) = insertPlace;

    list->head = insertPlace;

    list->size++;

    DUMP_LIST_END_OF_FUNC ();
    return NO_ERROR;
}

errorsList listInsertBefore (List* list, size_t place, data_t val)
{
    DUMP_LIST();

    if (list->size == list->capacity)
    {
        errorsList tempErr = listRealloc (list, 2);
        if (tempErr != NO_ERROR)
            return NO_ERROR;
    }
   
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

    list->isSorted = 0;

    list->size++;

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

    if (verificatorMap->map & 0b100000)
    {
        PRINT_LOGS ("Error Detected! Error PREV_DEAD.\n"
                    "Pointer to buffer Next is dead\n"                    
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n\n\n");    

        errorState = false;        
    }

    if (verificatorMap->map & 0b10000)
    {
        PRINT_LOGS ("Error Detected! Error NEXT_DEAD.\n"
                    "Pointer to buffer Next is dead\n"                    
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n\n\n");    

        errorState = false;        
    }

    if (verificatorMap->map & 0b1000)
    {
         PRINT_LOGS ("Error Detected! Error DATA_DEAD.\n"
                    "Pointer to buffer Prev is dead\n"
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n\n\n");    

        errorState = false;              
    }

    if (verificatorMap->map & 0b100)
    {
        PRINT_LOGS ("Error Detected! Error OVERFLOW_ERROR.\n"
                    "Somehow the current number of elements is larger than capcity of the buffer\n"
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n\n\n");    

        errorState = false;        
    }
    
    if (verificatorMap->map & 0b10)
    {
        PRINT_LOGS ("Error Detected! Error LIST_DESTRUCTED.\n"
                    "The data structure has already been destructed\n"
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n\n\n");   
        errorState = false;        
    }

    if (verificatorMap->map & 0b1)
    {
        PRINT_LOGS ("Error Detected! Error POINTER_ERROR.\n"
                    "The pointer to data structure is equal to nullptr\n"
                    "Be careful!\n"
                    "The elements aren't going to be printed as it may cause UB\n\n\n");   
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

        fprintf (logs.logPointer,
                    "Pointer to data: %p\n"
                    "Pointer to next: %p\n"
                    "Pointer to prev: %p\n"
                    "Head: %zu\n"
                    "Tail: %zu\n"
                    "Capacity: %zu\n"
                    "Size: %zu\n"
                    "Free: %zu\n"
                    "isSorted: %d\n\n", 
                    list->data,
                    list->next,
                    list->prev,
                    list->head,
                    list->tail,
                    list->capacity,
                    list->size,
                    list->free,
                    list->isSorted);

        listPrinter (list, logs.logPointer);
    }
    PRINT_SPLITTER();

    logs.err = closeLogs (&logs);
    if (logs.err != 0)
    {
        printf ("Logs are dead, error when closing\n");
        return false;
    }

    dumpCounter++;
    return errorState;      
}

errorsList dumpDotList (List *list)
{
    FILE* dotLog = fopen ("dotShit.dot", "w");

    dumpDotSetupGraphNotFree (dotLog);

    dumpDotListNodeNotFree (list, 0, dotLog);

    for (int i = list->head; i != 0; i = listNextAt(i))
        dumpDotListNodeNotFree (list, i, dotLog);

    dumpDotSetupGraphFree (dotLog);

    for (int i = list->free; listNextAt (i) != 0; i = listNextAt(i))
        dumpDotListNodeFree (list, i, dotLog);

    endDotFree (dotLog);

    dumpDotConnectNotFree (list, dotLog);
    dumpDotConnectFree (list, dotLog);

    dumpDotEndGraph (dotLog);

    fclose (dotLog);
    return NO_ERROR;
}

errorsList listRealloc (List *list, size_t newSize)
{   
    DUMP_LIST();

    list->data = (data_t*) realloc (list->data, newSize * list->capacity * sizeof (data_t));
    list->next = (int*)    realloc (list->next, newSize * list->capacity * sizeof    (int));
    list->prev = (int*)    realloc (list->prev, newSize * list->capacity * sizeof    (int));
    
    list->capacity *= newSize;
    listFillEmpty (list);
    
    list->free = list->size;

    listSort (list);

    DUMP_LIST_END_OF_FUNC();
    return NO_ERROR;
}

errorsList listSort (List *list)
{
    DUMP_LIST ();

    data_t* newData = (data_t*)calloc (list->capacity, sizeof(data_t));
    int*    newNext = (int*)   calloc (list->capacity, sizeof   (int));
    int*    newPrev = (int*)   calloc (list->capacity, sizeof   (int));

    for (size_t placeInOldList = list->head, placeInNewList = 1;
         listNextAt (placeInOldList) != 0 
         || listPrevAt (placeInOldList) != 0;
         placeInOldList = listNextAt(placeInOldList), placeInNewList++)
    {
        *(newData + placeInNewList) =     listAt (placeInOldList);
        *(newNext + placeInNewList) =          placeInNewList + 1;
        *(newPrev + placeInNewList) =          placeInNewList - 1;
    }

    free (list->data);
    free (list->next);
    free (list->prev);
    
    list->data = newData;
    list->next = newNext;
    list->prev = newPrev;

    list->head =              1;
    list->tail = list->size - 1;

    listFillEmpty (list);

    DUMP_LIST_END_OF_FUNC ();
    return NO_ERROR;
}

errorsList listSwap (List *list, size_t n1, size_t n2)
{
    DUMP_LIST();

    data_t tempValN1 = listAt (n1);
    data_t tempValN2 = listAt (n2);

    listAt (n1) = 0;
    listAt (n2) = 0;

    listAt (n1) = tempValN2;
    listAt (n2) = tempValN1;

    

    /*size_t tempNext = listNextAt (n1);
    listNextAt (n1) = listNextAt (n2);
    listNextAt (n2) = tempNext;*/

    /*size_t tempPrev = listPrevAt (n1);
    listPrevAt (n1) = listPrevAt (n2);
    listPrevAt (n2) = tempPrev;*/
    list->isSorted = 0;

    DUMP_LIST_END_OF_FUNC();

    return NO_ERROR;
}

errorsList listDeleteElement (List *list, size_t place)
{
    DUMP_LIST();

    listAt (place) = 0;
    
    if (place == list->head)
        list->head = listNextAt (place);
        
    listPrevAt (listNextAt (place)) = listPrevAt (place);
    
    if (place == list->tail)
        list->tail = listPrevAt (place);

    listNextAt (listPrevAt (place)) = listNextAt (place);

    listNextAt (place) = list->free;
    list->free = place;
    listPrevAt (place) = -1;

    list->size--;

    DUMP_LIST_END_OF_FUNC();
    return NO_ERROR;
}
errorsList listReverse (List* list)

{
    DUMP_LIST();

    for (size_t i = list->head; listNextAt (i) != 0 || listPrevAt (i) != 0;
                                                         i = listPrevAt (i))
        listReverseSwap (list, i);       

    listSwapTailHead (list);

    list->isSorted = 0;

    DUMP_LIST_END_OF_FUNC();

    return NO_ERROR;
}

errorsList listReverseSwap (List* list, size_t n)
{
    DUMP_LIST();

    size_t nextSave = listNextAt (n);
    listNextAt (n) = listPrevAt (n);
    listPrevAt (n) = nextSave; 

    list->isSorted = 0;

    DUMP_LIST_END_OF_FUNC();

    return NO_ERROR;
}

errorsList listPrintLogic (List *list, FILE* stream)
{
    DUMP_LIST();

    for (size_t i = list->head; listNextAt (i) != 0 || listPrevAt (i) != 0;
                                                       i = listNextAt (i))
        fprintf (stream, "%d\n", listAt (i));

    DUMP_LIST_END_OF_FUNC();
    return NO_ERROR;
}

errorsList listSwapTailHead (List *list)
{
    DUMP_LIST();

    size_t headSave = list->head;
    list->head = list->tail;
    list->tail = headSave;

    DUMP_LIST_END_OF_FUNC();
    return NO_ERROR;
}


void dumpDotListNodeNotFree (List* list, size_t physicalSpace, FILE* dotFile)
{
    static int rank = 1;
    fprintf (dotFile, "    node%zu [rank = %d, shape = record, label = \"physSpace = %zu "
                      "| {<prev> prev = %d | <data> data = %d | <next> next = %d}\"];\n",
                    physicalSpace, rank, physicalSpace, listPrevAt (physicalSpace), listAt (physicalSpace), listNextAt (physicalSpace));

    rank++;
}

void dumpDotListNodeFree (List* list, size_t physicalSpace, FILE* dotFile)
{
    static int rank = 1;
    fprintf (dotFile, "    free%zu [rank = %d, shape = record, label = \"next = %d \"];\n", 
                    physicalSpace, rank, listNextAt (physicalSpace));

    rank++;
}

void dumpDotSetupGraphFree (FILE* dotFile)
{
    fprintf (dotFile, "    node [color = green];\n"
                      "    subgraph cluster_Free{\n");
}

void endDotFree (FILE* dotFile)
{
    fprintf (dotFile, "    label = \"Free elements\";\n"
                      "    color = green;\n"
                      "}\n");
}

void dumpDotSetupGraphNotFree (FILE* dotFile)
{
    fprintf (dotFile, "digraph List{\n"
                   "    rankdir = LR;\n"    
                   "    edge [dir =\"both\"];\n");
}

void dumpDotEndGraph (FILE* dotFile)
{
    fprintf (dotFile, "}\n");
}

void dumpDotConnectFree (List* list, FILE* dotFile)
{
    fprintf (dotFile, "edge [dir = \"forward\"];\n");
    for (int i = list->free; listPrevAt (listNextAt(i)) != -1 || listNextAt(listNextAt(i)) != 0; i = listNextAt (i))
    {
        printf ("%d\n", i);
        fprintf (dotFile, "    \"free%d\" -> \"free%d\";\n", i, listNextAt (i));
    }
}

void dumpDotConnectNotFree (List* list, FILE* dotFile)
{
    for (int i = list->head; listPrevAt (i) != 0 || listNextAt(i) != 0; i = listNextAt (i))
    {
        //printf ("%d\n", i);
        fprintf (dotFile, "    \"node%d\":<next> -> \"node%d\":<prev>;\n", listPrevAt (i), i);
    }
}
#endif

