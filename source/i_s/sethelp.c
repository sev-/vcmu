/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:04
*
*   Name            sethelp.c  --  Set help function
*
*   Description     Set the global pointer to a help function to a new
*                   function and returns a pointer to the old help
*                   function
*
*   Return Value    Returns pointer to old help function
*
**/

#include <vcstdio.h>

PFI sethelp(func)
PFI func;           /* Pointer to new help function                 */
    {
    PFI oldfunc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "sethelp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldfunc = helpfunc;
    helpfunc = func;
    return(oldfunc);
    }


