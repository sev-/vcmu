/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:31
*
*   Name            vcprtchr.c  --  send chr to printer
*
*   Description     This function provides a simple method for
*                   sending a character to the printer
*
*   Return Value    VOID
*                    
*
**/

#include <vcstdio.h>

VOID vcprtchr(ch)
TEXT ch;            /* Character to be printed                      */
    {
    if(prthandle != (FILE *)0)
        fwrite(&ch,sizeof(ch),1,prthandle);
    }

