/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:23
*
*   Name            werase.c  --  Erase to end of screen
*
*   Description     This function erases the selected virtual window
*                   (number) using attr or the default attribute if
*                   attr == -1 (winfo[number].bg_at)
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID werase(wptr,attr)
WPTR wptr;          /* Pointer to window to erase                   */
PFAST COUNT attr;   /* Attribute to use                             */
    {
#ifdef TERMINAL
    COUNT flow = FALSE;
#endif
    VOID wclr();
    COUNT vcpee();
    VOID vcflush();
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "werase:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(attr == -1)
        attr=wptr->bg_at;
#ifdef TERMINAL
    if(vctio == 5)
        flow = vcpee();
#endif
    wclr(wptr,attr);
    wptr->cur_r=0;
    wptr->cur_c=0;
    wptr->c_pos=0;
    wptr->r_pos=0;
    if(wptr->wctrl & ACTIVE)
        {
        wstack(wptr);
        wwrtdw(wptr);
        wplace_cur(wdoctrl->wcurrent);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    }

#endif


