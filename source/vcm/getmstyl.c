/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:09
*
*   Name            getmstyle.c  --  get menu style
*
*   Description     This function get a menu style by name
*
*   Return Value    Returns pointer to style or NULL if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

MENUSTYLE *getmstyle(name)
TEXT *name;         /* Name of style to get location                */
   {
   MENUSTYLE *ptr;
   COUNT strcmp();
   ptr= &vcmstyle;
   if( ptr && (ptr->smagic != MSTYLEMAGIC) )
      {
      vcerror = BADMSTYLE;
      return((MENUSTYLE *)0);
      }
   while( ptr && strcmp(ptr->stylename,name)!=0 )
      {
      ptr = ptr->snext;
      if( ptr->smagic != MSTYLEMAGIC )
         {
         vcerror = BADMSTYLE;
         return((MENUSTYLE *)0);
         }
      }
   if( ptr == (MENUSTYLE *)0 )
      vcerror = NOMSTYLE;      /* style name not found */
   return(ptr);
   }


