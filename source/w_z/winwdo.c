/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:42
*
*   Name            winwdo.c  --  Check to see if character on screen 
*
*   Description     This function checks to see if it is safe to 
*                   print a character on the screen. It could be
*                   possible that the printing is on a part of the
*                   window not shown on the screen
*
*   Return Value    Returns 1 - yes or 0 - do not print
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT winwdo(wptr,row,col)
PFAST WPTR wptr;    /* Pointer to window to check                   */
COUNT row,col;      /* Row and column to check                      */
    {
    FAST COUNT bd;
    COUNT yes=1;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "winwdo:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wptr->wctrl & NOAUTO)
        {
        bd=(wptr->wctrl & BORDER ? 1: 0);
        if( ((wptr->lower_r-bd) < row) || 
            ((wptr->upper_r+bd) > row) ||
            ((wptr->lower_c-bd) < col) ||
            ((wptr->upper_c+bd) > col)  )
            yes=0;
        }
    return(yes);
    }

#endif


