/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 8/31/90 at 22:18:22
*
*   Name            vca_cput.c  --  Terminal put character
*
*   Description     This program puts one character to the terminal
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

TEXT vcspfill = SPACE;
COUNT vcspafill = 7;
COUNT vcinvchr = SPACE;

VOID vca_cput(ch,attr)
TEXT *ch;
COUNT attr;
    {
    VOID trn_on();
    VOID trn_off();
    VOID flipattr();
    VOID dist_str();
    COUNT ckspattr();
    VOID setspattr();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vca_cput:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    tcol++;
#ifdef NOUNSIGNED
#ifdef PRIMOS
    *ch = ((*ch < ' ') && (*ch > 128) ? ' ':*ch);
#else
    *ch = ((*ch < ' ') && (*ch > 0) ? ' ':*ch);
#endif
    if(vcterm.mc && (*ch <= AT_OFF))
#else
    *ch = (*ch < ' ' ? ' ':*ch);
    if(vcterm.mc && (*ch >= AT_OFF))
#endif
        {
        if(*ch == AT_OFF)
            {
            trn_off(termattr);
            trn_off(attr);
            if(sp_attr)
                setspattr(sp_attr,OFF);
            if(!ckspattr(attr))
                {
                vca_cput(vcspfill,vcspafill);
                tcol--;
                }
            termattr = normattr;
            }
        else
            {
            trn_off(termattr);
            trn_on(attr);
            if(!ckspattr(attr))
                {
                vca_cput(vcspfill,vcspafill);
                tcol--;
                }
            }
        }
    else
        {
        if(attr != termattr)
            flipattr(attr);
#ifdef PRIMOS
        if(*ch < 128)
#else
#ifdef NOUNSIGNED
        if(*ch < 0)
#else
        if(*ch > 127)
#endif
#endif
            {
            if(!graphattr)
                {
                dist_str(vcterm.gs,0);
                graphattr = TRUE;
                }
            }
        else
            {
            if(graphattr)
                {
                dist_str(vcterm.ge,0);
                graphattr = FALSE;
                }
            }
        if(!termattr)
            *ch = vcinvchr;
        dist_str(ch,1);
        }
    }

VOID flipattr(attr)
COUNT attr;
    {
    VOID trn_off();
    VOID trn_on();
    COUNT ckspattr();
    VOID setspattr();
    VOID dist_str();
    if(!vcterm.mc || !ckspattr(termattr))
        trn_off(termattr);
    if(vcterm.xs)
        {
        if(graphattr)
            {
            dist_str(vcterm.ge,0);
            graphattr = FALSE;
            }
        if(sp_attr)
            setspattr(sp_attr,OFF);
        }
    if(!vcterm.mc || !ckspattr(attr))
        trn_on(attr);
    if(sp_attr)
        setspattr(sp_attr,OFF);
    }

#endif




