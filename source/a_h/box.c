/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:03
*
*   Name            box.c  --  Draw a box
*
*   synopsis        box(up,lf,lo,rt,type,attr);
*                   COUNT up,lf;   Upper left corner of box
*                   COUNT lo,rt;   Lower right corner of box
*                   COUNT type;    Type of box {0,1,2}
*                   COUNT attr;    Attribute to print box
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

VOID box(up,lf,lo,rt,type,attr)
COUNT up,lf;        /* Upper left corner of box                     */
COUNT lo,rt;        /* Lower right corner of box                    */
COUNT type;         /* Type of box {0,1,2}                          */
COUNT attr;         /* Attribute to print box (-1 for default       */
    {
    FAST COUNT n,attrb;
#ifdef TERMINAL
    COUNT flow=0;
#endif
    struct BODR *bptr;
    VOID at();
    VOID vcflush();
    COUNT vcpee();
    VOID vcputc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "box:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef TERMINAL
    if(vcterm.mc || !vcterm.ms)
        spbox(up,lf,lo,rt,type,attr);
#endif
    bptr= &border[type];
    cur_switch = FALSE;

    if(attr == vc.dflt)
        {
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            attrb = wdoctrl->wcurrent->say_at;
        else
#endif
            attrb = attrsay;
        }
    else
        attrb = attr;
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    at(up,lf);
    if((up == lo) || (lf == rt) )
        {
        if(up == lo)
            {
            for(n=1;n<(rt-lf+2);n++)
                vcputc(bptr->across,attrb);
            }
        else
            {
            for(n=0;n<(lo-up+1);n++)
                {
                at( (up+n),lf);
                vcputc(bptr->up,attrb);
                }
            }
#ifdef TERMINAL
        if(flow)
            vcflush();
#endif
        cur_switch = TRUE;
        at(vcrow,vccol);
        return;
        }
    vcputc(bptr->tl,attrb);
    for(n=1;n<(rt-lf);n++)
        vcputc(bptr->across,attrb);
    vcputc(bptr->tr,attrb);
    for(n=1;n<(lo-up);n++)
        {
        at( (up+n),lf);
        vcputc(bptr->up,attrb);
        at( (up+n),rt);
        vcputc(bptr->up,attrb);
        }
    at( lo,lf);
    vcputc(bptr->bl,attrb);
    for(n=1;n<(rt-lf);n++)
        vcputc(bptr->across,attrb);
    vcputc(bptr->br,attrb);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
    cur_switch = TRUE;
    at(vcrow,vccol);
    }
