/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:39
*
*   Name            winit.c  --  Start Window
*
*   Description     This function opens a window. By using the 
*                   winfo[] for the necessary information about the
*                   window. If the window is active it calls the 
*                   programs necessary to open and display on the
*                   screen 
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT winit(wptr)
PFAST WPTR wptr;    /* Pointer to window to start                   */
    {
    VOID wscrn_blank();
    VOID wclr();
    VOID wshuffle();
    VOID wstack();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "winit:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wdoctrl->wsrninit)
        wscrn_blank();
    if(wptr->wctrl & WOPEN)
        {
        vcerror=CUROPEN;
        return(-1);
        }
    else
        wptr->wctrl |= WOPEN;
    wclr(wptr,wptr->bg_at);
    if((wdoctrl->wcurrent == (WPTR)0) || !(wptr->wctrl & WOPENBACK))
        wdoctrl->wcurrent = wptr;
    if(wptr->wctrl & ACTIVE)
        {
        wdoctrl->wno_active += 1;
        wshuffle(wptr);
        wstack(wptr);
        (*wdoctrl->wopnfunc)(wptr);
        wplace_cur(wptr);
        }
    wdoctrl->wno_opn += 1;
    return(0);
    }

#endif

