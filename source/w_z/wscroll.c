/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:28
*
*   Name            wscroll.c  --  Scroll the window
*
*   synopsis        wscroll(number,direction,amount);
*                   COUNT number;    Window number to Scroll
*                   COUNT direction; Direction to move window
*                   COUNT amount;    Number of units to move
*
*   Description     This function takes the window {number} and
*                   adjusts the upper left display cord.
*                   (winfo[number].cur_r, winfo[number].cur_c)
*                   so you get the effect of scrolling.
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT wscroll(wptr,direction,amount)
PFAST WPTR wptr;    /* Pointer to window to scroll                  */
COUNT direction;    /* Direction to scroll                          */
COUNT amount;       /* Number of columns or rows to scroll          */
    {
    COUNT work,bd,row,col,retval=0;
    VOID wstack();
    VOID wwrtdw();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wscroll:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & WOPEN))
        {
        vcerror = SCRNOTOPEN;
        return(-1);
        }
    bd = ( wptr->wctrl & BORDER ? 1 : 0);
    col = wptr->cur_c;
    row = wptr->cur_r;
    if(direction == vckey.cur_up)
        wptr->cur_r = max(0,wptr->cur_r-amount);
    if(direction == vckey.cur_down)
        {
        work = wptr->lower_r-wptr->upper_r+1-(bd << 1);
        wptr->cur_r = min(wptr->depth-work,wptr->cur_r+amount);
        }
    if(direction == vckey.cur_right)
        {
        work = wptr->lower_c-wptr->upper_c+1-(bd << 1);
        wptr->cur_c = min(wptr->width-work,wptr->cur_c+amount);
        }
    if(direction == vckey.cur_left)
        wptr->cur_c = max(0,wptr->cur_c-amount);
    if( ((row != wptr->cur_r) || (col != wptr->cur_c)) && 
         (wptr->wctrl & ACTIVE) )
       {
       wstack(wptr);
       wwrtdw(wptr);
       }
    return(retval);
    }

#endif

