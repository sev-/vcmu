/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:34
*
*   Name            wshuffle.c  --  Bring window to top of active 
*                                   list
*
*   Description     Brings the window to the top of the window 
*                   link list
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wshuffle(wptr)
WPTR wptr;          /* Pointer to window to move to top of stack    */
    {
    COUNT opnback = FALSE;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wshuffle:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wptr->wctrl & WOPENBACK)
        {
        wptr->wctrl &= ~WOPENBACK;
        opnback = TRUE;
        }
    if(wdoctrl->wdhead == (WPTR) 0)
        {
        wdoctrl->wdhead = wptr;
        wdoctrl->wdtail = wptr;
        }
    if(opnback)
        {
        if(wptr != wdoctrl->wdhead)
            {
            wptr->wnext = wdoctrl->wdhead;
            wdoctrl->wdhead = wptr;
            if(wptr->wnext != (WPTR)0)
                wptr->wnext->wprevious = wptr;
            wptr->wprevious = (WPTR)0;
            }
        }
    else
        {
        if(wptr == wdoctrl->wdhead)
            if(wptr->wnext != (WPTR) 0)
                wdoctrl->wdhead = wptr->wnext;
        if(wptr != wdoctrl->wdtail)
            {
            if(wptr->wnext != (WPTR) 0)
                wptr->wnext->wprevious = wptr->wprevious;
            if(wptr->wprevious != (WPTR) 0)
                wptr->wprevious->wnext = wptr->wnext;
            wptr->wprevious = wdoctrl->wdtail;
            wdoctrl->wdtail->wnext = wptr;
            wptr->wnext = (WPTR) 0;
            wdoctrl->wdtail = wptr;
            }
        }
    }

#endif

