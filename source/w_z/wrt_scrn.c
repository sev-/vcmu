/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:21
*
*   Name            wrt_scrn.c  --  write memory screen
*
*   Description     Writes the whole screen back from the memory
*                   screen.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wrt_scrn()
    {
    FAST COUNT rowcnt=0;
    COUNT twidth;
    FAST TEXT *sptr;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    VOID vca_put();
    VOID vcfree();
    VOID wplace_cur();
    VOID at();
    COUNT vcpee();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wrt_scrn:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    sptr = wscreen;
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    twidth = vcterm.cols << 1;
    while(rowcnt < vcterm.rows)
        {
        vca_put(rowcnt,0,sptr,vcterm.cols);
        sptr += twidth;
        rowcnt++;
        }
    if( wbscreen != NULLTEXT)
        {
        vcfree(wbscreen,vcdebug);
        wbscreen = NULLTEXT;
        }
    if(wdoctrl->wno_opn && !override)
        wplace_cur(wdoctrl->wcurrent);
    else
        at(vcrow,vccol);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif

