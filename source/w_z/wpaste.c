/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:55
*
*   Name            wpaste.c  --  Paste a section on window
*
*   Description     This function marks the area to paste from backup
*                   Screen then pastes the area in with wflop().
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wpaste(wptr,attr,key)
PFAST WPTR wptr;    /* Pointer to window to paste on                */
COUNT attr;         /* True send attribute also else no             */
COUNT key;          /* Additional exit key                          */
    {
    COUNT lo_r,lo_c,up_r,up_c;
    COUNT bd;
    COUNT wpkarea();
    VOID wflop();
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wpaste:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & ACTIVE) || wdoctrl->wfreeze || (wptr->wctrl & NOADJ))
        return;
    bd=(wptr->wctrl & BORDER ? 1 : 0);
    up_r=wptr->upper_r+bd;
    up_c=wptr->upper_c+bd;
    lo_r=min(wptr->lower_r-bd,up_r+wdoctrl->rowcut-1);
    lo_c=min(wptr->lower_c-bd,up_r+wdoctrl->colcut-1);
    wpkarea(&up_r,&up_c,&lo_r,&lo_c,wptr->upper_r+bd,wptr->upper_c+bd,
            wptr->lower_r-bd,wptr->lower_c-bd,wptr->border_at,0,
            wdoctrl->rowcut,wdoctrl->colcut,key);
    wflop(wptr,up_r,up_c,(lo_r-up_r+1),(lo_c-up_c+1),attr);
    wstack(wptr);
    wwrtdw(wptr);
    wplace_cur(wdoctrl->wcurrent);
    return;
    }
#endif


