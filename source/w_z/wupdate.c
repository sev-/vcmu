/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:49
*
*   Name            wupdate.c  --  Update memory screen
*
*   Description     This function is used everywhere it purpose is
*                   to move the portion of the virtual window starting
*                   at winfo[number].cur_r,winfo[number].cur_c to
*                   the memory screen. It adjusts these number if they
*                   are not correct.
*
*   Return Value    VOID
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

VOID wupdate(wptr)
WPTR wptr;          /* Pointer to window to update                  */
    {
    FAST COUNT rowcnt;
    COUNT bd,twidth;
    COUNT width,depth,wdowidth;
    COUNT offset;
    FAST TEXT *cpntr,*sptr;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wupdate:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    bd=(wptr->wctrl & BORDER ? 1 : 0);
    width=wptr->lower_c-wptr->upper_c+1-bd-bd;
    depth=wptr->lower_r-wptr->upper_r+1-bd-bd;
    if((width < 0) || (depth < 0))
        return;
    if((width+wptr->cur_c) > wptr->width)
        wptr->cur_c=wptr->width-width;
    if((depth+wptr->cur_r) > wptr->depth)
        wptr->cur_r=wptr->depth-depth;
    if(wptr->cur_r < 0)
        wptr->cur_r=0;
    if(wptr->cur_c < 0)
        wptr->cur_c=0;
    offset = ( (wptr->cur_r*wptr->width+wptr->cur_c) << 1);
    cpntr=wptr->location + offset;
    width = width << 1;
    sptr = wscreen+((wptr->upper_r+bd)*twidth)+((wptr->upper_c+bd) << 1);
    wdowidth = wptr->width << 1;
    for(rowcnt=0;rowcnt < depth;rowcnt++)
        {
        vcmem(sptr,cpntr,(UCOUNT)width);
        cpntr += wdowidth;
        sptr += twidth;
        }
    return;
    }

#endif

