/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:56
*
*   Name            wbound.c  --  Determines if next Print is in Bounds
*
*   Description     Low level function used by various window functions
*                   to adjust winfo[number].cur_r and winfo[number].cur_c
*                   so that the next print on window will show on screen.
*                   Returns true if the window need to be redrawn and false
*                   if the window need not be redrawn.
*
*   Return Value    Return 1 for redraw or 0 if not necessary
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wbound(wptr)
PFAST WPTR wptr;    /* Pointer to window to check                   */
    {
    COUNT draw=0;
    FAST COUNT width,depth;
    COUNT bd,spread,tmp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wbound:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wptr->wctrl & NOAUTO)
        return(draw);
    bd=(wptr->wctrl & BORDER ? 1 : 0);
    width=wptr->lower_c-wptr->upper_c+1-(bd << 1);
    depth=wptr->lower_r-wptr->upper_r+1-(bd << 1);
    spread=(width < 8 ? 1 : 8);
    if(wptr->c_pos >= wptr->cur_c+width)
        {
        draw=1;
        if(wptr->c_pos < wptr->width-spread)
            wptr->cur_c=((tmp=wptr->c_pos+spread-width) < 0 ? 0 : tmp);
        else
            if(width < 2)
                wptr->cur_c=wptr->width-1;
            else
                wptr->cur_c=wptr->width-width+1;
        }
    if(wptr->c_pos < wptr->cur_c)
        {
        draw=1;
        if(wptr->c_pos < spread)
            wptr->cur_c=0;
        else
            wptr->cur_c=wptr->c_pos-spread;
        }
    if(wptr->r_pos >= wptr->cur_r+depth)
        {
        draw=1;
        wptr->cur_r=wptr->r_pos-depth+1;
        }
    if(wptr->r_pos < wptr->cur_r)
        {
        draw=1;
        wptr->cur_r=wptr->r_pos;
        }
    return(draw);
    }

#endif

