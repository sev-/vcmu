/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:58
*
*   Name            wpickopn.c  --  Pick method of open
*
*   Description     This function decides how the window is to be
*                   opened and calls the correct function. Useful
*                   for animated opens only.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wpickopn(wptr)
PFAST WPTR wptr;    /* Pointer to window to open                    */
    {
    FAST COUNT choice;
#ifdef TERMINAL
    COUNT flow=0;
    COUNT vcpee();
    VOID vcflush();
#endif
    VOID wwrtdw();
    VOID wzoom();
    VOID wfandn();
    VOID wpulldn();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wpickopn:";
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
            wwrtdw(wptr);
            break;
        case CENTER :
            wzoom(wptr);
            break;
        case CURTAIN :
            wspread(wptr);
            break;
        case CUSTOM :
            wpulldn(wptr);
            break;
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif

