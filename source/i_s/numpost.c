/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:29
*
*   Name            numpost.c  --  Double post function
*
*   Description     Double post function converts the string
*                   back to its native data type.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT numpost(gi)
GETITEM *gi;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "numpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    sscanf(gi->gtmpfld,"%lf",(double *)gi->g_field);
    return(0);
    }


