/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:12
*
*   Name            wdefopen -- open window by definiton
*                                   
*   Description     Opens a window by the window definition
*
*   Return Value    Returns window pointer or NULL if error
*                                   
**/                                 

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

WPTR wdefopen(wdef)
TEXT *wdef;
    {
    WDEF *wd,*getwdef();
    WPTR wdefinit();
    if((wd = getwdef(wdef)) == (WDEF *)0)
        return((WPTR)0);
    return(wdefinit(wd->wdefname,wd->wdefstyle,wd->wdeftitle,
             wd->wdefrtitle,wd->wdefltitle,wd->wdefbtitle,
             wd->wdefur,wd->wdefuc,wd->wdeflr,wd->wdeflc,
             wd->wdefwid,wd->wdefdep,wd->wdefsmer,wd->wdefbmer));
    }
