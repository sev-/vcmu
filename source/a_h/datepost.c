/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:21
*
*   Name            datepost.c  --  Standard date post-function
*
*   Description     This is the standard date post function.
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT datepost(gi)
GETITEM *gi;        /* Get item to act upon                         */
    {
    LONG tojul();
    LONG *tmp;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "strpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    tmp = (LONG *) gi->g_field;
    *tmp = tojul(gi->gtmpfld);
    return(0);
    }
