#include "logs.h"

logErrors openLogs (LogFile* log)
{
    static bool wasCalled = 0;

    if (wasCalled == 1)
    {
        printf ("here\n");
        log->logPointer = fopen ("logs/myPersonalLogs/txt", "w");
        return NO_ERROR_LOG;
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

    return NO_ERROR_LOG;
}

logErrors closeLogs (LogFile* log)
{
    if (log->isFileOk != 0)
        return LOG_ALREADY_DEAD;

    int closeReturn = fclose (log->logPointer);   

    log->isFileOk = 0;

    if (closeReturn == EOF)
        return LOG_CLOSE_ERROR;

    return NO_ERROR_LOG;
}