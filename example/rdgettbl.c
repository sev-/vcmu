/**
*
*   Vitamin C Multi-User version 1.%R%
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .%L% on %G% at %U%
*
*   Name            rdgettbl
*                                   
*   Description     Example of how to read gettables.
*
*   Return Value    N/A
*                                   
**/                                 

#define VCGET_DEFS
#include <vcstdio.h>

main()
   {
   TEXT name[32],address[32],phone[14];
   COUNT chk_tel();
   vcstart(CLRSCRN);
   empty(name,32);
   empty(address,32);
   empty(phone,14);
   atsayget(5,0,"Name........: ",name,NULL);
   atsayget(6,0,"Address.....: ",address,NULL);
   atsay(7,0,"Phone.......: ");
   xatget(7,14,phone,"(999)999-9999",chk_tel,NULL,NULL,-1,-1);
   readgets();
   vcend(NOCLOSE);
   }

COUNT chk_tel(curfld,tblptr)
TEXT *curfld;
GETTABLE *tblptr;
   {
   GETITEM *itmptr;
   COUNT lincntr=5;
   if( hasdata(tblptr->thead->gtmpfld,tblptr->thead->gtmppic) )
      {
      if( !hasdata(curfld,"(999)999-9999") )
         return(BAD);
      itmptr=tblptr->thead;
      while( itmptr != (GETITEM *)NULL )
         {
         atsay(lincntr++,45,itmptr->gtmpfld);
         itmptr = itmptr->gnext;
         }
      }
   return(GOOD);
   }

