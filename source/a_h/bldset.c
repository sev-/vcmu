/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:58
*
*   Name            bldset.c --  Build selection set
*
*   Description     Builds selection set from simple array
*                   
*   Return Value    Always return pointer to head of select list
*                   must check vcerror for errors
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

SELSET *bldset(array)
TEXT *array[];      /* Pointer to special array                     */
   {
   SELSET *addselitm();
   SELSET *list = (SELSET *) 0;
   SELSET *retval;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "bldset:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   while( array && *array )
      {
      if( (retval = addselitm(list,*array,*array)) == (SELSET *) 0 )
         {
         vcerror='?';
         return(list);
         }
      if( list == (SELSET *) 0 )
         list=retval;
      array++;
      }
   vcerror=0;
   return(list);
   }
#endif


