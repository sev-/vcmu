/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:45
*
*   Name            empty.c  --  empty a string
*
*   Description     Empties a string to length {len} including
*                   the NULL terminator.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID empty(str,len)
TEXT str[];         /* String to empty                              */
PFAST COUNT len;    /* Size of string including NULL                */
    {
    FAST COUNT n;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "empty:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    for(n=0;n<len;n++)
        str[n]=' ';
    str[len-1]=0;
    }

