/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:52
*
*   Name            won()  --  Turn refresh on
*
*   Description     Turn refresh back on and refreshs the screen
*                   This should be used with woff() and should only
*                   be used with wcurrent.  You should not select
*                   a different screen or write to a different screen
*                   after you have used woff() until you use won().
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID won()
    {
    FAST WPTR wptr;
    COUNT wbound();
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "won:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wptr = wdoctrl->wcurrent;
    wdoctrl->wfreeze = FALSE;
    wbound(wptr);
    wstack(wptr);
    wwrtdw(wptr);
    wplace_cur(wptr);
    }

#endif


