/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:28
*
*   Name            wfanup.c  --  Fan up close
*
*   Description     Low level function that uses wwtb() to write a border
*                   from the lower right to the upper left.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wfanup(wptr)
WPTR wptr;          /* Pointer to window to close                   */
    {
    COUNT upr,upc,lor,loc;
    COUNT no_frames,delay;
    FAST COUNT loopcnt;
    VOID wwtb();
    VOID vcdelay();
    upr=wptr->upper_r;
    upc=wptr->upper_c;
    lor=wptr->lower_r;
    loc=wptr->lower_c;
    no_frames= min(((loc-upc+1)/2),(lor-upr+1));
    delay= wdoctrl->wdelay-(200*no_frames);
    for(loopcnt=1;loopcnt < no_frames;loopcnt++)
        {
        loc-=2;
        wwtb(upr,upc,--lor,loc,wptr->border_at);
        vcdelay(delay);
        }
    }

#endif


