/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:49
*
*   Name            wmove.c  --  Move Window
*
*   Description     This function moves window {number} to the new 
*                   location described by upr,upc and lor,loc. This  
*                   could be used to move a window or resize a window  
*                   under program control.  This function is called by 
*                   wadjust() and uses whide and wshow to do most of 
*                   its work.
*
*   Return Value    Return -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT wmove(wptr,up_r,up_c,lo_r,lo_c)
WPTR wptr;          /* Pointer to window to move                    */
PFAST COUNT up_r,up_c; /* New upper row and column                  */
PFAST COUNT lo_r,lo_c; /* New lower row and column                  */
    {
    COUNT doshow = FALSE;
    COUNT bd;
    COUNT whide();
    COUNT wbound();
    COUNT wshow();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wmove:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bd=(wptr->wctrl & BORDER ? 2 : 0);
    if( (up_r+bd > lo_r) || (up_c+bd > lo_c) || 
        (lo_c > vcterm.cols-1) || (lo_r > vcterm.rows-1) || 
        (up_r < 0) || (up_c < 0) )
        {
        vcerror = MVCOORD;
        return(-1);
        }
    if(wptr->wctrl & ACTIVE)
        {
        whide(wptr);
        doshow = TRUE;
        }
    lo_r=((lo_r-up_r+1-bd) < wptr->depth ? lo_r :
        up_r+wptr->depth+bd-1);
    lo_c=((lo_c-up_c+1-bd) < wptr->width ? lo_c :
        up_c+wptr->width+bd-1);
    wptr->upper_r=up_r;
    wptr->upper_c=up_c;
    wptr->lower_r=lo_r;
    wptr->lower_c=lo_c;
    wptr->cur_r=wptr->cur_c=0;
    wbound(wptr);
    if(doshow)
        wshow(wptr);
    return(0);
    }

#endif

