/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:57
*
*   Name            wpickcl.c  --  Pick method of close
*
*   Description     This function decides how the window is to be
*                   closed and calls the correct function. Useful
*                   for animated closes only.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wpickcl(wptr)
PFAST WPTR wptr;    /* Pointer to window to close                   */
    {
    FAST COUNT choice;
#ifdef TERMINAL
    COUNT flow=0;
    COUNT vcpee();
    VOID vcflush();
#endif
    VOID wwrtup();
    VOID wzoomin();
    VOID wfanup();
    VOID wpullup();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wpickcl:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    choice = wptr->wctrl & CUSTOM;
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    switch(choice)
        {
        case STANDARD :
            wwrtup(wptr);
            break;
        case CENTER :
            wzoomin(wptr);
            break;
        case CURTAIN :
            wsquish(wptr);
            break;
        case CUSTOM :
            wpullup(wptr);
            break;
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif

