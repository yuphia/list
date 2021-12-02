#include <stdio.h>
#include <stdlib.h>

#include "listLib/listLib.h"

int main()
{
    List testList = {};
    listCtor (&testList, 3);

    listInsertAfterTail (&testList, 5);
    listInsertAfterTail (&testList, 6);

    listInsertBefore (&testList, 2, 10);
    //listDtor (&testList);
    listDtor (&testList);
    return 0;    
}
