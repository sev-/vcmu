/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:07
*
*   Name            wcut.c  --  Cut a section of window
*
*   Description     This function marks the area to cut to backup
*                   Screen and blanks the area if clear TRUE
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wcut(wptr,clear,key)
WPTR wptr;          /* Pointer to window to cut from                */
COUNT clear;        /* True = erase area                            */
COUNT key;          /* Additional exit key                          */
    {
    COUNT lo_r,lo_c,up_r,up_c;
    COUNT row,col,bd;
    COUNT wpkarea();
    VOID wflip();
    VOID werabox();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wcut:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & ACTIVE) || wdoctrl->wfreeze ||
                                        (wptr->wctrl & NOADJ))
        return;
    bd=(wptr->wctrl & BORDER ? 1 : 0);
    up_r=wptr->upper_r+bd;
    up_c=wptr->upper_c+bd;
    lo_r=wptr->lower_r-bd;
    lo_c=wptr->lower_c-bd;
    row = lo_r-up_r+1;
    col = lo_c-up_c+1;
    wpkarea(&up_r,&up_c,&lo_r,&lo_c,up_r,up_c,lo_r,lo_c,wptr->border_at,
            0,row,col,key);
    wflip(up_r,up_c,lo_r,lo_c);
    wdoctrl->rowcut=lo_r-up_r+1;
    wdoctrl->colcut=lo_c-up_c+1;
    if(clear)
        {
        up_r=wptr->cur_r+up_r-wptr->upper_r-bd;
        up_c=wptr->cur_c+up_c-wptr->upper_c-bd;
        lo_r=up_r+wdoctrl->rowcut-1;
        lo_c=up_c+wdoctrl->colcut-1;
        werabox(wptr,up_r,up_c,lo_r,lo_c,wptr->bg_at);
        }
    return;
    }
#endif


