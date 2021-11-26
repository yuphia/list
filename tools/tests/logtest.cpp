#include "logs/logs.h"

int main()
{
    LogFile logTest = {nullptr, 1};
    
    openLogs (&logTest);
    
    if (logTest.isFileOk == 1)
        fprintf (logTest.logPointer, "bebroid\n");
    else
        printf ("Logs dead\n");

    closeLogs (&logTest);
    return 0;
}