/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:39
*
*   Name            vcprtstr.c  --  prints a string
*
*   Description     This function prints a NULL terminated string
*                   to the printer
*
*   Return Value    VOID
*                    
*
**/

#include <vcstdio.h>

COUNT vcprtstr(str)
TEXT *str;          /* Pointer to string to be printed              */
    {
    COUNT strlen();
    if(prthandle != (FILE *)0)
        return(fwrite(str,sizeof(TEXT),strlen(str),prthandle));
    }


