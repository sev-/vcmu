/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:18
*
*   Name            werabox.c  --  Erase box with attribute
*
*   Description     Erases a box (or block) of the screen to attribute.
*                   If -1 is specified for attribute then winfo[number].bg_at
*                   is used. If window is off (woff) will turn window on (won)
*                   This function can be called but programmer should call
*                   erabox() or xerabox().
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID werabox(wptr,up_r,up_c,lo_r,lo_c,attr)
WPTR wptr;          /* Pointer to window to clear                   */
COUNT up_r,up_c;    /* Upper left corner                            */
COUNT lo_r,lo_c;    /* Lower right corner                           */
COUNT attr;         /* Attribute for cleared area                   */
    {
    FAST COUNT cnt;
    COUNT depth,width,nrow;
    FAST TEXT *cpntr;
    TEXT *ptr;
    COUNT offset;
    VOID vcmem();
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "werabox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(attr == -1)
        attr=wptr->bg_at;
    up_r=max(up_r,0);
    up_c=max(up_c,0);
    lo_c=min(lo_c,(wptr->width-1));
    lo_r=min(lo_r,(wptr->depth-1));
    width=lo_c-up_c+1;
    depth=lo_r-up_r+1;
    offset = (up_r*wptr->width+up_c) << 1;
    cpntr=wptr->location+offset;
    nrow = wptr->width << 1;
    ptr = cpntr;
    for(cnt=0;cnt<width;cnt++)
        {
        *(cpntr++)=wptr->fill_ch;
        *(cpntr++)=attr;
        }
    cpntr += ((wptr->width - width) << 1);
    width = width << 1;
    for(cnt=1;cnt < depth;cnt++)
        {
        vcmem(cpntr,ptr,width);
        cpntr += nrow;
        }
    if(wptr->wctrl & ACTIVE)
        {
        wstack(wptr);
        wwrtdw(wptr);
        wplace_cur(wdoctrl->wcurrent);
        }
    }

#endif


