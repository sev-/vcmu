/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:52
*
*   Name            trn_off.c  --  Turn off terminal attribute
*
*   Description     This program turns off a specified attribute
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID trn_off(attr)
PFAST COUNT attr;   /* Attribute to turn off                        */
    {
    COUNT ckspattr();
    VOID dist_str();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "trn_off:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
/* This has been replaced by Vitamin C sending spaces
    if(!attr)
        {
        if(vcterm.sp0off != NULLTEXT);
            dist_str(vcterm.sp0off,0);
        return;
        }
*/
    if(attr & BLINK_ATTR)
        if(ckspattr(BLINK_ATTR+NORM_ATTR))
            sp_attr |= BLINK_ATTR;
        else
            dist_str(vcterm.be,0);
    if(attr & INTEN_ATTR)
        if(ckspattr(INTEN_ATTR+NORM_ATTR))
            sp_attr |= INTEN_ATTR;
        else
            dist_str(vcterm.ie,0);
    attr &= ~GRAPH_ATTR;
    if(vcterm.ct == NULLTEXT)
        {
        switch(attr)
            {
            case UNDER_ATTR :
                if(ckspattr(UNDER_ATTR))
                    sp_attr |= UNDER_ATTR;
                else
                    dist_str(vcterm.ue,0);
                break;
            case NORM_ATTR :
                if(sp_attr)
                    sp_attr |= NORM_ATTR;
                break;
            case INVER_ATTR :
                if(ckspattr(INVER_ATTR))
                    sp_attr |= INVER_ATTR;
                else
                    dist_str(vcterm.se,0);
                break;
            case UNDER_ATTR+INVER_ATTR :
                if(ckspattr(UNDER_ATTR))
                    sp_attr |= UNDER_ATTR;
                else
                    dist_str(vcterm.ue,0);
                if(ckspattr(INVER_ATTR))
                    sp_attr |= INVER_ATTR;
                else
                    dist_str(vcterm.se,0);
                break;
            default :
                break;
            }
        }
    }
#endif


