/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:20
*
*   Name            menuxnew.c  --  create menu without menu style
*
*   Description     This function creates a menu without menu style
*                   for more control.
*
*   Return Value    Returns pointer to menu or NULL if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VCMENU *menuxnew(row,col,width,mnunam,style,norm,bar,unav,bord,
                            permis,hlpkey)
COUNT row,col;      /* Upper row and column for menu                */
COUNT width;        /* Width of menu window                         */
TEXT *mnunam;       /* Pointer to menu title                        */
COUNT style;        /* Style options                                */
COUNT norm;         /* Attribute for normal items                   */
COUNT bar;          /* Attribute for bar                            */
COUNT unav;         /* Attribute for unavailable items              */
COUNT bord;         /* Attribute for border                         */
COUNT permis;       /* Menu permission level                        */
TEXT *hlpkey;       /* Pointer to help key word                     */
   {
   VCMENU *tmp;
   TEXT *vcalloc();
   if( (tmp=(VCMENU *)vcalloc(1,sizeof(VCMENU),NULLTEXT)) == (VCMENU *)0 )
      return((VCMENU *)0);
   tmp->mmagic=MENUMAGIC;
   tmp->mrow=row;
   tmp->mcol=col;
   tmp->mwidth=width;
   tmp->menuname=mnunam;
   tmp->mstyle=style;
   tmp->mnormattr=norm;
   tmp->mbarattr=bar;
   tmp->munavattr=unav;
   tmp->mbordattr=bord;
   tmp->mhelpkey=hlpkey;
   tmp->mpermlvl=permis;
   if( vcmchain )
      {
      if( tmp->mmagic != MENUMAGIC )
         {
         vcerror = BADMENU;   /* Corupt element in menuchain */
         return((VCMENU *)0);
         }
      tmp->mnext=vcmchain;
      vcmchain->mprev=tmp;
      }
   vcmchain=tmp;
   return(tmp);
   }


