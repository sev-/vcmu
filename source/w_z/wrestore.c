/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:18
*
*   Name            wrestore.c  --  Restore the orginal screen
*
*   Description     Restores the orginal screen as a first step
*                   in closing a window. This is to put the correct
*                   background before redrawing all of the windows.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wrestore(wptr)
WPTR wptr;
    {
    COUNT topcol,toprow,botrow,botcol;
    FAST COUNT rowcnt;
    COUNT twidth;
    COUNT width,depth;
    FAST TEXT *sptr,*bsptr;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wrestore:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    topcol=max(0,wptr->upper_c);
    toprow=max(0,wptr->upper_r);
    botrow=min(vcterm.rows-1,wptr->lower_r);
    botcol=min(vcterm.cols-1,wptr->lower_c);
    width=botcol-topcol+1;
    depth=botrow-toprow+1;
    width = width << 1;
    rowcnt = (toprow*twidth)+(topcol << 1);
    sptr = wscreen+rowcnt;
    bsptr = wbscreen+rowcnt;
    rowcnt = 0;
    while(rowcnt < depth)
        {
        vcmem(sptr,bsptr,(UCOUNT)width);
        sptr += twidth;
        bsptr += twidth;
        rowcnt++;
        }
    }

#endif

