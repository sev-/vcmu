/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:11
*
*   Name            setswdo.c  --  set status window
*
*   Description     Sets the status window
*
*   Return Value    Returns window pointer of previous status
*                   window
*                    
*
**/

#include <vcstdio.h>

WPTR setswdo(wptr)
WPTR wptr;
    {
    WPTR oldwno;
    oldwno = msgwdo;
    msgwdo = wptr;
    return(oldwno);
    }


