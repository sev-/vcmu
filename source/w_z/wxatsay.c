/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:57
*
*   Name            wxatsay.c  --  Extended atsay()
*
*   Description     This print the Null terminated string pointed
*                   to by str to the window {number} at location
*                   row,col with attribute attr. This is a way to
*                   print to any window at any time without changing
*                   the current window (by selecting).
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wxatsay(wptr,row,col,str,attr)
PFAST WPTR wptr;    /* Pointer to window to use                     */
COUNT row,col;      /* Location to display string                   */
TEXT *str;          /* Pointer to string to display                 */
COUNT attr;         /* Attribute to use                             */
    {
    VOID wsxatsay();
    VOID wplace_cur();
    VOID wputs();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wxatsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vcterm.mc || !vcterm.ms)
        {
        wsxatsay(wptr,row,col,str,attr);
        return;
        }
#endif
    wptr->r_pos=row;
    wptr->c_pos=col;
    wplace_cur(wptr);
    wputs(wptr,str,attr);
    wplace_cur(wdoctrl->wcurrent);
    }

#endif


