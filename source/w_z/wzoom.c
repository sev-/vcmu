/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:02
*
*   Name            wzoom.c  --  Open from middle
*
*   Description     Low level function that uses wwtb() to write a border
*                   from the middle out. Used while opening window from
*                   center. 
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wzoom(wptr)
WPTR wptr;          /* Pointer to window to zoom open               */
    {
    COUNT upr,upc,lor,loc;
    COUNT no_frames,delay;
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
    vcdebug = (TEXT *) "wzoom:";
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
    if( (lor > upr) && (loc > upc))
        {
        no_frames=min(((loc-upc+1)/2),(lor-upr+1));
        no_frames/=2;
        delay=wdoctrl->wdelay-(200*no_frames);
        if(no_frames < 2)
            no_frames=min((loc-upc+1),(lor-upr+1));
        for(loopcnt=1;loopcnt <= no_frames;loopcnt++)
            {
            frames[loopcnt].up_r = ++upr;
            frames[loopcnt].lo_r = --lor;
            upc+=2;  loc-=2;
            frames[loopcnt].up_c = upc;
            frames[loopcnt].lo_c = loc;
            }
        for(loopcnt=no_frames; loopcnt > 0; loopcnt--)
            {
            wrtb(frames[loopcnt].up_r,frames[loopcnt].up_c,
                 frames[loopcnt].lo_r,frames[loopcnt].lo_c);
            wrtb(frames[loopcnt].up_r,frames[loopcnt].up_c+1,
                 frames[loopcnt].lo_r,frames[loopcnt].up_c+1);
            wrtb(frames[loopcnt].up_r,frames[loopcnt].lo_c-1,
                 frames[loopcnt].lo_r,frames[loopcnt].lo_c-1);
            vcdelay(delay);
            }
        wrtb(frames[1].up_r-1,frames[1].up_c-2,
             frames[1].lo_r+1,frames[1].lo_c+2);
        wrtb(frames[1].up_r,frames[1].up_c-1,
             frames[1].lo_r,frames[1].up_c-1);
        wrtb(frames[1].up_r,frames[1].lo_c+1,
             frames[1].lo_r,frames[1].lo_c+1);
        }
    else
        wrtb(upr,upc,lor,loc);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif


