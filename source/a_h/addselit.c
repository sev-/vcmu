/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:24
*
*   Name            addselitm.c -- Add or Create a Selection set
*
*   Description     Allows initialization and addition to a selection
*                   set
*                   
*   Return Value    Returns NULL if error
*
**/

#define SEL_DEFS

#include <vcstdio.h>

#ifdef WINDOW

SELSET *addselitm(list,display,value)
SELSET *list;       /* Pointer to selection list                    */
TEXT *display;      /* Pointer to display string                    */
TEXT *value;        /* Pointer to data entry string                 */
    {
    SELSET *newitem;
    SELSET *aloselitm();
    TEXT *vcalloc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "addselitm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (newitem = aloselitm()) == (SELSET *) 0 )
        return((SELSET *)0);
    if(display != NULLTEXT)
        {
        newitem->idisplay = vcalloc(1,strlen(display)+1,vcdebug);
        strcpy(newitem->idisplay,display);
        }
    if(value != NULLTEXT)
        {
        newitem->ivalue = vcalloc(1,strlen(value)+1,vcdebug);
        strcpy(newitem->ivalue,value);
        }
    if(list)
        {
        while(list->inext)
            list = list->inext;
        list->inext = newitem;
        newitem->iprev = list;
        }
    return(newitem);
    }
#endif
