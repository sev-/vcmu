/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:14
*
*   Name            wrd_scrn.c  --  Read the entire screen
*
*   Description     This function is called by vcinit to read
*                   the entire screen so it can be replaced later
*                   It also saves the screen to a backup screen
*                   so at any time the correct image can be achieved
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wrd_scrn()
    {
    FAST COUNT rowcnt=0;
    COUNT twidth;
    FAST TEXT *sptr;
    TEXT *vcalloc();
    VOID terror();
    VOID vca_get();
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wrd_scrn:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( wbscreen == NULLTEXT)
        if( (wbscreen = vcalloc((UCOUNT) (vcterm.rows*vcterm.cols) << 1,
                       (UCOUNT) sizeof(TEXT),vcdebug)) == NULLTEXT)
            terror((TEXT *)"Terminal Error in wrd_scrn");
    sptr = wscreen;
    twidth = vcterm.cols << 1;
    while(rowcnt < vcterm.rows)
        {
        vca_get(rowcnt,0,sptr,vcterm.cols);
        sptr += twidth;
        rowcnt++;
        }
    wdoctrl->wsrninit=0;
    vcmem(wbscreen,wscreen,(UCOUNT)vcterm.rows*twidth);
    }

#endif

