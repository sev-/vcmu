/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:05
*
*   Name            wcols.c -- Number of Column
*
*   Description     Determine number of columns for a window
*                   
*   Return Value    Returns number of columns
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wcols(wptr)
WPTR wptr;          /* Pointer to window to check                   */
    {
    COUNT bd;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wcols:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bd = (wptr->wctrl & BORDER ? 1 : 0);
    return(wptr->lower_c-wptr->upper_c+1-bd-bd);
    }

#endif


