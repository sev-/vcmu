/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:10
*
*   Name            wdefinit -- open window by wstyle/definiton
*                                   
*   Description     Opens a window by the window style/definition
*
*   Return Value    Returns window pointer or NULL if error
*                                   
**/                                 

#define VCERROR_DEFS
#include <vcstdio.h>

WPTR wdefinit(name,style,title,rtitle,ltitle,btitle,ur,uc,lr,lc,
                                                wid,dep,smer,bmer)
TEXT *name;                 /* Pointer to Window Name               */
TEXT *style;                /* Pointer to Name of Window Style      */
TEXT *title;                /* Pointer to Title for window          */
TEXT *rtitle;               /* Pointer to Right Title for window    */
TEXT *ltitle;               /* Pointer to Left Title for window     */
TEXT *btitle;               /* Pointer to Bottom Title for wdo      */
COUNT ur;                   /* Upper Right                          */
COUNT uc;                   /* Upper Left                           */
COUNT lr;                   /* Lower Right                          */
COUNT lc;                   /* Lower Left                           */
COUNT wid;                  /* Width of the Actual Window           */
COUNT dep;                  /* Depth of the Actual Window           */
COUNT smer;                 /* Side Merge Location                  */
COUNT bmer;                 /* Bottom Merge Location                */
    {
    COUNT len;
    WPTR wptr,wsetup();
    WSTYLE *ws,*getwstyle();
    TEXT *vcalloc();
    COUNT winit();
    FAST COUNT bd;
    if((ws = getwstyle(style)) == (WSTYLE *)0)
        return((WPTR)0);
    bd = (ws->wstylctrl & BORDER ? 1 : 0);
    if( (ur+(bd << 1) > lr) || (uc+(bd << 1) > lc) || 
        (lc > vcterm.cols-1) || (lr > vcterm.rows-1) || 
        (ur < 0) || (uc < 0) )
        {
        vcerror = WCORD;
        return((WPTR) 0);
        }
    wptr = wsetup(name,ws->wstylctrl,ur,uc,lr,lc,ws->wstylfch,
                    ws->wstylbg,ws->wstylbd,ws->wstylsay,ws->wstylget,
                    ws->wstylnget,ws->wstyltit,title,dep,wid);
    if(wptr != (WPTR)0)
        {
        wptr->rtit_at = ws->wstylrtit;
        wptr->ltit_at = ws->wstylltit;
        wptr->btit_at = ws->wstylbtit;
        wptr->stat_at = ws->wstylstat;
        wptr->smerge = smer;
        wptr->bmerge = bmer;
        if(rtitle != NULLTEXT)
            {
            len = strlen(rtitle);
            if((wptr->rtitle = vcalloc(sizeof(TEXT),(UCOUNT)len+1,vcdebug)) != 
                                  NULLTEXT)
                strcpy(wptr->rtitle,rtitle);
            }
        if(ltitle != NULLTEXT)
            {
            len = strlen(ltitle);
            if((wptr->ltitle = vcalloc(sizeof(TEXT),(UCOUNT)len+1,vcdebug)) != 
                                  NULLTEXT)
                strcpy(wptr->ltitle,ltitle);
            }
        if(btitle != NULLTEXT)
            {
            len = strlen(btitle);
            if((wptr->btitle = vcalloc(sizeof(TEXT),(UCOUNT)len+1,vcdebug)) != 
                                  NULLTEXT)
                strcpy(wptr->btitle,btitle);
            }
        }
    else
        wptr->title = NULLTEXT;
    if( winit(wptr) == -1)
        return((WPTR)0);
    return(wptr);
    }
