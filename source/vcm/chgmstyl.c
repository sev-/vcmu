/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:58
*
*   Name            chgmstyle.c  --  Change menu style
*
*   Description     This function changes menu style
*
*   Return Value    Returns -1 if error
*                                       
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT chgmstyle(styleptr,name,mnustyle,width,norm,bar,unav,bord,permlvl)
MENUSTYLE *styleptr;/* Pointer to menu style to change              */
TEXT *name;         /* Name of menu                                 */
COUNT mnustyle;     /* Style options                                */
COUNT width;        /* Width of menu window                         */
COUNT norm;         /* Attribute for normal items                   */
COUNT bar;          /* Attribute for bar                            */
COUNT unav;         /* Attribute for unavailable                    */
COUNT bord;         /* Attribute for border                         */
COUNT permlvl;      /* Permission level for menu                    */
   {
   if( styleptr == (MENUSTYLE *)0 )
      {
      vcerror = BADMSTYLE;
      return(-1);
      }
   if( styleptr->smagic != MSTYLEMAGIC )
      {
      vcerror = BADMSTYLE;
      return(-1);
      }
   styleptr->stylename=name;
   styleptr->mnustyle=mnustyle;
   styleptr->swidth=width;
   styleptr->snormattr=norm;
   styleptr->sbarattr=bar;
   styleptr->sunavattr=unav;
   styleptr->sbordattr=bord;
   styleptr->spermlvl=permlvl;
   styleptr->smagic=MSTYLEMAGIC;
   return(0);
   }



