/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:34
*
*   Name            whidden.c  --  Check if window is hidden
*
*   Description     This function checks to see if the file
*                   was hidden using whide().
*
*   Return Value    Returns True if hidden
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT whidden(wptr)
PFAST WPTR wptr;    /* Pointer to window to check                   */
    {
    FAST WPTR wp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "whidden:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wp = wdoctrl->wdhead;
    while(wp != (WPTR) 0)
        if(wp == wptr)
            return(1);
        else
            wp = wp->wnext;
    return(0);
    }

#endif

