/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:33
*
*   Name            delselset.c -- Delete selection set
*
*   Description     Deletes the selection set
*                   
*   Return Value    Returns a 1 if error
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

COUNT delselset(list)
SELSET *list;               /* Pointer to selection set to delete   */
    {
    COUNT retval = 1;
    SELSET *lptr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "delselset:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while(list != (SELSET *)0)
        {
        if(list->idisplay != NULLTEXT)
            vcfree(list->idisplay,vcdebug);
        if(list->ivalue != NULLTEXT)
            vcfree(list->ivalue,vcdebug);
        lptr = list->inext;
        vcfree(list,vcdebug);
        list = lptr;
        retval = 0;
        }
    return(retval);
    }
#endif



