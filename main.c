#include <moca.h>

#include <stdio.h>
#include <stdlib.h>

#include <mocagendef.h>
#include <mocaerr.h>
#include <mislib.h>
#include <oslib.h>
#include <mxmllib.h>


int main(int argc, char *argv[])
{
    SOCKET              fd;
    PROCESS_INFORMATION procinfo1,
                        procinfo2;
    SECURITY_ATTRIBUTES security1,
                        security2;
    STARTUPINFO         startupInfo1,
                        startupInfo2;

    osTCPListen(&fd, 9900, 10, TRUE);

    /* 
     *  1
     */

    security1.nLength              = sizeof security1;
    security1.lpSecurityDescriptor = NULL;
    security1.bInheritHandle       = TRUE;

    startupInfo1.cb          = sizeof startupInfo1;
    startupInfo1.lpReserved  = NULL;
    startupInfo1.lpDesktop   = NULL;
    startupInfo1.lpTitle     = NULL;
    startupInfo1.dwFlags     = STARTF_USESTDHANDLES;
    startupInfo1.cbReserved2 = 0;
    startupInfo1.lpReserved2 = NULL;

    if (!CreateProcess(NULL, "echo Hello", NULL, NULL, TRUE, 0L,
		       NULL, NULL, &startupInfo1, &procinfo1))
    {
        perror("CreateProcess");
	exit(1);
    }
   
    printf("Process Info Handle: %ld\n", procinfo1.hProcess);

    /* 
     *  2
     */

    security2.nLength              = sizeof security2;
    security2.lpSecurityDescriptor = NULL;
    security2.bInheritHandle       = TRUE;

    startupInfo2.cb          = sizeof startupInfo2;
    startupInfo2.lpReserved  = NULL;
    startupInfo2.lpDesktop   = NULL;
    startupInfo2.lpTitle     = NULL;
    startupInfo2.dwFlags     = STARTF_USESTDHANDLES;
    startupInfo2.cbReserved2 = 0;
    startupInfo2.lpReserved2 = NULL;

    if (!CreateProcess(NULL, "echo World", NULL, NULL, TRUE, 0L,
		       NULL, NULL, &startupInfo2, &procinfo2))
    {
        perror("CreateProcess");
	exit(1);
    }
   
    printf("Process Info Handle: %ld\n", procinfo2.hProcess);

    exit(0);
}
