/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:03
*
*   Name            vcaddrc.c  --  Address the cursor
*
*   Description     This addresses the cursor to the location
*                   row,col.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcaddrc(row,col)
PFAST COUNT row,col;/* Location to move cursor                      */
    {
#ifdef IBM
    VOID vcint();
#endif
    VOID term_at();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcaddrc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef IBM
#ifdef TERMINAL
    if(vctio != 5)
        {
#endif
        struct VCREGS wdiregs,wdoregs;
        wdiregs.ax = 0x0200;
        wdiregs.dx = row*256+col;
        wdiregs.bx = 0;
        vcint(16,&wdiregs,&wdoregs);
#ifdef TERMINAL
        }
    else
        term_at(row,col);
#endif
#endif
#ifdef TERMONLY
    term_at(row,col);
#endif
#ifdef OS2
#ifdef TERMINAL
    if(vctio == 5)
        term_at(row,col);
    else
#endif
        VioSetCurPos(row,col,0);
#endif
    }


