/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:12
*
*   Name            lstmstyle.c  --  list menu style
*
*   Description     This function list menu style that have been
*                   initialized
*
*   Return Value    VOID
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VOID lstmstyle()
   {
   MENUSTYLE *ptr;
   VOID atsay();
   ptr = &vcmstyle;
   while( ptr )
      {
      atsay(vcrow,0,ptr->stylename);
      vcrow++;
      ptr=ptr->snext;
      }
   }


