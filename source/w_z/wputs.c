/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:13
*
*   Name            wputs.c  --  Put a string to a window
*
*                   COUNT number;  Window number
*                   TEXT *str;   Pointer to NULL terminated string
*                   COUNT attr;    Attribute to use for string.
*
*   Description     This function puts a string to the window by 
*                   calling wputchr() until the string is ended.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wputs(wptr,str,attrb)
PFAST WPTR wptr;    /* Pointer to Window                            */
PFAST TEXT *str;    /* Pointer to String                            */
COUNT attrb;        /* Attribute to use                             */
    {
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    COUNT vcpee();
    COUNT wputchr();
    VOID wplace_cur();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wputs:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    cur_switch = FALSE;
#ifdef TERMINAL
    if(wptr->wctrl & ACTIVE)
        if(vctio == 5)
            flow=vcpee();
#endif
    while(*str)
        wputchr(wptr,*(str++),attrb);
    cur_switch = TRUE;
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    wplace_cur(wdoctrl->wcurrent);
    }

#endif


