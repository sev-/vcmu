/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:42
*
*   Name            wsscroll.c  --  scroll the window blank the bottom row
*
*   Description     This is a low level used by a couple of function
*                   to scroll the window up line making the top lines
*                   disappear and adding blank lines to the bottom
*                   of the virtual window.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wsscroll(wptr,direction,no)
WPTR wptr;          /* Pointer to window to scroll                  */
COUNT direction;    /* direction to scroll                          */
COUNT no;           /* Number of lines to scroll                    */
    {
    TEXT nscrl;
    TEXT *cpntr,*cptr1;
    UCOUNT count;
    COUNT offset;
    COUNT twidth;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wsscroll:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((wptr == (WPTR)0) || !(wptr->wctrl & WOPEN))
        return;
    nscrl = no;
    twidth = wptr->width << 1;
    if(direction == vckey.cur_down)
        {
        count = ((wptr->depth-1)*wptr->width) << 1;
        cpntr = wptr->location + count;
        offset = ((wptr->depth-no-1)*wptr->width) << 1;
        cptr1 = wptr->location + offset;
        count = wptr->depth-no;
        while(count--)
            {
            vcmem(cpntr,cptr1,twidth);
            cpntr -= twidth;
            cptr1 -= twidth;
            }
        cpntr = wptr->location;
        }
    else
        {
        cpntr=wptr->location;
        offset = ((no*wptr->width) << 1);
        cptr1=wptr->location + offset;
        count=((wptr->depth-no)*wptr->width) << 1;
        vcmem(cpntr,cptr1,count);
        cpntr += count;
        }
    cptr1 = cpntr;
    count = 0;
    while(count < wptr->width)
        {
        *(cpntr++)=wptr->fill_ch;
        *(cpntr++)=wptr->bg_at;
        count++;
        }
    no--;
    if(no)
        {
        while(no--)
            {
            vcmem(cpntr,cptr1,(UCOUNT)twidth);
            cpntr += twidth;
            }
        }
    if(wptr->wctrl & NOAUTO)
        wptr->cur_r = max(0,(wptr->cur_r - nscrl));
    }
#endif


