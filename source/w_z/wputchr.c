/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:11
*
*   Name            wputchr.c  --  Put character to window
*
*   Description     This is one of the main program in windows it
*                   puts a character to the window and if necessary
*                   to the screen. This function checks and adjusts
*                   for word wrap, insert mode, expanding control 
*                   codes, margins, and adjusts so the next location
*                   to be printed is visible. This function like 
*                   vcputc() puts one character and increments the 
*                   cursor.
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT wputchr(wptr,text,attr)
PFAST WPTR wptr;    /* Pointer to window to write to                */
COUNT text;         /* Text to write                                */
COUNT attr;         /* Attribute to use                             */
    {
    COUNT row,col,bd,width,depth;
    COUNT twidth,draw=0;
    FAST TEXT *sptr;
    TEXT hold[2];
    COUNT offset;
    VOID vca_put();
    COUNT wmov_cur();
    COUNT whit();
    COUNT winwdo();
    COUNT wbound();
    VOID wstack();
    VOID wwrtdw();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wputchr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!(wptr->wctrl & WOPEN))
        {
        vcerror = PUTNOTOPEN;
        return(-1);
        }
    twidth = vcterm.cols << 1;
    bd=(wptr->wctrl & BORDER ? 1: 0);
    if((wptr->wctrl & COOKED) && (wptr->wtranfunc != NULLFUNC))
        if((draw = (*wptr->wtranfunc)(wptr,&text,&attr)) < 0)
            {
            if((wptr->wctrl & ACTIVE) && (draw == -2))
                {
                wstack(wptr);
                wwrtdw(wptr);
                }
            return(0);
            }
    width=wptr->lower_c-wptr->upper_c+1-(bd << 1);
    depth=wptr->lower_r-wptr->upper_r+1-(bd << 1);
    row=wptr->r_pos;
    col=wptr->c_pos;
#ifdef NOUNSIGNED
    if(vcterm.mc && (text <= AT_OFF))
#else
    if(vcterm.mc && (text >= AT_OFF))
#endif
        {
        hold[0]=text;
        hold[1]=attr;
        row+=wptr->upper_r+bd-wptr->cur_r;
        col+=wptr->upper_c+bd-wptr->cur_c;
        if(!wdoctrl->wfreeze && (wptr->wctrl & ACTIVE))
            vca_put(row,col,hold,1);
        draw = wmov_cur(wptr,draw);
        return(0);
        }
    offset = ((row*wptr->width+col) << 1);
    sptr = wptr->location + offset;
    *(sptr++) = text;
    *sptr = attr;
    row+=wptr->upper_r+bd-wptr->cur_r;
    col+=wptr->upper_c+bd-wptr->cur_c;
    if((wptr->wctrl & ACTIVE)  && whit(wptr,row,col) &&
            winwdo(wptr,row,col) && (width > 0) && (depth > 0)
            && !wdoctrl->wfreeze )
        {
        sptr = wscreen+(row*twidth)+(col << 1);
        *(sptr++) = text;
        *(sptr--) = attr;
        vca_put(row,col,sptr,1);
        }
    draw = wmov_cur(wptr,draw);
    if((wptr->wctrl & ACTIVE) && !wdoctrl->wfreeze)
        {
        if( !(wptr->wctrl & NOAUTO) && (wbound(wptr) || draw) )
            {
            wstack(wptr);
            wwrtdw(wptr);
            }
        if(cur_switch)
            wplace_cur(wptr);
        }
    return(0);
    }

#endif


