/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:36
*
*   Name            wspbox.c  --  Draw a box
*
*   Description     This function prints a box described by
*                   up,lf and lo,rt with attribute attr on
*                   a window.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID wspbox(wptr,up,lf,lo,rt,type,attr)
WPTR wptr;          /* Pointer to window                            */
COUNT up,lf;        /* Upper left corner of box                     */
COUNT lo,rt;        /* Lower right corner of box                    */
COUNT type;         /* Type of box {0,1,2}                          */
COUNT attr;         /* Attribute to print box (-1 for default       */
    {
    FAST COUNT n,attrb;
    struct BODR *bptr;
    VOID wat();
    VOID vcflush();
    COUNT vcpee();
    COUNT wputchr();
    VOID wwrrtbox();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wspbox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    bptr= &border[type];
    cur_switch = FALSE;
    if(attr == vc.dflt)
        attrb = wptr->say_at;
    else
        attrb = attr;
    woff();
    if((up == lo) || (lf == rt) )
        {
        if(up == lo)
            {
            wat(wptr,up,lf);
            for(n=1;n<(rt-lf+2);n++)
                wputchr(wptr,bptr->across,attrb);
            }
        else
            {
            for(n=0;n<(lo-up+1);n++)
                {
                wat(wptr,(up+n),lf);
                wputchr(wptr,bptr->up,attrb);
                }
            }
        wdoctrl->wfreeze = FALSE;
        wstack(wptr);
        wwrrtbox(wptr,up,lf,lo,rt);
        cur_switch = TRUE;
        wplace_cur(wdoctrl->wcurrent);
        return;
        }
    wat(wptr,up,lf);
    wputchr(wptr,bptr->tl,attrb);
    for(n=1;n<(rt-lf);n++)
        wputchr(wptr,bptr->across,attrb);
    wputchr(wptr,bptr->tr,attrb);
    for(n=1;n<(lo-up);n++)
        {
        wat(wptr,(up+n),lf);
        wputchr(wptr,bptr->up,attrb);
        wat(wptr,(up+n),rt);
        wputchr(wptr,bptr->up,attrb);
        }
    wat(wptr,lo,lf);
    wputchr(wptr,bptr->bl,attrb);
    for(n=1;n<(rt-lf);n++)
        wputchr(wptr,bptr->across,attrb);
    wputchr(wptr,bptr->br,attrb);
    wdoctrl->wfreeze = FALSE;
    wstack(wptr);
    wwrrtbox(wptr,up,lf,lo,rt);
    cur_switch = TRUE;
    wplace_cur(wdoctrl->wcurrent);
    }

VOID wwrrtbox(wptr,up_row,up_col,lo_row,lo_col)
WPTR wptr;
COUNT up_row,up_col;
COUNT lo_row,lo_col;
    {
    COUNT trow,tcol,brow,bcol;
    COUNT row,col;
    COUNT bd;
    VOID wwrtbox();
    bd=(wptr->wctrl & BORDER ? 1: 0);
    trow = wptr->upper_r+bd-wptr->cur_r+up_row;
    tcol = wptr->upper_c+bd-wptr->cur_c+up_col;
    col = lo_col - up_col + 1;
    row = lo_row - up_row +1;
    brow = min(vcterm.rows-1,trow+row);
    bcol = min(vcterm.cols-1,tcol+col);
    if(trow)
        trow--;
    if(tcol)
        tcol--;
    wwrtbox(trow,tcol,brow,bcol);
    return;
    }

VOID wwrtbox(up_row,up_col,lo_row,lo_col)
COUNT up_row,up_col;
COUNT lo_row,lo_col;
    {
    FAST COUNT rowcnt;
    COUNT width,twidth;
    COUNT flow = 0;
    FAST TEXT *sptr;
    COUNT vcpee();
    VOID vca_put();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wwrtbox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    if(wdoctrl->wfreeze)
        return;
    if(vctio == 5)
        flow=vcpee();
    width = lo_col - up_col + 1;
    sptr = wscreen+(up_row*twidth)+(up_col << 1);
    for(rowcnt = up_row;rowcnt <= lo_row ; rowcnt++)
        {
        vca_put(rowcnt,up_col,sptr,width);
        sptr += twidth;
        }
    if(flow)
        vcflush();
    return;
    }

#endif

