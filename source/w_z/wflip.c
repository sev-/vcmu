/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:30
*
*   Name            wflip.c  --  Move intersection to scratch window
*
*   Description     This moves the block described by trow,tcol and brow,bcol
*                   to the scratch window (window 0) starting at 0,0.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wflip(toprow,topcol,botrow,botcol)
COUNT toprow,topcol;/* Upper row and column                         */
COUNT botrow,botcol;/* Lower row and column                         */
    {
    FAST COUNT loopcnt,cnt;
    COUNT width,wwidth,twidth;
    TEXT *cpntr,*sptr;
    WPTR wptr;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wflip:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wptr=  wdoctrl->wcutwdo;
    twidth = vcterm.cols << 1;
    width=botcol-topcol+1;
    cnt=botrow-toprow+1;
    cpntr=wptr->location;
    wwidth = wptr->width << 1;
    sptr = wscreen+(toprow*twidth)+(topcol << 1);
    width = width << 1;
    for(loopcnt=0;loopcnt < cnt;loopcnt++)
        {
        vcmem(cpntr,sptr,(UCOUNT)width);
        cpntr += wwidth;
        sptr += twidth;
        }
    }
#endif


