/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:33
*
*   Name            whbar.c  --  prints hortizonal bar
*
*   Description     Prints the hortizonal scroll bar for window
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID whbar(wp)
WPTR wp;            /* Pointer to window for hortizonal scroll bar  */
    {
    COUNT bd,viswdth,ttlwdth,pct;
        FAST COUNT barloc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "whbar:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bd=(wp->wctrl & BORDER) ? 1 : 0;
    viswdth = wp->lower_c - wp->upper_c + 1 - (bd*2);
    ttlwdth=wp->width-viswdth;
        if( ttlwdth == 0 )
            return;
    pct = (wp->cur_c * 100) / ttlwdth;
    barloc = ( pct * viswdth ) / 100;
    if( barloc == 0 )
        barloc++;
    if( (barloc == 1) && (wp->cur_c != 0) )
        barloc++;
    else
        if( (barloc == viswdth) && (wp->cur_c != ttlwdth) )
            barloc--;
    return;
    }

#endif


