/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 8/31/90 at 22:10:18
*
*   Name            spbox.c  --  Draw a box
*
*   Description     This function prints a box described by
*                   up,lf and lo,rt on a special terminal
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID spbox(up,lf,lo,rt,type,attr)
COUNT up,lf;        /* Upper left corner of box                     */
COUNT lo,rt;        /* Lower right corner of box                    */
COUNT type;         /* Type of box {0,1,2}                          */
COUNT attr;         /* Attribute to print box (-1 for default       */
    {
    FAST COUNT n,attrb;
    COUNT flow=0;
    TEXT hold[2];
    COUNT skip = FALSE;
    struct BODR *bptr;
    VOID at();
    VOID vcflush();
    COUNT vcpee();
    VOID vcputc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "spbox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        {
        wspbox(wdoctrl->wcurrent,up,lf,lo,rt,type,attr);
        return;
        }
#endif
    bptr= &border[type];
    cur_switch = FALSE;
    if(attr == vc.dflt)
        attrb = attrsay;
    else
        attrb = attr;
    if(vctio == 5)
        flow=vcpee();
    hold[1] = attrb;
    if((up == lo) || (lf == rt) )
        {
        if(up == lo)
            {
            at(up,lf);
            if(!vcterm.ms)
                {
                hold[0] = AT_ON;
                if(vcterm.mc)
                    {
                    if(lf)
                        vca_put(up,lf-1,hold,1);
                    else
                        {
                        vca_put(up,lf,hold,1);
                        lf--;
                        }
                    }
                else
                    flipattr(attrb);
                }
            for(n=1;n<(rt-lf+2);n++)
                vcputc(bptr->across,attrb);
            if(!vcterm.ms)
                {
                hold[0] = AT_OFF;
                if(vcterm.mc)
                    {
                    if(rt < vcterm.cols-1)
                        vca_put(up,rt+1,hold,1);
                    }
                else
                    flipattr(NORM_ATTR);
                }
            }
        else
            {
            for(n=0;n<(lo-up+1);n++)
                {
                if(!vcterm.ms)
                    {
                    hold[0] = AT_ON;
                    if(vcterm.mc)
                        {
                        if(lf)
                            {
                            at((up+n),lf);
                            vca_put(up+n,lf-1,hold,1);
                            vcputc(bptr->up,attrb);
                            if(lf < vcterm.cols-1)
                                {
                                hold[0] = AT_OFF;
                                vca_put(up+n,lf+1,hold,1);
                                }
                            }
                        }
                    else
                        {
                        at((up+n),lf);
                        flipattr(attrb);
                        vcputc(bptr->up,attrb);
                        flipattr(NORM_ATTR);
                        }
                    }
                else
                    {
                    at((up+n),lf);
                    vcputc(bptr->up,attrb);
                    }
                }
            }
        if(flow)
            vcflush();
        cur_switch = TRUE;
        at(vcrow,vccol);
        return;
        }
    at(up,lf);
    if(!vcterm.ms)
        {
        hold[0] = AT_ON;
        if(vcterm.mc)
            {
            if(lf)
                vca_put(up,lf-1,hold,1);
            else
                {
                vca_put(up,lf,hold,1);
                lf--;
                skip = TRUE;
                }
            }
        else
            flipattr(attrb);
        }
    if(!skip)
        vcputc(bptr->tl,attrb);
    for(n=1;n<(rt-lf);n++)
        vcputc(bptr->across,attrb);
    vcputc(bptr->tr,attrb);
    if(!vcterm.ms)
        {
        hold[0] = AT_OFF;
        if(vcterm.mc)
            {
            if(rt < vcterm.cols-1)
                vca_put(up,rt+1,hold,1);
            }
        else
            flipattr(NORM_ATTR);
        }
    for(n=1;n<(lo-up);n++)
        {
        if(!vcterm.ms)
            {
            hold[0] = AT_ON;
            if(vcterm.mc)
                {
                if(!skip)
                    {
                    vca_put(up+n,lf-1,hold,1);
                    at( (up+n),lf);
                    vcputc(bptr->up,attrb);
                    hold[0] = AT_OFF;
                    vca_put(up+n,lf+1,hold,1);
                    }
                hold[0] = AT_ON;
                vca_put(up+n,rt-1,hold,1);
                at( (up+n),rt);
                vcputc(bptr->up,attrb);
                if(rt < vcterm.cols-1)
                    {
                    hold[0] = AT_OFF;
                    vca_put(up+n,rt+1,hold,1);
                    }
                }
            else
                {
                flipattr(attrb);
                at( (up+n),lf);
                vcputc(bptr->up,attrb);
                flipattr(NORM_ATTR);
                flipattr(attrb);
                at( (up+n),rt);
                vcputc(bptr->up,attrb);
                flipattr(NORM_ATTR);
                }
            }
        else
            {
            at( (up+n),lf);
            vcputc(bptr->up,attrb);
            at( (up+n),rt);
            vcputc(bptr->up,attrb);
            }
        }
    at( lo,lf);
    if(!vcterm.ms)
        {
        hold[0] = AT_ON;
        if(vcterm.mc)
            vca_put(lo,lf-1,hold,1);
        else
            flipattr(attrb);
        }
    if(!skip)
        vcputc(bptr->bl,attrb);
    for(n=1;n<(rt-lf);n++)
        vcputc(bptr->across,attrb);
    vcputc(bptr->br,attrb);
    if(!vcterm.ms)
        {
        hold[0] = AT_OFF;
        if(vcterm.mc)
            {
            if(rt < vcterm.cols-1)
                vca_put(lo,rt+1,hold,1);
            }
        else
            flipattr(NORM_ATTR);
        }
    if(flow)
        vcflush();
    cur_switch = TRUE;
    at(vcrow,vccol);
    }

#endif
