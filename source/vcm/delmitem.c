/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:00
*
*   Name            delmitem -- Deletes a menu item                 
*                                   
*   Description     Given a pointer to a menu and an item name, will
*                   search that menu for that item name.  If found,
*                   it will delete the item.
*
*   Return Value    Returns 1 if error , 0 if no error
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT  delmitem(mnuptr,itmnam)
VCMENU *mnuptr;             /* Pointer to menu to look for item     */
TEXT *itmnam;               /* Item to delete                       */
    {
    COUNT retval = 1;
    MENUITEM *ptr,*tptr;
    MENUITEM *getmnuitm();
    if((mnuptr != (VCMENU *)0) && (itmnam != NULLTEXT) &&
       ((ptr = getmnuitm(mnuptr,itmnam)) != (MENUITEM *)0) )
        {
        retval = 0;
        mnuptr->mitemcnt--;
        if(ptr == mnuptr->mitemhead)
            mnuptr->mitemhead = ptr->enext;
        if(ptr == mnuptr->mitemtail)
            mnuptr->mitemtail = ptr->eprev;
        if(ptr->enext != (MENUITEM *)0)
            ptr->enext->eprev = ptr->eprev;
        if(ptr->eprev != (MENUITEM *)0)
            ptr->eprev->enext = ptr->enext;
        tptr = ptr->enext;
        if(ptr->ectrl & MENU)
            delmenu(ptr->eparm.pmnuptr);
        vcfree(ptr,NULLTEXT);
        while(tptr != (MENUITEM *)0)
            {
            tptr->eitemnbr--;
            tptr = tptr->enext;
            }
        }
    return(retval);
    }



