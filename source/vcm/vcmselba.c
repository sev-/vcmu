/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:29
*
*   Name            vcselbar -- highlights/unhighlights menu bar                 
*                                   
*   Description     Used internally to move selection bar on menu                 
*                                   
*   Return Value    VOID
*
**/                                 

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VOID vcmselbar(m,mode)
VCMENU *m;          /* Pointer to menu to process                   */
COUNT mode;         /* Highlighting ON or OFF                       */
    {
    COUNT attr,bdofst;
    COUNT col;
    VOID at();
    COUNT wputattr();
    COUNT strlen();
    bdofst = (m->mstyle & BORDERLESS) ? 1 : 0;
    attr = (mode==ON) ? m->mbarattr : m->mnormattr;
    if( m->mstyle & VERTICAL )
        {
        col = 1-bdofst;
        at(m->mcuritmnbr-bdofst,col);
        wputattr(m->mwptr,attr,
             (bdofst) ? m->mwptr->width : m->mwptr->width-2);
        }
    else
        {
        col = m->mcuritmptr->ehcoords & 0xff;
        at(m->mcuritmptr->ehcoords >> 8,col);
        wputattr(m->mwptr,attr,strlen(m->mcuritmptr->eitemname));
        }
    }


