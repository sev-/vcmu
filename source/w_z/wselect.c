/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:29
*
*   Name            wselect.c  --  select a current window
*
*   synopsis        wselect(number);
*                   COUNT number;  Window number
*
*   Description     Selects window {number} as the current window
*                   (wcurrent) brings the window to the top of the
*                   stack on the screen (if active).
*
*   Return Value    Returns -1 if error or previously selected 
*                   window
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

WPTR wselect(wptr)
PFAST WPTR wptr;    /* Pointer to window to select                  */
    {
    WPTR prevwdo;
    VOID wshuffle();
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
    COUNT whidden();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wselect:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & WOPEN))
        {
        vcerror = SELNOTOPEN;
        return((WPTR) 0);
        }
    prevwdo = wdoctrl->wcurrent;
    if((wptr->wctrl & ACTIVE) && (wptr != wdoctrl->wdtail))
        {
        wshuffle(wptr);
        wstack(wptr);
        wwrtdw(wptr);
        wdoctrl->wcurrent = wptr;
        wplace_cur(wptr);
        }
    else
        {
        wdoctrl->wcurrent = wptr;
        if(whidden(wptr))
            wshuffle(wptr);
        wplace_cur(wptr);
        }
    vcrow = wptr->r_pos;
    vccol = wptr->c_pos;
    return(prevwdo);
    }

#endif
