/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:36
*
*   Name            allcaps.c  --  Convert a String to all Caps
*
*   Description     This function convert the string passed it to
*                   all upper case
*
*   Return Value    VOID
*
**/

#ifdef toupper
#undef toupper
#endif

#include <vcstdio.h>

COUNT allcaps(str)
PFAST TEXT *str;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "allcaps:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(str != NULLTEXT)
        while((*str) != '\0')
            {
            *str = toupper(*str);
            str++;
            }
    return(0);
    }

