/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:16
*
*   Name            lstsellst.c -- List selection set
*
*   Description     List the selection set 
*                   
*   Return Value    VOID
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

VOID lstsellst(list)
SELSET *list;       /* Pointer to selection list                    */
   {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "lstsellst:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   while( list )
      {
      printf("\n'%s'   '%s'",list->idisplay,list->ivalue);
      list=list->inext;
      }
   }
#endif


