/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:19
*
*   Name            wrows.c -- Number of rows
*
*   Description     Determine number of rows for a window
*                   
*   Return Value    Returns number of rows
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wrows(wptr)
WPTR wptr;          /* Pointer to window to check                   */
    {
    COUNT bd;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wrows:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bd = (wptr->wctrl & BORDER ? 1 : 0);
    return(wptr->lower_r-wptr->upper_r+1-bd-bd);
    }
#endif


