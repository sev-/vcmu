/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:22
*
*   Name            getselitm.c -- Get selection item
*
*   Description     Gets the pointer to an item in a selection
*                   set.
*                   
*   Return Value    Returns pointer to select item or NULL if
*                   error.
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

SELSET *getselitm(list,display,value)
SELSET *list;       /* Pointer to selection list                    */
TEXT *display;      /* Pointer to display string                    */
TEXT *value;        /* Pointer to data entry string                 */
    {
    COUNT dtst=0,vtst=0;
    COUNT strcmp();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getselitm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( list == (SELSET *) 0 || list->imagic != SELITEMMAGIC )
        {
        vcerror='?';
        return((SELSET *)0);
        }
    list = list->inext;
    while( list )
        {
        if((display != NULLTEXT) && (list->idisplay != NULLTEXT))
            dtst=strcmp(display,list->idisplay);
        if((value != NULLTEXT) && (list->ivalue != NULLTEXT))
            vtst=strcmp(value,list->ivalue);
        if((dtst == 0) && (vtst == 0))
            return(list);
        list=list->inext;
        }
    vcerror='?';
    return((SELSET *)0);
    }
#endif


