/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:57
*
*   Name            wbox.c  --  Draw a box
*
*   Description     This function prints a box described by
*                   up,lf and lo,rt with attribute attr on
*                   the screen or on the current window. if
*                   upper row = lower row a line is drawn or
*                   lower left = upper right a column
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#define VCUSESCROLL BIT12

VOID wbox(wptr,up,lf,lo,rt,type,attr)
WPTR wptr;          /* Window to draw box on                        */
COUNT up,lf;        /* Upper left corner of box                     */
COUNT lo,rt;        /* Lower right corner of box                    */
COUNT type;         /* Type of box {0,1,2}                          */
COUNT attr;         /* Attribute to print box (-1 for default       */
    {
    FAST COUNT n,attrb;
    COUNT ntype;
    COUNT bottom;
    COUNT right;
    COUNT right_corner;
    COUNT left_corner;
    COUNT top_right;
#ifdef TERMINAL
    COUNT flow=0;
#endif
    struct BODR *bptr;
    COUNT vcpee();
    VOID vcflush();
    COUNT wputchr();
    VOID wat();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wbox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ntype = type & ~VCUSESCROLL;
    bptr= &border[ntype];
    if(ntype == type)
        {
        bottom = bptr->across;
        right = bptr->up;
        right_corner = bptr->br;
        left_corner = bptr->bl;
        top_right = bptr->tr;
        }
    else
        {
        bottom = bptr->scr_bot;
        right = bptr->scr_side;
        right_corner = bptr->scr_rch;
        left_corner = bptr->scr_lch;
        top_right = bptr->scr_tch;
        }
    cur_switch = FALSE;
    if(attr == vc.dflt)
        {
        attrb = wptr->say_at;
        }
    else
        attrb = attr;
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    wat(wptr,up,lf);
    if((up == lo) || (lf == rt) )
        {
        if(up == lo)
            {
            for(n=1;n<(rt-lf+2);n++)
                wputchr(wptr,bptr->across,attrb);
            }
        else
            {
            for(n=0;n<(lo-up+1);n++)
                {
                wat(wptr, (up+n),lf);
                wputchr(wptr,bptr->up,attrb);
                }
            }
#ifdef TERMINAL
        if(flow)
            vcflush();
#endif
        cur_switch = TRUE;
        wat(wptr,vcrow,vccol);
        return;
        }
    wputchr(wptr,bptr->tl,attrb);
    for(n=1;n<(rt-lf);n++)
        wputchr(wptr,bptr->across,attrb);
    wputchr(wptr,top_right,attrb);
    for(n=1;n<(lo-up);n++)
        {
        wat(wptr,(up+n),lf);
        wputchr(wptr,bptr->up,attrb);
        wat(wptr,(up+n),rt);
        wputchr(wptr,right,attrb);
        }
    wat(wptr,lo,lf);
    wputchr(wptr,left_corner,attrb);
    for(n=1;n<(rt-lf);n++)
        wputchr(wptr,bottom,attrb);
    wputchr(wptr,right_corner,attrb);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    cur_switch = TRUE;
    wat(wptr,vcrow,vccol);
    return;
    }
