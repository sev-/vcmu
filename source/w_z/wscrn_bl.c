/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:26
*
*   Name            wscrn_bl.c  --  blank memory image of real screen
*
*   Description     Blanks the memory screen and the backup image of
*                   the memory screen.  This function is to prevent
*                   extra work when dealing with a screen that can
*                   not be read.  This function puts the screen in
*                   a predictable state with a attribute byte between
*                   a SPACE character. 
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wscrn_blank()
    {
    FAST COUNT count=1;
    FAST TEXT *cptr;
    COUNT twidth;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wscrn_blank:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wdoctrl->wsrninit=0;
    cptr = wscreen;
    twidth = vcterm.cols << 1;
    while(count<=vcterm.cols)
        {
        *(cptr++)=' ';
        *(cptr++)=normattr;
        count++;
        }
    count = 1;
    while(count < vcterm.rows)
        {
        vcmem(cptr,wscreen,twidth);
        cptr += twidth;
        count++;
        }
    }

#endif
