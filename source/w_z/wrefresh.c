/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:16
*
*   Name            wrefresh.c  --  refresh window screen
*
*   Description     Writes the whole screen back from the memory
*                   screen.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wrefresh(flag)
COUNT flag;        /* True means clear the screen  */
    {
    FAST COUNT rowcnt=0;
    COUNT twidth;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    FAST TEXT *sptr;
    VOID wstack();
    COUNT vcpee();
    VOID xerase();
    VOID vca_put();
    VOID vcflush();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wrefresh:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wdoctrl->wfreeze = FALSE;
    wstack((WPTR)0);
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    if(flag)
        {
        override = TRUE;
        xerase(normattr);
        override = FALSE;
        }
    sptr = wscreen;
    twidth = vcterm.cols << 1;
    while(rowcnt < vcterm.rows)
        {
        vca_put(rowcnt,0,sptr,vcterm.cols);
        sptr += twidth;
        rowcnt++;
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    wplace_cur(wdoctrl->wcurrent);
    return(0);
    }

#endif

