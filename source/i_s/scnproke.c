/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:52
*
*   Name            scnprokey.c  --  scan list for code
*
*   Description     This function scans the list of programmed keys
*                   looking for a particular key code.
*
*   Return Value    Returns pointer to VCPROKEY structure of key
*                   if found or NULL if not found
*
*
**/

#define VCPRO_DEFS
#include <vcstdio.h>

VCPROKEY *prokeytbl = (VCPROKEY *) 0;

VCPROKEY *scnprokey( key )
COUNT key;
   {
   VCPROKEY *kp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "scnprokey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   kp=prokeytbl;
   while( kp != (VCPROKEY *) 0 )
      {
      if( kp->pro_keycode == key )
         return(kp);
      kp = kp->pro_next;
      }
   return((VCPROKEY *)0);
   }


