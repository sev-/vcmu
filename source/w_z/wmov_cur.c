/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:47
*
*   Name            wmov_cur.c  --  Move the cursor
*
*   Description     Low level function used to move the cursor and
*                   check next location.
*
*   Return Value    Returns 1 to redraw the window
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wmov_cur(wptr,draw)
PFAST WPTR wptr;    /* Pointer to window to increment cursor        */
COUNT draw;         /* Current value of draw variable               */
    {
    VOID wsscroll();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wmov_cur:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wptr->c_pos < wptr->width-1)
        wptr->c_pos +=1;
    else
        {
        wptr->c_pos=0;
        if(wptr->r_pos < wptr->depth-1)
            wptr->r_pos+=1;
        else
            {
            if(wptr->wctrl & SCROLL)
                {
                draw=1;
                wsscroll(wptr,0,1);
                }
            else
                wptr->r_pos=0;
            }
        }
    return(draw);
    }
#endif


