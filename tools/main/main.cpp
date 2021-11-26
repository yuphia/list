#include <stdio.h>
#include <stdlib.h>

#include "listLib.h"

int main()
{
    List testList = {};
    listCtor (&testList, 3);
    listPrinter (&testList);

    listDtor (&testList);

    return 0;    
}
