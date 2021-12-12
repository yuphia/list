#include <stdio.h>
#include <stdlib.h>

#include "listLib/listLib.h"

int main()
{
    List testList = {};
    listCtor (&testList, 18);

    listInsertAfterTail (&testList, 17);
    listInsertAfterTail (&testList, 16);
    listInsertAfterTail (&testList, 15);
    listInsertAfterTail (&testList, 14);
    listInsertAfterTail (&testList, 13);
    listInsertAfterTail (&testList, 12);
    listInsertAfterTail (&testList, 11);
    listInsertAfterTail (&testList, 10);
    listInsertAfterTail (&testList, 9);
    listInsertAfterTail (&testList, 8);
    listInsertAfterTail (&testList, 7);
    listInsertAfterTail (&testList, 6);
    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 4);
    listInsertAfterTail (&testList, 3);

    dumpDotList (&testList);

    listInsertAfterTail (&testList, 2);
    listInsertAfterTail (&testList, 1);
   
    listPrintLogic (&testList, stdout);

    listReverse (&testList);

    listPrintLogic (&testList, stdout);

    listPrinter (&testList, stdout);

    listSort (&testList);

    listPrinter (&testList, stdout);

    //listInsertBefore (&testList, 2, 10);

    //listSwap (&testList, 2, 3);
    //listDeleteElement (&testList, 2);    

    //listInsertBefore (&testList, 4, 10);
    //listDtor (&testList);
    listDtor (&testList);
    return 0;    
}
