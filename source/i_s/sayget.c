/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:49
*
*   Name            sayget.c
*
*   Description     This function displays a getsay item
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VOID sayget(si)
SAYITEM *si;
    {
    COUNT num;
    COUNT attr;
    COUNT haveauth();
    VOID wxatsay();
    VOID xatsay();
    WPTR wselect();
    VOID box();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "sayget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (haveauth(si->snctrl & 127,FLDEDIT) == FALSE) &&
        (haveauth(si->snctrl & 127,FLDVIEW) == FALSE) )
        {
        vcerror = NOSAYAUTH;      /* Not authorized */
        return;
        }
    if(si->snctrl & GETSAY)
        {
#ifdef WINDOW
        if(si->snwptr != (WPTR) 0)
            wxatsay(si->snwptr,si->snrow,si->sncol,si->snfld,si->snattr);
        else
#endif
            xatsay(si->snrow,si->sncol,si->snfld,si->snattr);
        }
    else
        {
        num = (si->snctrl & 384) >> 7;
#ifdef WINDOW
        if(si->snwptr != (WPTR)0)
            {
            if(si->snwptr != wdoctrl->wcurrent)
                wselect(si->snwptr);
            if(si->snattr == -1)
                attr = si->snwptr->border_at;
            else
                attr = si->snattr;
            }
        else
#endif
            attr = si->snattr;
        box(si->snrow,si->sncol,si->snbrow,si->snbcol,num,attr);
        }
    }


