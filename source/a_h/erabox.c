/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:46
*
*   Name            erabox.c  --  Erase a box
*
*   Description     Erases a box with default attributes
*                   described by up,lf and lo,rt by calling
*                   xerabox() or werabox() with the proper 
*                   attribute.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID erabox(up,lf,lo,rt)
COUNT up,lf;        /* Upper left corner                            */
COUNT lo,rt;        /* Lower right corner                           */
    {
    VOID werabox();
    VOID xerabox();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "erabox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wdoctrl->wno_opn && !override)
        werabox(wdoctrl->wcurrent,up,lf,lo,rt,vc.dflt);
    else
#endif
        xerabox(up,lf,lo,rt,normattr);
    }

