/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:09
*
*   Name            wputattr.c  --  Put attribute to window
*
*   Description     This function puts an attribute to the window
*                   This function unlike wputchr() does not increment
*                   the cursor. and it is the programmer responsibility
*                   to be sure the number of times does not cause
*                   an attribute to print outside the virtual window. 
*
*   Return Value    VOID
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT wputattr(wptr,attr,times)
WPTR wptr;          /* Pointer to window to place attribute         */
COUNT attr;         /* Attribute to use                             */
COUNT times;        /* Number of times to put attribute             */
    {
    COUNT row,col,bd,len,twidth;
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    FAST COUNT count;
    FAST TEXT *cpntr;
    COUNT offset;
    VOID wstack();
    COUNT vcpee();
    VOID vca_put();
    VOID vcflush();
    VOID wplace_cur();
    COUNT winwdo();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wputattr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & WOPEN))
        {
        vcerror = PANOTOPEN;
        return(-1);
        }
    twidth = vcterm.cols << 1;
    bd=(wptr->wctrl & BORDER ? 1: 0);
    row=wptr->r_pos;
    col=wptr->c_pos;
    offset = ((row*wptr->width+col) << 1)+1;
    cpntr=wptr->location+offset;
    for(count=0;count <times;count++,cpntr++)
        *(cpntr++)=attr;
    row+=wptr->upper_r+bd-wptr->cur_r;
    col+=wptr->upper_c+bd-wptr->cur_c;
    len=min((wptr->lower_c-col+1-bd),times);
    if((wptr->wctrl & ACTIVE) && winwdo(wptr,row,col))
        {
        wstack(wptr);
#ifdef TERMINAL
        if(vctio == 5)
            flow=vcpee();
        if(vcterm.mc)
            {
            if( col == 0)
                len = max((len+1),vcterm.cols);
            else
                {
                col--;
                len = ((col+len+2) > vcterm.cols ? vcterm.cols-col-1:len+2);
                }
            }
#endif 
        if(!wdoctrl->wfreeze)
            vca_put(row,col,wscreen+(row*twidth)+(col << 1),len);
#ifdef TERMINAL
        if(flow)
            vcflush();
#endif
        }
    if(cur_switch)
        wplace_cur(wdoctrl->wcurrent);
    return(0);
    }

#endif

