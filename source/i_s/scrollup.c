/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:56
*
*   Name            scrollup.c  --  hardware scroll
*
*   Description     This function preforms a hardware scroll up
*                   on the location described by up,lf and lo,rt
*                   n number of lines with atr as an attribute.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID scrollup(up,lf,lo,rt,n,atr)
COUNT up,lf;        /* Upper left location                          */
COUNT lo,rt;        /* Lower right location                         */
COUNT n;            /* Number of lines to scroll                    */
COUNT atr;          /* Attribute for new line                       */
    {
#ifdef TERMONLY
    FAST COUNT start,wth,cnt;
    TEXT *sptr;
    COUNT twidth,flow=0;
    VOID vcint();
    COUNT vcpee();
    VOID clbx();
    VOID vca_put();
    VOID vcflush();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "scrollup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    flow=vcpee();
    if((n > (lo-up)) || (n == 0))
        {
        clbx(up,lf,lo,rt,atr);
        }
    else
        {
        start=up+n;
        twidth = vcterm.cols << 1;
        sptr = tscreen+(start*twidth)+(lf << 1);
        wth=rt-lf+1;
        for(cnt=0;start+cnt <= lo;cnt++)
            {
            vca_put(up+cnt,lf,sptr,wth);
            sptr += twidth;
            }
        clbx(lo-n+1,lf,lo,rt,atr);
        }
     if(flow)
         vcflush();
#endif
#ifdef IBM
#ifndef TERMINAL
    VOID vcint();
    COUNT vcpee();
    VOID clbx();
    VOID vca_put();
    VOID vcflush();
    struct VCREGS wdiregs,wdoregs;
    wdiregs.cx = (up * 0x100)+lf;
    wdiregs.dx = (lo * 0x100)+rt;
    wdiregs.ax = (6 * 0x100)+n;
    wdiregs.bx = atr * 0x100;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "scrollup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    vcint(0x10,&wdiregs,&wdoregs);
#else
    VOID vcint();
    COUNT vcpee();
    VOID clbx();
    VOID vca_put();
    VOID vcflush();
    FAST COUNT start,wth,cnt;
    TEXT *sptr;
    struct VCREGS wdiregs,wdoregs;
    COUNT twidth,flow=0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "scrollup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(vctio != 5)
        {
        wdiregs.cx = (up * 0x100)+lf;
        wdiregs.dx = (lo * 0x100)+rt;
        wdiregs.ax = (6 * 0x100)+n;
        wdiregs.bx = atr * 0x100;
        vcint(0x10,&wdiregs,&wdoregs);
        }
    else
        {
        flow=vcpee();
        if((n > (lo-up)) || (n == 0))
            {
            clbx(up,lf,lo,rt,atr);
            }
        else
            {
            start=up+n;
            twidth = vcterm.cols << 1;
            sptr = tscreen+(start*twidth)+(lf << 1);
            wth=rt-lf+1;
            for(cnt=0;start+cnt <= lo;cnt++)
                {
                vca_put(up+cnt,lf,sptr,wth);
                sptr += twidth;
                }
            clbx(lo-n+1,lf,lo,rt,atr);
            }
        if(flow)
            vcflush();
        }
#endif
#endif
#ifdef OS2
#ifndef TERMINAL
    BYTE blank[2];
#ifdef VCDEBUG
    vcdebug = (TEXT *) "scrollup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    blank[0] = ' ';
    blank[1] = atr;
    VioScrollUp(up,lf,lo,rt,n,blank,0);
#else
    BYTE blank[2];
    COUNT vcpee();
    VOID clbx();
    VOID vca_put();
    VOID vcflush();
    FAST COUNT start,wth,cnt;
    TEXT *sptr;
    COUNT twidth,flow=0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "scrollup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(vctio != 5)
        {
        blank[0] = ' ';
        blank[1] = atr;
        VioScrollUp(up,lf,lo,rt,n,blank,0);
        }
    else
        {
        flow=vcpee();
        if((n > (lo-up)) || (n == 0))
            {
            clbx(up,lf,lo,rt,atr);
            }
        else
            {
            start=up+n;
            twidth = vcterm.cols << 1;
            sptr = tscreen+(start*twidth)+(lf << 1);
            wth=rt-lf+1;
            for(cnt=0;start+cnt <= lo;cnt++)
                {
                vca_put(up+cnt,lf,sptr,wth);
                sptr += twidth;
                }
            clbx(lo-n+1,lf,lo,rt,atr);
            }
        if(flow)
            vcflush();
        }
#endif
#endif
    }

