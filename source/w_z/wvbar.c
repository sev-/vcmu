/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:50
*
*   Name            wvbar.c  --  prints vertical bar
*
*   Description     Prints the vertical scroll bar for a window
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wvbar(wp)
WPTR wp;            /* Pointer to window for vertical scroll bar    */
    {
    COUNT bd,visdpth,ttldpth,pct;
    FAST COUNT barloc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wvbar:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bd=(wp->wctrl & BORDER) ? 1 : 0;
    visdpth = wp->lower_r - wp->upper_r + 1 - (bd*2);
    ttldpth=wp->depth-visdpth;
        if( ttldpth == 0 )
            return;
    pct = (wp->cur_r * 100) / ttldpth;
    barloc = ( pct * visdpth ) / 100;
    if( barloc == 0 )
        barloc++;
    if( (barloc == 1) && (wp->cur_r != 0) )
        barloc++;
    else
        if( (barloc == visdpth) && (wp->cur_r != ttldpth) )
            barloc--;
    return;
    }
#endif


