/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:06
*
*   Name            getmnuitm -- finds a menu item                 
*                                   
*   Description     Given a pointer to a menu and an item name, will
*                   search that menu for that item name.  If found,
*                   returns pointer to the item structure.  If no match,
*                   returns NULL.  NOTE: Searches from head to tail, so
*                   will always return FIRST MATCH (can't do next match)
*
*   Return Value    Returns pointer to menu item or NULL if
*                   Not found or error
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

MENUITEM *getmnuitm(mnuptr,itmnam)
VCMENU *mnuptr;     /* Pointer to menu to look for item             */
TEXT *itmnam;       /* Item to find                                 */
   {
   MENUITEM *ptr;
   COUNT strcmp();
   if( mnuptr->mmagic != MENUMAGIC )
      {
      vcerror = BADMENU;
      return((MENUITEM *)0);
      }
   if( itmnam == NULLTEXT)
      return((MENUITEM *)0);
   ptr=mnuptr->mitemhead;
   while( ptr )
      {
      if( ptr->emagic != MITEMMAGIC )
         {
         vcerror = BADMITEM;
         return((MENUITEM *)0);
         }
      if(ptr->eitemname != NULLTEXT)
          if( strcmp(itmnam,ptr->eitemname)==0 )
             return(ptr);
      ptr = ptr->enext;
      }
   vcerror = NOSYM;   /* item name not found*/
   return((MENUITEM *)0);
   }


