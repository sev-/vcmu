/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:37
*
*   Name            aloselitm.c --  Allocate select item
*
*   Description     Allocates space for a select item
*                   
*   Return Value    Return NULL if error else returns pointer to
*                   allocated space for select item
*
**/

#define SEL_DEFS
#include <vcstdio.h>

#ifdef WINDOW

SELSET *aloselitm()
   {
   SELSET *ptr;
   TEXT *vcalloc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "aloselitm:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   if( (ptr=(SELSET *)vcalloc(1,sizeof(SELSET),vcdebug)) == (SELSET *) 0)
      vcerror='?';
   else
      ptr->imagic=SELITEMMAGIC;
   return(ptr);
   }

#endif


