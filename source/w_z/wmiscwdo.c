/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:45
*
*   Name            wmiscwdo.c -- Misc window function
*
*   Description     These functions return various values associated
*                   with a window. When windows were addressed by
*                   a number these were valuable but now that windows
*                   are addressed by a pointer the value of the 
*                   functions are questionable and will be removed
*                   in future releases.
*                   
*   Return Value    Varies
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wcoord(wptr,ur,uc,lr,lc)
WPTR wptr;
COUNT *ur,*uc,*lr,*lc;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wcoord:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    *ur = wptr->upper_r;
    *uc = wptr->upper_c;
    *lr = wptr->lower_r;
    *lc = wptr->lower_c;
    }

COUNT wctrl(wptr,ctrl,mode)
WPTR wptr;
COUNT *ctrl,mode;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wctrl:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(mode == SET)
        wptr->wctrl = *ctrl;
    else
        *ctrl = wptr->wctrl;
    return(0);
    }

COUNT wcurspos(wptr,row,col)
WPTR wptr;
COUNT *row,*col;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wcurspos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    *row = wptr->r_pos;
    *col = wptr->c_pos;
    return(0);
    }

TEXT *wmemloc(wptr)
WPTR wptr;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wmemloc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(wptr->location);
    }

WPTR winfoptr(wptr)
WPTR wptr;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "winfoptr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(wptr);
    }

COUNT wvirtpos(wptr,ur,uc)
WPTR wptr;
COUNT *ur,*uc;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wvirtpos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    *ur = wptr->cur_r;
    *uc = wptr->cur_c;
    return(0);
    }

COUNT wvirtsiz(wptr,depth,width)
WPTR wptr;
COUNT *depth,*width;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wvirtsiz:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    *depth = wptr->depth;
    *width = wptr->width;
    return(0);
    }

COUNT wattr(wptr,bd,bg,say,atg,natg,tit,mode)
WPTR wptr;
COUNT *bd,*bg,*say,*atg,*natg,*tit,mode;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wattr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(mode == SET)
        {
        wptr->bg_at = *bg;
        wptr->border_at = *bd;
        wptr->say_at = *say;
        wptr->get_at = *atg;
        wptr->nget_at = *natg;
        wptr->tit_at = *tit;
        }
    else
        {
        *bg = wptr->bg_at;
        *bd = wptr->border_at;
        *say = wptr->say_at;
        *atg = wptr->get_at;
        *natg = wptr->nget_at;
        *tit = wptr->tit_at;
        }
    return(0);
    }
#endif
