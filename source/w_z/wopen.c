/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:53
*
*   Name            wopen.c  --  Highest window open
*
*   Description     This is the easiest window open. This function
*                   takes the upper corner, lower corner and title
*                   and adds default values and calls wxopen(). It
*                   returns the window number or -1 if an error has
*                   occured.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

#ifdef WINDOW

WPTR wopen(up_r,up_c,lo_r,lo_c,title)
PFAST COUNT up_r,up_c; /* Upper row and column for window           */
PFAST COUNT lo_r,lo_c; /* Lower row and column for window           */
TEXT *title;        /* Pointer to title for window or NULL          */
    {
    WPTR wxopen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wopen:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(wxopen(up_r,up_c,lo_r,lo_c,title,wdoctrl->wstdctrl,0,0));
    }
#endif

