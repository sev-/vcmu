/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:11
*
*   Name            initmenu.c  --  Init from menu structure
*
*   Description     This function initializes menu using the menu
*                   structures
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT initmenu(style,menu,item)
SSTYLES *style;     /* Pointer to style structure to initialize     */
SMENUS *menu;       /* Pointer to menu structure to initialize      */
SMENUITEMS *item;   /* Pointet to menu item structure to initialize */
    {
    VCMENU *menuxnew(),*menunew();
    VCMENU *getmnuptr();
    MENUITEM *menuxxitem();
    TEXT *ptr;
    COUNT addmstyle();
    COUNT std2attr();
    COUNT std2cord();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "initmenu:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( style != (SSTYLES *)0)
        {
        while(style->istylename != NULLTEXT)
            {
            addmstyle(style->istylename,style->imnustyle,
                    style->iswidth,std2attr(style->isnormattr),
                    std2attr(style->isbarattr),std2attr(style->isunavattr),
                    std2attr(style->isbordattr),style->ispermlvl);
            style++;
            }
       }
    if(menu != (SMENUS *)0)
        {
        while(menu->smnunam != NULLTEXT)
            {
            if( ( menunew(std2cord(menu->srow),std2cord(menu->scol),
                        menu->smnunam,menu->shlpkey,menu->sstyle) ) 
                                                == (VCMENU *)0)
                {
                return(-1);
                }
            menu++;
            }
        }
    if(item != (SMENUITEMS *)0)
        {
        while(item->imenu != NULLTEXT)
            {
            if(item->ictrl & MENU)
                ptr = (TEXT *)getmnuptr(item->iparm);
            else
                ptr = item->iparm;
            if(menuxxitem(getmnuptr(item->imenu),item->iitem,
                         item->ikeynam,item->ikeynum,
                         item->ifunc,ptr,item->istat,
                         item->ihlpkey,item->ictrl,
                         item->imctrl,item->imbuf) == (MENUITEM *) 0)
                {
                return(-1);
                }
            item++;
            }
        }        
    return(0);
    }

