/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:59
*
*   Name            wxopen.c  --  Middle window open
*
*   synopsis        c = wxopen(upr,upc,lor,loc,title,ctrl,dth,wth);
*                   COUNT c;    Returns window number or -1 if error
*                   COUNT upr,upc;  Upper row and Column
*                   COUNT lor,loc;  Lower row and Column
*                   TEXT *title; Pointer to NULL terminated string
*                                   to be used as a title for window
*                   COUNT ctrl;     Window control byte (see manual)
*                   COUNT dth,wth;  Width and depth of virtual window
*
*   Description     This is the middle window open. This function
*                   takes the upper corner, lower corner, title, ctrl 
*                   and size and adds default values for window color 
*                   and fill character and calls wxxopen(). It returns
*                   the window number or -1 if an error has occured.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

#ifdef WINDOW

WPTR wxopen(up_r,up_c,lo_r,lo_c,title,ctrl,dth,wth)
PFAST COUNT up_r,up_c; /* Upper row and column for window           */
PFAST COUNT lo_r,lo_c; /* Lower row and column for window           */
TEXT *title;        /* Pointer to title for window or NULL          */
COUNT ctrl;         /* Control byte for window                      */
COUNT dth,wth;      /* Depth and width of virtual window            */
    {
    WPTR wxxopen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wxopen:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(wxxopen(up_r,up_c,lo_r,lo_c,title,ctrl,dth,wth,-1,' '));
    }

#endif


