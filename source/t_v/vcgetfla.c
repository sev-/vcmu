/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:54
*
*   Name            vcgetflag.c  --  get boolean value
*
*   Description     This function retrieves the termcap information
*                   for the boolean expression.
*
*   Return Value    Returns True if found -1 if bad id and 0 if not
*                   found.
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

COUNT vcgetflag(id)
TEXT *id;           /* Pointer to string of boolean value           */
    {
    TEXT *ptr,*findset();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcgetflag:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(id == NULLTEXT)
        return(-1);
    if( (ptr = findset(id)) == NULLTEXT)
        return(0);
    ptr += 2;
    if ( *(ptr++) == '@')
        return(0);
    return(1);
    }

#endif
 
