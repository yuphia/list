#ifndef LOGS_H

#define LOGS_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct LogFile
{
    FILE* logPointer;
    bool isFileOk;
};

enum logErrors
{
    NO_ERROR_LOG,
    LOG_CANT_OPEN,
    LOG_CLOSE_ERROR,
    LOG_ALREADY_DEAD
};  

const size_t BUFF_SIZE = 1e6;

logErrors openLogs (LogFile* log);
logErrors closeLogs (LogFile* log);

#endif
