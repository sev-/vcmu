/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:18
*
*   Name            menuxitem.c  --  Extended menu item
*
*   Description     This function allow an item to be added to a
*                   menu with more programmer control
*
*   Return Value    Returns pointer to menu item or NULL if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

MENUITEM *menuxitem(menuptr,item,keynam,keynum,func,parm,stat,hlpkey,
                                        ctrl)
VCMENU *menuptr;    /* Pointer to menu to add item                  */
TEXT *item;         /* Item to add to menu                          */
TEXT *keynam;       /* String description of keystroke              */
COUNT keynum;       /* Key code of key used for direct keystroke    */
PFI func;           /* Function to execute if this item selected    */
TEXT *parm;         /* Parameter to pass to function                */
TEXT *stat;         /* Pointer to status line message for this item */
TEXT *hlpkey;       /* Pointer to help text for this item           */
COUNT ctrl;         /* Control byte for this item                   */
   {
   MENUITEM *menuxxitem();
   return(menuxxitem(menuptr,item,keynam,keynum,func,parm,stat,
                      hlpkey,ctrl,0,NULLTEXT));
   }


