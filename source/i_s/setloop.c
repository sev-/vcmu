/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:08
*
*   Name            setloop.c  --  Set loop function
*
*   Description     Set the global pointer to a loop function to a new
*                   function and returns a pointer to the old loop
*                   function
*
*   Return Value    Returns pointer to old loop function
*
**/

#include <vcstdio.h>

PFI setloop(func)
PFI func;           /* Pointer to new loop function                 */
    {
    PFI oldfunc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "setloop:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldfunc = waitfunc;
    waitfunc = func;
    return(oldfunc);
    }


