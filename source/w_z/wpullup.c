/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:08
*
*   Name            wpullup.c  --  Pull up from corner
*
*   Description     This is a window close function that draws a 
*                   tempory border from the lower right corner to
*                   the upper left corner.  The global variable
*                   wdelay can be used to make the close faster or
*                   slower to adjust for diferent screen speeds.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wpullup(wptr)
WPTR wptr;          /* Pointer to window to close                   */
    {
    COUNT upr,upc,lor,loc,width;
    COUNT no_frames,delay,twidth;
    FAST COUNT loopcnt;
    FAST TEXT *sptr;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    VOID scrollup();
    VOID vca_put();
    VOID vcdelay();
    COUNT vcpee();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wpullup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    twidth = vcterm.cols+vcterm.cols;
    upr = wptr->upper_r;
    upc = wptr->upper_c;
    if(wptr->wctrl & SHADOW)
        {
        lor = min((wptr->lower_r+1),(vcterm.rows-1));
        loc = min((wptr->lower_c+2),(vcterm.cols-1));
        }
    else
        {
        lor = wptr->lower_r;
        loc = wptr->lower_c;
        }
    width = loc - upc + 1;
    no_frames = lor - upr + 1;
    delay=wdoctrl->wdelay/2-(no_frames*width);
    sptr = wscreen+(lor*twidth)+(upc << 1);
    for(loopcnt=0;loopcnt < no_frames;loopcnt++)
        {
        if(loopcnt < no_frames-1)
            scrollup(upr,upc,lor-loopcnt,loc,1,normattr);
        vca_put(lor-loopcnt,upc,sptr,width);
        sptr -= twidth;
        vcdelay(delay);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif


