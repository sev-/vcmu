/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:30
*
*   Name            delprokey.c  --  remove programmed key
*
*   Description     This function removes a definition for the 
*                   list of programmed keys
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCPRO_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

extern VCPROKEY *prokeytbl;

COUNT delprokey(key)
COUNT key;
   {
   VCPROKEY *kp,*kc;
   VOID vcfree();
   kc=kp=prokeytbl;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "delprokey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   while( kc != (VCPROKEY *) 0 )
      {
      if( kc->pro_keycode == key )
         {
         if( kc == prokeytbl )
            prokeytbl = kc->pro_next;
         else
            kp->pro_next = kc->pro_next;
         vcfree(kc,vcdebug);
         return(0);
         }
      kp = kc;
      kc = kc->pro_next;
      }
   vcerror= VCNOSYM;
   return(-1);
   }


