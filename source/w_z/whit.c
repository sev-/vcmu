/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:37
*
*   Name            whit.c  --  Check Screen if character ok 
*
*   Description     This function checks to see if it is safe to 
*                   print a character on the screen. It could be
*                   possible that a window is covering the location
*                   (row,col) where the character is to be printed. 
*
*   Return Value    Returns the current status of the draw variable
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT whit(wptr,row,col)
WPTR wptr;          /* Pointer to window to check                   */
PFAST COUNT row,col;/* Row and column to check                      */
    {
    FAST WPTR wp;
    COUNT ok=1;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "whit:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(wdoctrl->wbgdisplay)
        {
        wp = wptr->wnext;
        while((wp != (WPTR) 0) && ok)
            {
            if( (wp->wctrl & ACTIVE) && 
                ((wp->lower_r >= row) && (wp->upper_r <= row)) &&
                ((wp->lower_c >= col) && (wp->upper_c <= col))  )
                    ok=0;
            wp = wp->wnext;
            }
        }
    return(ok);
    }

#endif


