/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:08
*                
*   Name            wcutout.c  --  Remove window number from display order
*
*   Description     Removes the window number from wdisplay[] - the order
*                   in which windows are displayed on the screen
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wcutout(wptr)
PFAST WPTR wptr;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wcutout:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wptr == wdoctrl->wdhead)
        {
        wdoctrl->wdhead = wptr->wnext;
        if(wptr->wnext != (WPTR)0)
            wptr->wnext->wprevious = (WPTR) 0;
        wptr->wnext = (WPTR) 0;
        wptr->wprevious = (WPTR) 0;
        }
    if(wptr == wdoctrl->wdtail)
        {
        wdoctrl->wdtail = wptr->wprevious;
        if(wptr->wprevious != (WPTR) 0)
            wptr->wprevious->wnext = (WPTR) 0;
        wptr->wnext = (WPTR) 0;
        wptr->wprevious = (WPTR) 0;
        }
    if((wptr->wnext != (WPTR) 0) && (wptr->wprevious != (WPTR) 0))
        {
        wptr->wprevious->wnext = wptr->wnext;
        wptr->wnext->wprevious = wptr->wprevious;
        wptr->wnext = (WPTR) 0;
        wptr->wprevious = (WPTR) 0;
        }
    }

#endif

