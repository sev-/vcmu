/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:02
*
*   Name            delmstyle.c  --  Delete menu style
*
*   Description     This function deletes a menu style
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT delmstyle(stylename)
TEXT *stylename;    /* Pointer to name of style to delete           */
   {
   MENUSTYLE *ptr,*prevptr;
   COUNT strcmp();
   VOID vcfree();
   ptr= &vcmstyle;
   if( ptr->smagic != MSTYLEMAGIC )
      {
      vcerror = BADMSTYLE;
      return(-1);
      }
   if( ptr->snext == (MENUSTYLE *)0 )
      {
      vcerror = ONLYMSTYLE;   /* Can not delete only member in list */
      return(-1);
      }
   prevptr=ptr;
   ptr=ptr->snext;

   while( ptr && strcmp(ptr->stylename,stylename)!=0 )
      {
      if( ptr->smagic != MSTYLEMAGIC )
         {
         vcerror = BADMSTYLE;
         return(-1);
         }
      prevptr=ptr;
      ptr = ptr->snext;
      }

   if( ptr )
      {
      prevptr->snext = ptr->snext;
      vcfree(ptr,NULLTEXT);
      return(0);
      }
   vcerror = NOMSTYLE;
   return(-1);
   }


