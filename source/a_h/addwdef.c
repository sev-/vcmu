/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:28
*
*   Name            addwdef -- add window definition
*                                   
*   Description     Adds to the window definition structure from
*                   the generated structure
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT addwdef(name,style,title,rtitle,ltitle,btitle,
                ur,uc,lr,lc,wid,dep,smer,bmer)
TEXT *name;
TEXT *style;
TEXT *title;
TEXT *rtitle;
TEXT *ltitle;
TEXT *btitle;
COUNT ur,uc;
COUNT lr,lc;
COUNT wid;
COUNT dep;
COUNT smer,bmer;
    {
    WDEF *ndef,*fdef,*pdef;
    TEXT *vcalloc();
    COUNT std2cord();
#ifdef VCDEBUG
    vcdebug = (TEXT *)"addwdef";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ndef = (WDEF *)vcalloc(1,sizeof(*ndef),vcdebug);
    ndef->wdefnext = (WDEF *)0;
    ndef->wdefname = name;
    ndef->wdefstyle = style;  
    ndef->wdeftitle = title;  
    ndef->wdefrtitle = rtitle; 
    ndef->wdefltitle = ltitle;
    ndef->wdefbtitle = btitle; 
    ndef->wdefur = std2cord(ur);
    ndef->wdefuc = std2cord(uc);
    ndef->wdeflr = std2cord(lr);
    ndef->wdeflc = std2cord(lc);
    ndef->wdefwid = wid;
    ndef->wdefdep = dep;
    ndef->wdefsmer = smer;
    ndef->wdefbmer = bmer;
    if((wdoctrl->wdefine == (WDEF *)0) || 
       (wdoctrl->wdefine->wdefname[0] == '\0'))
        wdoctrl->wdefine = ndef;
    else
        {
        fdef = wdoctrl->wdefine;
        while( (fdef != (WDEF *)0) && (fdef->wdefname[0] != '\0'))
            {
            pdef = fdef;
            fdef = pdef->wdefnext;
            }
        pdef->wdefnext = ndef;
        }
    return(0);
    }
