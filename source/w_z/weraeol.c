/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:20
*
*   Name            weraeol.c  --  Window erase end of line
*
*   Description     Erase from the current column position to the end of
*                   line If attribute equal to -1 uses winfo[number].bg_at 
*                   for attribute.  This function can be called with 
*                   wcurrent by using eraeol() and xeraeol().
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID weraeol(wptr,attr)
WPTR wptr;          /* Pointer to window to erase                   */
COUNT attr;         /* Attribute to use on erase                    */
    {
    FAST COUNT cnt;
    FAST TEXT *cpntr;
    COUNT offset;
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "weraeol:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(attr < 0)
        attr=wptr->bg_at;
    offset = (wptr->r_pos*wptr->width+wptr->c_pos) << 1;
    cpntr=wptr->location+offset;
    for(cnt=wptr->c_pos;cnt < wptr->width;cnt++)
        {
        *(cpntr++)= wptr->fill_ch;
        *(cpntr++)= attr;
        }
    if(wptr->wctrl & ACTIVE)
        {
        wstack(wptr);
        wwrtdw(wptr);
        wplace_cur(wdoctrl->wcurrent);
        }
    }

#endif


