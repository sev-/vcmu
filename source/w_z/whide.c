/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:36
*
*   Name            whide.c  --  Make window inactive
*
*   Description     This function hides or removes a window from the screen
*                   it keeps all the information in tact to restore the
*                   window at another time (using wshow()). The window can
*                   still be selected and printed on.
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT whide(wptr)
PFAST WPTR wptr;    /* Pointer to window to hide                    */
    {
    VOID vccurs();
    VOID wstack();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "whide:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & WOPEN))
        {
        vcerror = HIDNOTOPEN;
        return(-1);
        }
    if(!(wptr->wctrl & ACTIVE))
        return(0);
    wptr->wctrl &= ~ACTIVE;
    if(wdoctrl->wcurrent == wptr)
        vccurs(OFF);
    wstack((WPTR)0);
    (*wdoctrl->wclfunc)(wptr);
    return(0);
    }

#endif

