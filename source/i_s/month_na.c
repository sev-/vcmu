/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:26
*
*   Name            month_na.c  --  Returns pointer to month name
*
*   Description     Return a pointer to a NULL terminated string
*                   containing the name of the month {n}. If error
*                   points the the message Invalid.
*
*   Return Value    Returns Pointer to month name
*
**/

#include <vcstdio.h>

TEXT *month_name(n) 
PFAST COUNT n;      /* Number of month                              */
    {
    static TEXT *name[] = 
        {
        (TEXT *)"Invalid",
        (TEXT *)"January",
        (TEXT *)"February",
        (TEXT *)"March",
        (TEXT *)"April",
        (TEXT *)"May",
        (TEXT *)"June",
        (TEXT *)"July",
        (TEXT *)"August",
        (TEXT *)"September",
        (TEXT *)"October",
        (TEXT *)"November",
        (TEXT *)"December"
        };
#ifdef VCDEBUG
    vcdebug = (TEXT *) "month_name:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return((n<1 || n>12) ? name[0] : name[n]);
    }


