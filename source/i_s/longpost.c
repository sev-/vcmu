/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:13
*
*   Name            longpost.c  --  Long post function
*
*   Description     Long post function converts the string
*                   back to its native data type.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT longpost(gi)
GETITEM *gi;
    {
    LONG *lp;
    LONG atol();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "longpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    lp = (LONG *)gi->g_field;
    *lp = atol(gi->gtmpfld);
    return(0);
    }


