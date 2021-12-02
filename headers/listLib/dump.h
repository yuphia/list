#ifndef DUMP_H

#define DUMP_H 1

#include "listLib.h"
#include "../logs/logs.h"

#define $$$ printf ("line: %d\n", __LINE__);

#define GET_INFO()\
    errorInfo info =\
                     {\
                      __LINE__,\
                      __PRETTY_FUNCTION__,\
                      __FILE__\
                     };

#define RENEW_INFO()\
    info.line = __LINE__;

#define DUMP_LIST()\
        GET_INFO();\
        errorMap verificatorMap = {0};\
        verificatorList (list, &verificatorMap);\
        bool isOk = dumpList (&verificatorMap, info, list);\
        if (isOk == false)\
                return FATAL_ERROR;


#define DUMP_LIST_END_OF_FUNC()\
        RENEW_INFO();\
        isOk = dumpList (&verificatorMap, info, list);\
        if (isOk == false)\
                return FATAL_ERROR;

#endif