/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:04
*
*   Name            wzoomin.c  --  Close to middle
*
*   Description     Low level function that uses wwtb() to write a border
*                   from the outside in. Used while closing window from
*                   CENTER.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wzoomin(wptr)
WPTR wptr;          /* Pointer to window to close                   */
    {
    FAST COUNT upc,loc,upr,lor;
    COUNT no_frames,delay;
    FAST COUNT loopcnt;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    VOID vcdelay();
    VOID wrtb();
    VOID vcflush();
    COUNT vcpee();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wzoomin:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
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
    if((lor > upr) && (loc > upc))
        {
        no_frames=min(((loc-upc+1)/2),(lor-upr+1));
        no_frames/=2;
        delay=wdoctrl->wdelay-(200*no_frames);
        wrtb(upr,upc,lor,loc);
        wrtb(upr,upc+1,lor,upc+1);
        wrtb(upr,loc-1,lor,loc-1);
        for(loopcnt=1;loopcnt <= no_frames;loopcnt++)
            {
            upc+=2;
            loc-=2;
            vcdelay(delay);
            wrtb(++upr,upc,--lor,loc);
            wrtb(upr,upc+1,lor,upc+1);
            wrtb(upr,loc-1,lor,loc-1);
            }
        }
    else
        wrtb(upr,upc,lor,loc);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif


