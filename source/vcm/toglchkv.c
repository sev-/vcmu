/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:30
*
*   Name            toglchkvar - toggles a menu 'check variable'                 
*                                   
*   Description     In a checked menu item, this will toggle the
*                   associated variable from on to off or off to on.
*                   This works on the current menu item.
*
*   Return Value    VOID
*                                   
**/                                 

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VOID toglchkvar(m)
VCMENU *m;
    {
    if( (m->mcuritmptr->ectrl & CHECKED) && m->mcuritmptr->eparm.pnumptr )
        {
        if( *m->mcuritmptr->eparm.pnumptr )
            *m->mcuritmptr->eparm.pnumptr = FALSE;
        else
            *m->mcuritmptr->eparm.pnumptr = TRUE;
        }
    }


