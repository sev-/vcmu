/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:56
*
*   Name            addmstyle.c  --  add menu style
*
*   Description     This function add a menu style to be used later by
*                   menunew
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT addmstyle(name,mnustyle,width,norm,bar,unav,bord,permlvl)
TEXT *name;         /* Name of menu                                 */
COUNT mnustyle;     /* Style options                                */
COUNT width;        /* Width of menu window                         */
COUNT norm;         /* Attribute for normal items                   */
COUNT bar;          /* Attribute for bar                            */
COUNT unav;         /* Attribute for unavailable                    */
COUNT bord;         /* Attribute for border                         */
COUNT permlvl;      /* Permission level for menu                    */
   {
   MENUSTYLE *ptr,*insptr,*getmstyle();
   TEXT *vcalloc();
   COUNT strcmp();
   VOID vcfree();
   COUNT chgmstyle();
   insptr = &vcmstyle;
   ptr = (MENUSTYLE *)0;
   if( insptr->smagic != MSTYLEMAGIC )
       {
       vcerror = BADMSTYLE;
       return(-1);
       }
   while( insptr && strcmp(insptr->stylename,name)!=0 )
       {
       if( insptr->smagic != MSTYLEMAGIC )
           {
           vcerror = BADMSTYLE;
           return(-1);
           }
       ptr=insptr;
       insptr = insptr->snext;
       }
   if( insptr != (MENUSTYLE *) 0 )
       {
       vcerror = SYMEXIST;            /* style name already exists */
       return(-1);
       }
   insptr=ptr;
   if( (ptr=(MENUSTYLE *)vcalloc(1,sizeof(MENUSTYLE),NULLTEXT)) ==
                            (MENUSTYLE *)0)
      {
      return(-1);
      }
   ptr->smagic=MSTYLEMAGIC;

   if(chgmstyle(ptr,name,mnustyle,width,norm,bar,unav,bord,permlvl))
      {
      vcfree(ptr,NULLTEXT);
      return(-1);     
      }
   insptr->snext=ptr;
   return(0);
   }


