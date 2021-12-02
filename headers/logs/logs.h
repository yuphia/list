#ifndef LOGS_H

#define LOGS_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PRINT_SPLITTER() fprintf (logs.logPointer, "\n\n============================================================================"\
                                                    "\n\n")
#define PRINT_LOGS(text)\
    fprintf (logs.logPointer, text) 

enum logErrors
{
    NO_ERROR_LOG,
    LOG_CANT_OPEN,
    LOG_CLOSE_ERROR,
    LOG_ALREADY_DEAD
};  

struct LogFile
{
    FILE* logPointer;
    bool isFileOk;
    char* fileBuff;
    logErrors err;
};

const size_t BUFF_SIZE = 1e7;

logErrors openLogs (LogFile* log);
logErrors closeLogs (LogFile* log);

#endif
