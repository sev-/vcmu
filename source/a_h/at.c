/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:42
*
*   Name            at.c  --  Address the cursor
*
*   Description     This moves the cursor to the desired row and
*                   column. If there is a window open it move to
*                   the window relative row,col.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID at(row,col)
PFAST COUNT row;    /* Row                                          */
PFAST COUNT col;    /* Column                                       */
    {
    VOID vcaddrc();
    VOID vccurs();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "at:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        {
        wdoctrl->wcurrent->r_pos=row;
        wdoctrl->wcurrent->c_pos=col;
        wplace_cur(wdoctrl->wcurrent);
        }
    else
        {
#endif
        vcaddrc(row,col);
/*
        vccurs(ON);
*/
#ifdef WINDOW
        }
#endif
    vcrow = row;
    vccol = col;
    }
