#include "stdio.h"

const size_t CONSTRUCT_SIZE = 5;

typedef 
    {
    int* data;
    int* next;
    int* prev;

    size_t head;
    size_t tail;    
    }
    struct list;


enum listErrors
    {
    NO_ERROR,
    DATA_CALLOC_FAIL,
    NEXT_CALLOC_FAIL,
    PREV_CALLOC_FAIL,
    LIST_POINTER_SHIT
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
