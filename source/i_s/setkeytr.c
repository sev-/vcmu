/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:07
*
*   Name            setkeytrap.c  --  Sets the keyboard trap function
*
*   Description     This function sets the keyboard trap function
*
*   Return Value    Returns the present keyboard trap function
*                    
*
**/

#include <vcstdio.h>

PFI setkeytrap(keyfunc)
PFI keyfunc;
   {
   PFI prevfunc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "setkeytrap:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
   prevfunc=keytrap;
   keytrap=keyfunc;
   return(prevfunc);
   }


