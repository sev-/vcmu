/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:50
*
*   Name            wat.c  --  window at
*
*   Description     This function address the cursor at the desired
*                   location for the window {number}.
*
*   Return Value    Returns -1 if window not open
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

VOID wat(wptr,row,col)
PFAST WPTR wptr;    /* Pointer to window to address                 */
COUNT row,col;      /* Row and column to address                    */
    {
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wat:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( !(wptr->wctrl & WOPEN) )
        {
        vcerror = ATNOTOPEN;
        return;
        }
    wptr->r_pos = row;
    wptr->c_pos = col;
    if(wptr->c_pos >= wptr->width)
        {
        wptr->c_pos %= wptr->width;
        wptr->r_pos += 1;
        }
    if(wptr->r_pos >= wptr->depth)
        wptr->r_pos %= wptr->depth;
    if(wptr->c_pos < 0)
        {
        wptr->c_pos=wptr->width+(wptr->width % wptr->c_pos)-1;
        wptr->r_pos -= 1;
        }
    if(wptr->r_pos < 0)
        wptr->r_pos=wptr->depth+(wptr->depth % wptr->r_pos)-1;
    wplace_cur(wdoctrl->wcurrent);
    }

#endif
