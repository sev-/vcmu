/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:54
*
*   Name            trn_on.c  --  Turn on terminal attribute
*
*   Description     This program turns on a specified attribute
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID trn_on(attr)
PFAST COUNT attr;   /* Attribute to turn on                         */
    {
    TEXT *gotopram;
    COUNT fgd,bgd;
    FAST COUNT spattr=0;
    COUNT ckspattr();
    VOID dist_str();
    COUNT ibmtoansi();
    VOID setspattr();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "trn_on:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    termattr = attr;
/* This has been replaced Vitamin C sending spaces !
    if(!attr)
        {
        if(vcterm.sp0on != NULLTEXT);
            dist_str(vcterm.sp0on,0);
        return;
        }
*/
    if(vcterm.ct != NULLTEXT)
        {
        fgd = FOREGROUND(attr);
        bgd = BACKGROUND(attr);
        fgd = ibmtoansi(fgd);
        bgd = ibmtoansi(bgd);
        switch(ttranslate)
            {
            case 0:
                 gotopram = (TEXT *)&(vcterm.color.before);
                break;
            case 1:
                gotopram = vcterm.ct;
                break;
            case 2:
                gotopram = vcterm.ct;
                break;
            }
        dist_str((*gotofunc)(gotopram,bgd,fgd),0);
        if(attr & BLINK_ATTR)
            if(ckspattr(BLINK_ATTR+NORM_ATTR))
                spattr |= BLINK_ATTR;
            else
                dist_str(vcterm.bo,0);
        if(attr & INTEN_ATTR)
            if(ckspattr(INTEN_ATTR+NORM_ATTR))
                spattr |= INTEN_ATTR;
            else
                dist_str(vcterm.it,0);
        }
    else
        {
        if(attr & BLINK_ATTR)
            if(ckspattr(BLINK_ATTR+NORM_ATTR))
                spattr |= BLINK_ATTR;
            else
                dist_str(vcterm.bo,0);
        if(attr & INTEN_ATTR)
            if(ckspattr(INTEN_ATTR+NORM_ATTR))
                spattr |= INTEN_ATTR;
            else
                dist_str(vcterm.it,0);
        attr &= ~GRAPH_ATTR;
        switch(attr)
            {
            case UNDER_ATTR :
                if(ckspattr(UNDER_ATTR))
                    spattr |= UNDER_ATTR;
                else
                    dist_str(vcterm.us,0);
                break;
            case NORM_ATTR :
                if(spattr)
                    spattr |= NORM_ATTR;
                break;
            case INVER_ATTR :
                if(ckspattr(INVER_ATTR))
                    spattr |= INVER_ATTR;
                else
                    dist_str(vcterm.so,0);
                break;
            case UNDER_ATTR+INVER_ATTR :
                if(ckspattr(UNDER_ATTR))
                    spattr |= UNDER_ATTR;
                else
                    dist_str(vcterm.us,0);
                if(ckspattr(INVER_ATTR))
                    spattr |= INVER_ATTR;
                else
                    dist_str(vcterm.so,0);
                break;
            default :
                break;
            }
        }
    if(spattr)
        setspattr(spattr,ON);
     }

static COUNT ibmcolors[8]= { 0,4,2,6,1,5,3,7};

COUNT ibmtoansi(color)
COUNT color;
    {
    return(ibmcolors[color]);
    }

#endif


