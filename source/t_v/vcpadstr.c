/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:23
*
*   Name            vcpadstr.c  --  Pad string with nulls  
*
*   Description     Pad string with nulls
*                   
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

TEXT vcpadbuf[128];
COUNT vcpadcnt = 0;

COUNT vcpadstr(ch)
TEXT ch;
    {
    if(ch == AT_ON)
        ch = 0;        
    if(vcpadcnt < 127)
        vcpadbuf[vcpadcnt++] = ch;
    return(0);
    }

#endif


