#ifndef DUMP_H

#define DUMP_H 1

#include "listLib.h"
#include "logs.h"

#define GET_INFO()\
    errorInfo info = {__PRETTY_FUNCTION__, __LINE__, __FILE__};

#define RENEW_INFO()\
    info.line = __LINE__;

#define DUMP_LIST()\
        dumpFunction (list, info);

#endif