/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:48
*
*   Name            wadjust.c  --  Window move and resize
*
*   Description     This is used to move and adjust the current window
*                   called by xgetone using wakey (window adjust key) or
*                   by user.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wadjust(wptr)
PFAST WPTR wptr;    /* Pointer to window to move                    */
    {
    COUNT lo_r,lo_c,up_r,up_c;
    COUNT bd;
    COUNT wpkarea();
    COUNT wmove();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wadjust:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & ACTIVE))
        return(-1);
    if(wptr->wctrl & NOADJ)
        return(-2);
    bd=(wptr->wctrl & BORDER ? 1 : 0);
    up_r=wptr->upper_r;
    up_c=wptr->upper_c;
    lo_r=wptr->lower_r;
    lo_c=wptr->lower_c;
    wpkarea(&up_r,&up_c,&lo_r,&lo_c,0,0,vcterm.rows-1,vcterm.cols-1,
            wptr->border_at,bd,wptr->depth,wptr->width,spkey.wakey);
    wmove(wptr,up_r,up_c,lo_r,lo_c);
    return(0);
    }

#endif



