/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:01
*
*   Name            wxxopen.c  --  Lowest window open
*
*   Description     This is the lowest window open. This function
*                   takes the information given it and calls wsetup()
*                   setting up all the variables for the window. Then it
*                   winit which opens the window and displays (if active).
*                   The only way to get more control of a window would be
*                   to call wsetup() and winit() directly.
*
*   Return Value    Returns -1 if error or a pointer to the window
*                   structure if no error.
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

WPTR wxxopen(up_r,up_c,lo_r,lo_c,title,ctrl,dth,wth,wc,fch)
COUNT up_r,up_c;    /* Upper row and column of window               */
COUNT lo_r,lo_c;    /* Lower row and column of window               */
TEXT *title;        /* Pointer to title of window                   */
COUNT ctrl;         /* Control byte for window                      */
COUNT dth,wth;      /* Width and depth of window                    */
COUNT wc;           /* Window color number                          */
COUNT fch;          /* Fill character to use in window              */
    {
    WPTR wptr;
    FAST COUNT bd;
    WPTR wsetup();
    COUNT winit();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wxxopen:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bd = (ctrl & BORDER ? 1 : 0);
    if( (up_r+(bd << 1) > lo_r) || (up_c+(bd << 1) > lo_c) || 
        (lo_c > vcterm.cols-1) || (lo_r > vcterm.rows-1) ||
        (up_r < 0) || (up_c < 0) )
        {
        vcerror = WCORD;
        return((WPTR) 0);
        }
    if(wc == -1)
            wc = wdoctrl->wno_opn % 10;
    if( (wptr = wsetup(NULLTEXT,ctrl,up_r,up_c,lo_r,lo_c,fch,wtable[wc].bg_t,
               wtable[wc].bd_t,wtable[wc].say_t,wtable[wc].get_t,
               wtable[wc].nget_t,wtable[wc].tit_t,title,dth,wth)) == 
                                          (WPTR) 0)
        return((WPTR) 0);
    if( (winit(wptr)) == -1)
        return((WPTR) 0);
    if( ctrl & COOKED )
        wptr->wtranfunc = wdoctrl->wcookfunc;
    return(wptr);
    }

#endif
