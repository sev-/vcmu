/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:20:59
*
*   Name            wclose.c  --  Closes window and updates screen
*
*   Description     Removes the window from screen and releases memory
*                   used to store window.  After a call to this function
*                   the window is no longer accessable.
*
*   Return Value    Return -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT wclose(wptr)
PFAST WPTR wptr;    /* Pointer to window to close                   */
    {
    VOID wstack();
    VOID wcutout();
    WPTR wselect();
    VOID wplace_cur();
    COUNT whidden();
    COUNT wlistdel();
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wclose:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((wptr->wctrl & WOPEN))
        wptr->wctrl &= ~WOPEN;
    else
        {
        vcerror = CLNOTOPEN;
        return(-1);
        }
    if(wptr->wctrl & ACTIVE)
        {
        wptr->wctrl &= ~ACTIVE;
        wstack((WPTR)0);
        wcutout(wptr);
        (*wdoctrl->wclfunc)(wptr);
        wdoctrl->wno_active -= 1;
        }
    else
        {
        if(whidden(wptr))
            {
            wcutout(wptr);
            wdoctrl->wno_active -= 1;
            }
        }
    if(wdoctrl->wcurrent == wptr)
        {
        if(wdoctrl->wdtail != (WPTR) 0)
            wselect(wdoctrl->wdtail);
        }
    else
        wplace_cur(wdoctrl->wcurrent);
    wdoctrl->wno_opn -= 1;
    wlistdel(wptr);
    if(wptr->title != NULLTEXT)
        vcfree(wptr->title,vcdebug);
    if(wptr->rtitle != NULLTEXT)
        vcfree(wptr->rtitle,vcdebug);
    if(wptr->ltitle != NULLTEXT)
        vcfree(wptr->ltitle,vcdebug);
    if(wptr->btitle != NULLTEXT)
        vcfree(wptr->btitle,vcdebug);
    vcfree(wptr->location,vcdebug);
    vcfree(wptr,vcdebug);
    return(0);
    }

COUNT wlistdel(wptr)
WPTR wptr;        /* Pointer to window to del from list          */
    {
    WPTR cptr,pptr=(WPTR)0;
    cptr = wdoctrl->whead;
    while((cptr != wptr) && (cptr != (WPTR)0))
        {
        pptr = cptr;
        cptr = pptr->wdlist;
        }
    if(cptr == (WPTR)0 )
        return(0);
    if(cptr == wdoctrl->whead)
        {
        wdoctrl->whead = wptr->wdlist;
        }
    else
        {
        pptr->wdlist = wptr->wdlist;
        }
    if(cptr == wdoctrl->wtail)
        {
        wdoctrl->wtail = pptr;
        }
    return(0);
    }

#endif

