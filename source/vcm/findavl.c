/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:05
*
*   Name            findavl.c  --  find the next available item
*
*   Description     This function finds the next available items. 
*                   Skips over unavialable and separators.
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT findavl(m)
VCMENU *m;          /* Pointer to menu                              */
    {
    MENUITEM *olditem;
    if( m == (VCMENU *)0 || m->mmagic != MENUMAGIC)
        {
        vcerror = BADMENU;
        return(-1);
        }
    if( m->mcuritmptr == (MENUITEM *)0 || m->mcuritmptr->emagic != MITEMMAGIC )
        {
        vcerror = BADMITEM;
        return(-1);
        }
    olditem = m->mcuritmptr;
    while( (m->mcuritmptr->ectrl & UNAVAILABLE) ||
           (m->mcuritmptr->ectrl & SEPARATOR) ||
           (m->mcuritmptr->ectrl & BLANKITEM) )
        {
        if(m->mcuritmptr->emagic != MITEMMAGIC)
            {
            vcerror = BADMITEM;
            return(-1);
            }
        if(m->mcuritmptr->enext)
            m->mcuritmptr = m->mcuritmptr->enext;
        else
            m->mcuritmptr = m->mitemhead;
        m->mcuritmnbr = m->mcuritmptr->eitemnbr;
        if(m->mcuritmptr == olditem)
            {
            vcerror = CANNOT;
            return(0);
            }
        }
    return(0);
    }


