/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:26
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

VOID wfandn(wptr)
PFAST WPTR wptr;    /* Pointer to window to open                    */
    {
    COUNT upr,upc,lor,loc;
    COUNT no_frames,delay;
    FAST COUNT loopcnt;
    VOID wwtb();
    VOID wwrtdw();
    VOID vcdelay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wfandn:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    upr=wptr->upper_r;
    upc=wptr->upper_c;
    lor=wptr->lower_r;
    loc=wptr->lower_c;
    no_frames=min(((loc-upc+1)/2),(lor-upr+1));
    delay=wdoctrl->wdelay-(200*no_frames);
    for(loopcnt=1;loopcnt < no_frames;loopcnt++)
        {
        upc+=2;
        wwtb(wptr->upper_r,wptr->upper_c,++upr,upc,wptr->border_at);
        vcdelay(delay);
        }
    wwrtdw(wptr);
    }

#endif


