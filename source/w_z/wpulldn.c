/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:06
*
*   Name            wpulldn.c  --  Pull down from corner
*
*   Description     This is a window open function that draws a 
*                   tempory border from the upper left corner to
*                   the lower right corner.  The global variable
*                   wdelay can be used to make the open faster or
*                   slower to adjust for diferent screen speeds.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wpulldn(wptr)
WPTR wptr;          /* Pointer to window to open                    */
    {
    COUNT upr,upc,lor,loc,width;
    COUNT no_frames,delay,twidth;
    FAST COUNT loopcnt;
    FAST TEXT *sptr;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    VOID scrolldn();
    VOID vca_put();
    VOID vcdelay();
    VOID vcflush();
    COUNT vcpee();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wpulldn:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    twidth = vcterm.cols << 1;
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
        if(loopcnt > 0)
            scrolldn(upr,upc,upr+loopcnt,loc,1,normattr);
        vca_put(upr,upc,sptr,width);
        sptr -= twidth;
        vcdelay(delay);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif


