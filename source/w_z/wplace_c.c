/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:02
*
*   Name            wplace_cur  --  Place the cursor 
*
*   Description     This function places the cursor at the location
*                   winfo[number].r_pos, winfo[number].c_pos. It checks
*                   to see if this new positon is displayed if not it
*                   adjusts and displays the window.  If the values are
*                   not in the range of the window it does not return
*                   an error just wraps the values to make them fit.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wplace_cur(wptr)
WPTR wptr;          /* Pointer to window to address cursor          */
    {
    COUNT row,col,bd;
    WPTR wptr2;
    COUNT wbound();
    VOID wstack();
    COUNT winwdo();
    VOID vccurs();
    VOID vcaddrc();
    VOID wwrtdw();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wplace_cur:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    wptr2 = wdoctrl->wcurrent;
    bd=(wptr2->wctrl & BORDER ? 1 : 0);
    if(wptr->c_pos >= wptr->width)
        {
        wptr->c_pos %= wptr->width;
        wptr->r_pos += 1;
        }
    if(wptr->r_pos >= wptr->depth)
        wptr->r_pos %= wptr->depth;
    if(wptr->c_pos < 0)
        {
        wptr->c_pos=wptr->width+(wptr->width % wptr->c_pos)-1;
        wptr->r_pos -= 1;
        }
    if(wptr->r_pos < 0)
        wptr->r_pos=wptr->depth+(wptr->depth % wptr->r_pos)-1;
    if(wdoctrl->wfreeze)
        return;
    if(wptr->wctrl & ACTIVE)
        {
        if(!(wptr->wctrl & NOAUTO) && wbound(wptr))
            {
            wstack(wptr);
            wwrtdw(wptr);
            }
        col=wptr2->c_pos-wptr2->cur_c+wptr2->upper_c+bd;
        row=wptr2->r_pos-wptr2->cur_r+wptr2->upper_r+bd;
        if((wptr2->wctrl & CURSOR) && winwdo(wptr2,row,col))
            {
            if(vccursor > 2)
                vccurs(ON);
            vcaddrc(row,col);
            }
        else
            {
            vccurs(OFF);
#ifdef TERMINAL
            if(vctio == 5)
                vcaddrc(vcterm.rows-1,vcterm.cols-1);
#endif
            }
        }
    }

#endif


