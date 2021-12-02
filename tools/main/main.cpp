#include <stdio.h>
#include <stdlib.h>

#include "listLib/listLib.h"

int main()
{
    List testList = {};
    listCtor (&testList, 3);

    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);
   




    //listInsertBefore (&testList, 2, 10);

    //listSwap (&testList, 2, 3);
    //listDeleteElement (&testList, 2);

    

    //listInsertBefore (&testList, 4, 10);
    //listDtor (&testList);
    listDtor (&testList);
    return 0;    
}
