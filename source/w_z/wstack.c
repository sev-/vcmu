/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:43
*
*   Name            wstack.c  --  Display the screen correctly
*
*   Description     This function redraws all of the window on
*                   the memory screen then uses the size and
*                   location of the window {number} to draw to
*                   the physical screen the corrected image.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wstack(wptr)
WPTR wptr;
    {
    FAST WPTR wp;
    VOID vcmem();
    VOID wscrn_blank();
    VOID wupdate();
    VOID wborder();
    VOID wshadow();
    VOID spfix();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wstack:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wdoctrl->wfreeze)
        return;
    wp = wdoctrl->wdhead;
    if((wptr != (WPTR)0) && !vcterm.mc)
        {
        while((wp != wptr) && (wp != (WPTR)0))
            wp = wp->wnext;
        }
    else
        {
        if(wbscreen != NULLTEXT)
            vcmem(wscreen,wbscreen,(UCOUNT)(vcterm.rows*vcterm.cols) << 1);
        else
            wscrn_blank();
        }
    while(wp != (WPTR) 0)
        {
        if((wp->wctrl & ACTIVE) && 
          ((wptr == (WPTR)0) || vcterm.mc || winter(wp,wptr)) )
            {
            wupdate(wp);
            if(wp->wctrl & BORDER)
                wborder(wp,-1);
            if(wp->wctrl & SHADOW)
                wshadow(wp);
            if(vcterm.mc)
                spfix();
            }
        wp = wp->wnext;
        }
    }

#endif

