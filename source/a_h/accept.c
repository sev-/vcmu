/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 8/31/90 at 22:03:19
*
*   Name            accept.c  --  Accept an entry into a string
*
*   Description     This function accepts an input into str using
*                   pic. Input is done immediately and the function
*                   returns the key press that caused the function
*                   to exit.
*
*   Return Value    Returns the key pressed that caused the exit
*                    
*
**/

#define VCERROR_DEFS
#define VCGET_DEFS

#include <vcstdio.h>

COUNT accept(str,pic)
TEXT str[];         /* String to accept entry into                  */
TEXT pic[];         /* Picture used during input                    */
    {
    COUNT xaccept();
#ifdef VCDEBUG
    tcdebug = (TEXT *) "accept:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xaccept(str,pic,-1));
    }
