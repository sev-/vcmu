/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:30
*
*   Name            addwstyle -- add window style
*                                   
*   Description     Adds to the window style structure from
*                   the generated structure
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT addwstyle(nam,ctrl,fch,bd,bg,say,get,nget,tit,rtit,ltit,btit,stat)
TEXT *nam;
COUNT ctrl;
COUNT fch;
COUNT bd;
COUNT bg;
COUNT say;
COUNT get;
COUNT nget;
COUNT tit;
COUNT rtit;
COUNT ltit;
COUNT btit;
COUNT stat;
    {
    WSTYLE *nstyle,*fstyle,*pstyle;
    TEXT *vcalloc();
    COUNT std2attr();
#ifdef VCDEBUG
    vcdebug = (TEXT *)"addwstyle";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    nstyle = (WSTYLE *)vcalloc(1,sizeof(*nstyle),vcdebug);
    nstyle->wstylnext = (WSTYLE *)0;
    nstyle->wstylnam = nam;
    nstyle->wstylctrl = ctrl;
    nstyle->wstylfch = fch;
    nstyle->wstylbd = std2attr(bd);
    nstyle->wstylbg = std2attr(bg);   
    nstyle->wstylsay = std2attr(say);
    nstyle->wstylget = std2attr(get);  
    nstyle->wstylnget = std2attr(nget); 
    nstyle->wstyltit = std2attr(tit);  
    nstyle->wstylrtit = std2attr(rtit); 
    nstyle->wstylltit = std2attr(ltit); 
    nstyle->wstylbtit = std2attr(btit); 
    nstyle->wstylstat = std2attr(stat); 
    if((wdoctrl->wstyle == (WSTYLE *)0) || 
       (wdoctrl->wstyle->wstylnam[0] == '\0'))
        wdoctrl->wstyle = nstyle;
    else
        {
        fstyle = wdoctrl->wstyle;
        while( (fstyle != (WSTYLE *)0) && (fstyle->wstylnam[0] != '\0'))
            {
            pstyle = fstyle;
            fstyle = pstyle->wstylnext;
            }
        pstyle->wstylnext = nstyle;
        }
    return(0);
    }

    


