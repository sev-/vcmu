/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:33
*
*   Name            wshow.c  --  Show an inactive window
*
*   Description     Display an inactive window. The window could be
*                   inactive by using whide or by being opened without
*                   ACTIVE added to the control byte.  This function
*                   moves the window to the top of the stack but does
*                   not make the window the current window (wcurrent);
*
*   Return Value    Returns -1 if window already active
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT wshow(wptr)
PFAST WPTR wptr;    /* Pointer to window to show                    */
    {
    COUNT whidden();
    VOID wshuffle();
    VOID wstack();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wshow:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & WOPEN))
        {
        vcerror=SHOWNOTOPEN;
        return(-1);
        }
    if(wptr->wctrl & ACTIVE)
        return(0);
    wptr->wctrl |= ACTIVE;
    if(!whidden(wptr))
        {
        wdoctrl->wno_active += 1;
        wshuffle(wptr);
        }
    wstack(wptr);
    (*wdoctrl->wopnfunc)(wptr);
    wplace_cur(wdoctrl->wcurrent);
    return(0);
    }

#endif

