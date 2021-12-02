#include "logs/logs.h"
#include "listLib/dump.h"

logErrors openLogs (LogFile* log)
{
    static bool wasCalled = 0;

    if (wasCalled == 1)
    {
        log->logPointer = fopen ("myPersonalLogs.txt", "a");
        log->fileBuff = (char*)calloc (BUFF_SIZE, 1);
        setvbuf (log->logPointer, log->fileBuff, _IOFBF, BUFF_SIZE);
        
        log->isFileOk = 1;
        return NO_ERROR_LOG;
    }

    int logDescriptor = creat ("myPersonalLogs.txt",
                               S_IREAD|S_IWRITE);

    if (logDescriptor == -1)
    {
        fprintf (stderr, "Error: couldn't create/open logfile\n");
        log->isFileOk = 0;
        return LOG_CANT_OPEN;
    }

    log->logPointer = fdopen (logDescriptor, "w");
    log->fileBuff = (char*)calloc (BUFF_SIZE, 1);
    setvbuf (log->logPointer, log->fileBuff, _IOFBF, BUFF_SIZE);

    wasCalled = 1;    

    return NO_ERROR_LOG;
}

logErrors closeLogs (LogFile* log)
{
    if (log->isFileOk == 0)
    {
        return LOG_ALREADY_DEAD;
    }
    //fflush (log->logPointer);

    int closeReturn = fclose (log->logPointer);   

    free (log->fileBuff);

    log->isFileOk = 0;

    if (closeReturn == EOF)
        return LOG_CLOSE_ERROR;

    return NO_ERROR_LOG;
}