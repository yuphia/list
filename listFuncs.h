#include "stdio.h"

const size_t CONSTRUCT_SIZE = 5;

typedef 
    {
    int* data;
    int* next;
    int* prev;

    size_t head;
    size_t tail;    

    bool isSorted;

    size_t size;
    size_t capacity;
    }
    struct list;


enum listErrors
    {
    NO_ERROR,
    DATA_CALLOC_FAIL,
    NEXT_CALLOC_FAIL,
    PREV_CALLOC_FAIL,
    LIST_POINTER_SHIT,
    REALLOC_DATA_FAIL,
    REALLOC_NEXT_FAIL,
    REALLOC_PREV_FAIL
    };

listErrors listCtor (list* thisList);
listErrors fillConstructedList (list* thisList);

listErrors listCtor (list* thisList)
{
    if (thisList == nullptr)
        return LIST_POINTER_SHIT;

    thisList->data = (int*) calloc (CONSTRUCT_SIZE, sizeof(int));
    thisList->next = (int*) calloc (CONSTRUCT_SIZE, sizeof(int));
    thisList->prev = (int*) calloc (CONSTRUCT_SIZE, sizeof(int));

    if (thisList->data == nullptr)
        return DATA_CALLOC_FAIL;

    if (thisList->next == nullptr)
        return NEXT_CALLOC_FAIL;

    if (thisList->prev == nullptr)
        return PREV_CALLOC_FAIL;

    listErrors fillCheck = fillConstructedData (thisList);
    if (fillCheck != NO_ERROR)
        return fillCheck;

    thisList->isSorted = 1;
    thisList->size = 1;

    return NO_ERROR;
}

listErrors fillConstructedList (list* thisList)
{
    for (size_t i = 0; i < CONSTRUCT_SIZE; i++)
    {
        *(thisList->data + i) = 0;

        if (i == 0)
        {
            *(thisList->next) = 0;
            *(thisList->prev) = 0;
        }
        else
        {            
            *(thisList->next) = -1;
            *(thisList->prev) = -1;
        }

    }

    return NO_ERROR;
}

listErrors insertListBack (list* thisList, int data)
{
    //verifier
    
    if (thisList->size + 1 > thisList->capacity)
        

    *(data + tail + 1) = data;     

    //verifier
    return NO_ERROR;
}

listErrors reallocList (list* thisList)
{
    //verifier
    int* tempData = (int*) realloc ((thisList->capacity)*2*sizeof(int));
    if (thisList->data == nullptr)
        return REALLOC_DATA_FAIL;

    int* tempNext = (int*) realloc ((thisList->capacity)*2*sizeof(int));
    if (thisList->next == nullptr)
        return REALLOC_NEXT_FAIL;

    int* tempPrev = (int*) calloc ((thisList->capacity)*2*sizeof(int));
    if (thisList->prev == nullptr)
        return REALLOC_PREV_FAIL;
    
    //verifier 
    return NO_ERROR;
}


listErrors fillReallocedList (list* thisList)
{
    //verifier
    size_t place = thisList->head;
    size_t nextPlace = *(thisList->next + head);

    while (*(thisList->next + nextPlace) != 0)
    {
        
    }
    
    //verifier        
    return NO_ERROR;
}
