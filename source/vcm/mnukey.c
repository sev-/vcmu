/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:22
*
*   Name            mnukey -- jump to menu item by single keystroke                 
*                                   
*   Description     Scans the menu items of the indicated menu for a
*                   matching key code.  Search begins at the current
*                   item and will, if necessary, wrap around the end
*                   of the menu back to the top and continue searching
*                   until it reaches the point at which it started.  
*                   If a match is found, the current pointer and line 
*                   number are changed, otherwise, they are left intact 
*                   and unchanged.
*
*   Return Value    If a match is found, a non-zero value is returned,
*                   otherwise, zero is returned.
*
**/                 

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT mnukey(m)
VCMENU *m;          /* Pointer to menu                              */
    {
    MENUITEM *olditm;
    COUNT oldlin;
    olditm=m->mcuritmptr;
    oldlin=m->mcuritmnbr;
    m->mcuritmptr = m->mcuritmptr->enext;
    m->mcuritmnbr++;
    /* First, search for a global menu key */
    while( m->mcuritmptr )
        {
        if( m->mkeyhit==m->mcuritmptr->ekeynum &&
          !(m->mcuritmptr->ectrl & SEPARATOR ) &&
          !(m->mcuritmptr->ectrl & BLANKITEM ) &&
          !(m->mcuritmptr->ectrl & UNAVAILABLE) )
            {
            if(m->mstyle & AUTOMENU)
                ungetone(vckey.ret);
            return( TRUE );
            }
        m->mcuritmptr = m->mcuritmptr->enext;
        m->mcuritmnbr++;
        }
    m->mcuritmptr = m->mitemhead;
    m->mcuritmnbr=1;
    while( m->mcuritmptr != olditm->enext )
        {
        if( m->mkeyhit==m->mcuritmptr->ekeynum &&
          !(m->mcuritmptr->ectrl & SEPARATOR ) &&
          !(m->mcuritmptr->ectrl & BLANKITEM ) &&
          !(m->mcuritmptr->ectrl & UNAVAILABLE) )
            {
            if(m->mstyle & AUTOMENU)
                ungetone(vckey.ret);
            return( TRUE );
            }
        m->mcuritmptr = m->mcuritmptr->enext;
        m->mcuritmnbr++;
        }
    m->mcuritmnbr=oldlin;
    m->mcuritmptr=olditm;
    m->mcuritmptr = m->mcuritmptr->enext;
    m->mcuritmnbr++;
    while( m->mcuritmptr )
        {
        if( (m->mcuritmptr->eitemname != NULLTEXT) &&
           toupper(m->mkeyhit)==toupper(m->mcuritmptr->eitemname[0]) &&
           !(m->mcuritmptr->ectrl & SEPARATOR ) &&
           !(m->mcuritmptr->ectrl & BLANKITEM ) &&
           !(m->mcuritmptr->ectrl & UNAVAILABLE) )
            {
            if(m->mstyle & AUTOMENU)
                ungetone(vckey.ret);
            return( TRUE );
            }
        m->mcuritmptr = m->mcuritmptr->enext;
        m->mcuritmnbr++;
        }
    m->mcuritmptr = m->mitemhead;
    m->mcuritmnbr=1;
    while( m->mcuritmptr != olditm->enext )
        {
        if( (m->mcuritmptr->eitemname != NULLTEXT) &&
           toupper(m->mkeyhit)==toupper(m->mcuritmptr->eitemname[0]) &&
           !(m->mcuritmptr->ectrl & SEPARATOR ) &&
           !(m->mcuritmptr->ectrl & BLANKITEM ) &&
           !(m->mcuritmptr->ectrl & UNAVAILABLE) )
            {
            if(m->mstyle & AUTOMENU)
                ungetone(vckey.ret);
            return( TRUE );
            }
        m->mcuritmptr = m->mcuritmptr->enext;
        m->mcuritmnbr++;
        }
    m->mcuritmnbr=oldlin;
    m->mcuritmptr=olditm;
    return(0);
    }


