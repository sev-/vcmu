/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:07
*
*   Name            getmnuptr -- returns a pointer to a menu structure          
*                                   
*   Description     Searches the menu chain looking for a menu with a
*                   name matching the "menunam" parameter. If found,
*                   a pointer to the menu structure is returned, else
*                   NULL is returned.  Note menu name same as title.
*
*   Return Value    Returns pointer to menu or NULL if error
*
*                                   
**/                                 

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VCMENU *getmnuptr(menunam)
TEXT *menunam;      /* Title of menu to get pointer                 */
   {
   VCMENU *ptr;
   COUNT strcmp();
   ptr=vcmchain;
   if(menunam == NULLTEXT)
       return((VCMENU *)0);
   while( ptr )
      {
      if( ptr->mmagic != MENUMAGIC )
         {
         vcerror = BADMENU;
         return((VCMENU *)0);
         }
      if(ptr->menuname != NULLTEXT)
          if( strcmp(menunam,ptr->menuname)==0 )
             return(ptr);
      ptr = ptr->mnext;
      }
   vcerror = NOSYM;   /*sybmolic table name not found */
   return((VCMENU *)0);
   }



