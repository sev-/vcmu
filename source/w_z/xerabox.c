/** 
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:16
*
*   Name            xerabox.c  --  eXtended erase a box
*
*   Description     Erases a box described by up,lf and lo,rt 
*                   with attr as attribute
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID xerabox(up,lf,lo,rt,attr)
COUNT up,lf;        /* Upper left corner                            */
COUNT lo,rt;        /* Lower right corner                           */
COUNT attr;         /* Attribute for cleared area                   */
    {
#ifdef TERMINAL
    COUNT flow = 0;
#endif
    VOID werabox();
    COUNT vcpee();
    VOID clbx();
    VOID vcflush();
    VOID scrollup();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xerabox:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if( attr==-1 )
        if( wdoctrl->wno_opn && !override )
            attr=wdoctrl->wcurrent->bg_at;
        else
            attr=normattr;
    if(wdoctrl->wno_opn && !override)
        werabox(wdoctrl->wcurrent,up,lf,lo,rt,attr);
    else
#else
    if(attr == -1)
        attr=normattr;
#endif
#ifdef IBM
#ifdef TERMINAL
        if(vctio == 5)
            {
            flow=vcpee();
            clbx(up,lf,lo,rt,attr);
            if(flow)
                vcflush();
            }
        else
#endif
            scrollup(up,lf,lo,rt,0,attr);
#endif
#ifdef TERMONLY
        {
        flow=vcpee();
        clbx(up,lf,lo,rt,attr);
        if(flow)
            vcflush();
        }
#endif
#ifdef OS2
#ifdef TERMINAL
        if(vctio == 5)
            {
            flow=vcpee();
            clbx(up,lf,lo,rt,attr);
            if(flow)
                vcflush();
            }
        else
#endif
            scrollup(up,lf,lo,rt,-1,attr);
#endif
    }


