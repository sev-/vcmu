/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:38
*
*   Name            wfandn.c  --  Fan down open
*
*   Description     Low level function that uses wwtb() to write a border
*                   from the upper left to the lower right.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wspread(wptr)
PFAST WPTR wptr;    /* Pointer to window to open                    */
    {
    COUNT upr,upc,lor,loc;
    COUNT no_frames,delay;
    FAST COUNT cur;
    FAST COUNT loopcnt;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    struct
        {
        COUNT up_r;
        COUNT up_c;
        COUNT lo_r;
        COUNT lo_c;
        } frames[40];
    VOID vcdelay();
    VOID wrtb();
    COUNT vcpee();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wspread:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    for(loopcnt = 0;loopcnt < 40;loopcnt++)
        {
        frames[loopcnt].up_r = 0;
        frames[loopcnt].lo_r = 0;    
        frames[loopcnt].up_c = 0;  
        frames[loopcnt].lo_c = 0;  
        }       
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
    if( (lor > (upr+1)) && (loc > (upc+1)))
        {
        cur = (loc-upc+1)/2;
        no_frames = cur + 1;
        delay = wdoctrl->wdelay-(200*no_frames);
        if(no_frames < 2)
            no_frames = loc-upc+1;
        cur += upc;
        for(loopcnt=1;loopcnt <= no_frames;loopcnt++)
            {
            wrtb(upr,cur,lor,min((cur+1),loc));
            vcdelay(delay);
            if(loopcnt % 2)
                {
                cur = cur - (2*loopcnt);
                cur = max(cur,upc);
                }
            else
                {
                cur = cur + (2*loopcnt);
                cur = min(cur,loc);
                }
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


