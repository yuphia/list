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
    NO_ERROR,
    LOG_CANT_OPEN,
    LOG_CLOSE_ERROR,
    LOG_ALREADY_DEAD
};  

const size_t BUFF_SIZE = 1e6;

logErrors openLogs (LogFile* log);
logErrors closeLogs (LogFile log);

logErrors openLogs (LogFile* log)
{
    static bool wasCalled = 0;

    if (wasCalled == 1)
    {
        printf ("here\n");
        log->logPointer = fopen ("logs/myPersonalLogs/txt", "w");
        return NO_ERROR;
    }

    int logDescriptor = creat ("logs/myPersonalLogs.txt",
                               S_IREAD|S_IWRITE);

    if (logDescriptor == -1)
    {
        fprintf (stderr, "Error: couldn't create/open logfile\n");
        log->isFileOk = 0;
        return LOG_CANT_OPEN;
    }

    log->logPointer = fdopen (logDescriptor, "w");

    char* fileBuff = (char*)calloc (BUFF_SIZE, 1);
    setvbuf (log->logPointer, fileBuff, _IOFBF, BUFF_SIZE);
    printf ("bebra\n");
    wasCalled = 1;    

    return NO_ERROR;
}

logErrors closeLogs (LogFile log)
{
    if (log.isFileOk != 0)
        return LOG_ALREADY_DEAD;

    int closeReturn = fclose (log.logPointer);   

    if (closeReturn == EOF)
        return LOG_CLOSE_ERROR;

    return NO_ERROR;
}

#endif
