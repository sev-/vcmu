/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:21
*
*   Name            menuxxitem.c  --  Extended menu item
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

MENUITEM *menuxxitem(menuptr,item,keynam,keynum,func,parm,stat,hlpkey,
                                        ctrl,mctrl,mbuf)
VCMENU *menuptr;    /* Pointer to menu to add item                  */
TEXT *item;         /* Item to add to menu                          */
TEXT *keynam;       /* String description of keystroke              */
COUNT keynum;       /* Key code of key used for direct keystroke    */
PFI func;           /* Function to execute if this item selected    */
TEXT *parm;         /* Parameter to pass to function                */
TEXT *stat;         /* Pointer to status line message for this item */
TEXT *hlpkey;       /* Pointer to help text for this item           */
COUNT ctrl;         /* Control byte for this item                   */
COUNT mctrl;        /* Screen Control byte                          */
TEXT *mbuf;         /* Screen buffer                                */
    {
    MENUITEM *tmp;
    TEXT *vcalloc();
    COUNT ntmp;
    COUNT strlen();
    if( menuptr->mmagic != MENUMAGIC )
        {
        vcerror = BADMENU;
        return((MENUITEM *)0);
        }
    if( (tmp=(MENUITEM *)vcalloc(1,sizeof(MENUITEM),NULLTEXT)) == (MENUITEM *)0 )
        {
        return((MENUITEM *)0);
        }
    tmp->eitemname=item;
    tmp->ekeyname=keynam;
    tmp->ekeynum=keynum;
    tmp->efunc=func;
    if( ctrl & STRPARM )
        tmp->eparm.pchrptr=parm;
    else if( (ctrl & MENU) && parm )
        tmp->eparm.pmnuptr=(VCMENU *)parm;
    else
        tmp->eparm.pnumptr=(COUNT *)parm;
    tmp->ectrl=ctrl;
    tmp->estat=stat;
    tmp->ehelpkey=hlpkey;
    tmp->emctrl = mctrl;
    tmp->embuf = mbuf;
    tmp->enext = (MENUITEM *)0;
    if( menuptr->mitemhead == (MENUITEM *)0 )
        {
        menuptr->mitemtail = menuptr->mitemhead = tmp;
        tmp->eprev = (MENUITEM *)0;
        }
    else
        {
        tmp->eprev=menuptr->mitemtail;
        menuptr->mitemtail->enext = tmp;
        menuptr->mitemtail=tmp;
        }
    menuptr->mitemcnt++;
    tmp->eitemnbr=menuptr->mitemcnt;
    if( keynam && *keynam )
        ntmp=strlen(keynam);
    else
        ntmp=0;
    if( ntmp > menuptr->mknamwid )
        menuptr->mknamwid=ntmp;
    if(item != NULLTEXT)
        ntmp = strlen(item);
    if( ntmp > menuptr->mitemwid )
        menuptr->mitemwid = ntmp;
    if( ctrl & CHECKED )
        menuptr->mchecks=1;
    tmp->emagic=MITEMMAGIC;
    return(tmp);
    }


