/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:00
*
*   Name            bldxset.c --  Extended build set
*
*   Description     Builds a set with different choice and return
*                   values.
*                   
*   Return Value    Always return pointer to head of select list
*                   must check vcerror for errors
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

SELSET *bldxset(array)
TEXT *array[];      /* Pointer to array                             */
   {
   SELSET *addselitm();
   SELSET *list = (SELSET *)0;
   SELSET *retval;
   TEXT *dispptr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "bldxset:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   while( array && *array )
      {
      dispptr = *array;
      array++;
      if( (retval = addselitm(list,dispptr,*array)) == (SELSET *) 0 )
         {
         vcerror='?';
         return(list);
         }
      if( list == (SELSET *)0)
         list = retval;
      if( array )
         array++;
      }
   vcerror=0;
   return(list);
   }
#endif



