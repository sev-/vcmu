/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:54
*
*   Name            wwrtup.c  --  Write up the screen
*
*   Description     This function writes a block of text from the 
*                   memory screen to the physical screen from the
*                   bottom up. The area is described by the size
*                   of window number passed to the function. for
*                   terminal applications it turn the cursor off
*                   then back on.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wwrtup(wptr)
WPTR wptr;          /* Pointer to window area to write              */
    {
    FAST COUNT rowcnt;
    COUNT width,twidth;
    COUNT row,col;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    FAST TEXT *sptr;
    COUNT vcpee();
    VOID vca_put();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wwrtup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wdoctrl->wfreeze)
        return;
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    twidth = vcterm.cols << 1;
    if(wptr->wctrl & SHADOW)
        {
        row = min((wptr->lower_r+1),(vcterm.rows-1));
        col = min((wptr->lower_c+2),(vcterm.cols-1));
        }
    else
        {
        row = wptr->lower_r;
        col = wptr->lower_c;
        }
    width = col - wptr->upper_c+1;
    sptr = wscreen+(row*twidth)+(wptr->upper_c << 1);
    for(rowcnt = row;rowcnt>=wptr->upper_r;rowcnt--)
        {
        vca_put(rowcnt,wptr->upper_c,sptr,width);
        sptr -= twidth;
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif

