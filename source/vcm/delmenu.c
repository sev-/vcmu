/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:59
*
*   Name            delmenu.c -- deletes a menu
*                                   
*   Description     Deletes a menu and all menu items
*
*   Return Value    Returns 1 if error , 0 if no error
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT delmenu(mptr)
VCMENU *mptr;               /* Pointer to menu to delete            */
    {
    COUNT retval = 1;
    MENUITEM *ptr,*tptr;
    if(mptr != (VCMENU *)0)
        {
        if(mptr == vcmchain)
            vcmchain = mptr->mnext;
        if(mptr->mprev != (VCMENU *)0)
            mptr->mprev->mnext = mptr->mnext;
        if(mptr->mnext != (VCMENU *)0)
            mptr->mnext->mprev = mptr->mprev;
        ptr = mptr->mitemhead;
        vcfree(mptr,NULLTEXT);
        retval = 0;
        while(ptr != (MENUITEM *)0)
            {
            tptr = ptr->enext;
            if(ptr->ectrl & MENU)
                delmenu(ptr->eparm.pmnuptr);
            vcfree(ptr,NULLTEXT);
            ptr = tptr;
            }
        }
    return(retval);
    }




