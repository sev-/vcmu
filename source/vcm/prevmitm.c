/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:26
*
*   Name            prevmitm -- moves to previous menu item                 
*                                   
*   Description     Used by vcmenu() to move to previous menu item.
*                   Automatically skips separators, blank items, and
*                   unavailable items.
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT prevmitm(m)
VCMENU *m;          /* Pointer to menu                              */
   {
   MENUITEM *olditem;
   if( m == (VCMENU *)0 || m->mmagic != MENUMAGIC )
      {
      vcerror = BADMENU;
      return(-1);
      }
   if( m->mcuritmptr == (MENUITEM *)0 || m->mcuritmptr->emagic != MITEMMAGIC )
      {
      vcerror = BADMITEM;
      return(-1);
      }
   olditem=m->mcuritmptr;
   do
      {
      if( m->mcuritmptr->emagic != MITEMMAGIC )
         {
         vcerror = BADMITEM;
         return(-1);
         }
      if(m->mcuritmptr->eprev)
         m->mcuritmptr = m->mcuritmptr->eprev;
      else
         m->mcuritmptr = m->mitemtail;
      m->mcuritmnbr = m->mcuritmptr->eitemnbr;
      if( m->mcuritmptr == olditem )
         {
         vcerror = CANNOT;  /*No other items available*/
         return(0);
         }
      } while((m->mcuritmptr->ectrl & UNAVAILABLE) ||
              (m->mcuritmptr->ectrl & SEPARATOR) ||
              (m->mcuritmptr->ectrl & BLANKITEM) );
   return(0);
   }



