/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:24
*
*   Name            day_name.c  --  Returns pointer to Day name
*
*   Description     Return a pointer to a NULL terminated string
*                   containing the name of the day {n}. If error
*                   points the the message Invalid.
*
*   Return Value    Returns pointer to day name
*
**/

#include <vcstdio.h>

static TEXT *name[] =
    {
    (TEXT *)"Sunday",
    (TEXT *)"Monday",
    (TEXT *)"Tuesday",
    (TEXT *)"Wednesday",
    (TEXT *)"Thursday",
    (TEXT *)"Friday",
    (TEXT *)"Saturday",
    (TEXT *)"Invalid"
    };

TEXT *day_name(n)
PFAST COUNT n;      /* Number of day                                */
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "day_name:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return((n<0 || n>6) ? name[7] : name[n]);
    }

