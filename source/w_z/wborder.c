/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:54
*
*   Name            wborder.c  --  prints border on memory screen
*
*   Description     Prints the border on the memory screen and prints
*                   the title centered on the top.  Uses the colors in
*                   winfo[number].bd_at & winfo[number].tit_at. Border
*                   could be the default of 0 thru 2 or custom and is
*                   found in the structure border[].
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wborder(wptr,type)
WPTR wptr;          /* Pointer to window needing border             */
COUNT type;         /* Type of border or -1 for default             */
    {
    FAST COUNT cnt;
    COUNT nrow,width;
    COUNT len,bd_no,twidth;
    FAST TEXT *sptr;
    TEXT *cpntr,*cp;
    COUNT strlen();
#ifdef SBARS
    COUNT vpoint,hpoint;
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wborder:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
#ifdef SBARS
    vpoint=wvbar(wptr);
    hpoint=whbar(wptr);
#endif
    if(type == -1)
        bd_no=(wptr->wctrl >> 5) & 3;
    else
        bd_no=type;
    width = wptr->upper_c << 1;
    sptr = wscreen+(wptr->upper_r*twidth)+width;
    *(sptr++) = border[bd_no].tl;
    *(sptr++) = wptr->border_at;
    nrow = (wptr->lower_c << 1)-width-2;
    sptr += nrow;
    *(sptr++) = border[bd_no].tr;
    *(sptr++) = wptr->border_at;
    sptr = wscreen+(wptr->lower_r*twidth)+width;
    *(sptr++) = border[bd_no].bl;
    *(sptr++) = wptr->border_at;
    sptr += nrow;
    *(sptr++) = border[bd_no].br;
    *(sptr++) = wptr->border_at;
    sptr = wscreen+(wptr->upper_r*twidth)+width+2;
    cp = wscreen+(wptr->lower_r*twidth)+width+2;
    for(cnt=wptr->upper_c+1;cnt < wptr->lower_c;cnt++)
        {
        *(sptr++) = border[bd_no].across;
        *(sptr++) = wptr->border_at;
#ifdef SBARS
        if( (wptr->wctrl & SCROLLBAR) && (cnt == hpoint) )
            *(cp++) = border[bd_no].middle;
        else
#endif
            *(cp++) = border[bd_no].across;
        *(cp++) = wptr->border_at;
        }
    cnt=wptr->upper_r+1;
    sptr = wscreen+(cnt*twidth)+width;
    width = twidth - nrow -4;
    for(;cnt < wptr->lower_r;cnt++)
        {
#ifdef SBARS
        if( (wptr->wctrl & SCROLLBAR) && (cnt==vpoint) )
            *(sptr++) = border[bd_no].middle;
        else
#endif
            *(sptr++) = border[bd_no].up;
        *(sptr++) = wptr->border_at;
        sptr += nrow;
        *(sptr++) = border[bd_no].up;
        *(sptr++) = wptr->border_at;
        sptr += width;
        }
    cpntr = wptr->title;
    if(cpntr != NULLTEXT)
        {
        len = strlen(cpntr);
        cnt=wptr->lower_c-wptr->upper_c-1;   /* width of window */
        if(len > cnt)               /* If title longer than window */
            len=cnt;                /* len = maximum size          */
        cnt = (cnt - len) / 2;     /* # of spaces to center       */
        cnt = cnt + wptr->upper_c + 1;
        cp = wscreen+(wptr->upper_r*twidth)+(cnt << 1);
        while( len )
            {
            *(cp++) = *(cpntr++);
            *(cp++) = wptr->tit_at;
            len--;
            }
        }
    cpntr = wptr->btitle;
    if(cpntr != NULLTEXT)
        {
        len = strlen(cpntr);
        cnt=wptr->lower_c-wptr->upper_c-1;   /* width of window     */
        if(len > cnt)                   /* If title longer than wdo */
            len = cnt;                  /* len = maximum size       */
        cnt = (cnt - len) / 2;          /* # of spaces to center    */
        cnt = cnt + wptr->upper_c + 1;
        cp = wscreen+(wptr->lower_r*twidth)+(cnt << 1);
        while( len )
            {
            *(cp++) = *(cpntr++);
            *(cp++) = wptr->btit_at;
            len--;
            }
        }
    cpntr = wptr->ltitle;
    if(cpntr != NULLTEXT)
        {
        len = strlen(cpntr);
        cnt=wptr->lower_r-wptr->upper_r-1;   /* depth of window     */
        if(len > cnt)                   /* If title longer than wdo */
            len = cnt;                  /* len = maximum size       */
        cnt = (cnt - len) / 2;          /* # of spaces to center    */
        cnt = cnt + wptr->upper_r + 1;
        cp = wscreen+(cnt*twidth)+(wptr->upper_c << 1);
        while( len )
            {
            *(cp++) = *(cpntr++);
            *(cp++) = wptr->ltit_at;
            len--;
            cp += twidth-2;
            }
        }
    cpntr = wptr->rtitle;
    if(cpntr != NULLTEXT)
        {
        len = strlen(cpntr);
        cnt=wptr->lower_r-wptr->upper_r-1;   /* depth of window     */
        if(len > cnt)                   /* If title longer than wdo */
            len = cnt;                  /* len = maximum size       */
        cnt = (cnt - len) / 2;          /* # of spaces to center    */
        cnt = cnt + wptr->upper_r + 1;
        cp = wscreen+(cnt*twidth)+(wptr->lower_c << 1);
        while( len )
            {
            *(cp++) = *(cpntr++);
            *(cp++) = wptr->rtit_at;
            len--;
            cp += twidth-2;
            }
        }
    }

VOID wshadow(wptr)
WPTR wptr;
    {
    FAST COUNT cnt;
    COUNT nrow,width;
    COUNT twidth;
    FAST TEXT *sptr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wshadow:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    if(wptr->lower_c < (vcterm.cols - 1))
        {
        cnt = wptr->upper_r+1;
        width = (wptr->lower_c+1) << 1;
        sptr = wscreen+(cnt*twidth)+width;
        width = twidth - 2;
        nrow = min((wptr->lower_r+1),(vcterm.rows-1));
        for(;cnt <= nrow;cnt++)
            {
            *(sptr++) = ' ';
            *(sptr++) = 0;
            if(wptr->lower_c < (vcterm.cols - 2))
                {
                *sptr = ' ';
                *(sptr+1) = 0;
                }
            sptr += width;
            }
        }
    if(wptr->lower_r < (vcterm.rows - 1))
        {
        width = wptr->upper_c << 1;
        sptr = wscreen+((wptr->lower_r+1)*twidth)+width+4;
        for(cnt=wptr->upper_c+2;cnt <= wptr->lower_c;cnt++)
            {
            *(sptr++) = ' ';
            *(sptr++) = 0;
            }
        }
    }

#endif


