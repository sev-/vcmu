/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:32
*
*   Name            delselitm.c -- Delete select item
*
*   Description     Deletes the select item from the selection
*                   set.
*                   
*   Return Value    Returns a NULL if error
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

SELSET *delselitm(list,selitem)
SELSET *list;       /* Pointer to selection set                     */
SELSET *selitem;    /* Pointer to item to be removed                */
    {
    SELSET *listhead;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "delselitm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((list->imagic != SELITEMMAGIC) ||
       (selitem->imagic != SELITEMMAGIC))
        {
        vcerror='?';
        return((SELSET *)0);
        }
    listhead=list;
    if(selitem->iprev)
        selitem->iprev->inext = selitem->inext;
    else
        listhead=selitem->inext;
    if(selitem->inext)
        selitem->inext->iprev = selitem->iprev;
    if(selitem->idisplay != NULLTEXT)
        vcfree(selitem->idisplay,vcdebug);
    if(selitem->ivalue != NULLTEXT)
        vcfree(selitem->ivalue,vcdebug);
    vcfree(selitem,vcdebug);
    if(listhead == (SELSET *)0)
        vcerror='?';       /* not really an error.  list is now empty */
    return(listhead);
    }
#endif




