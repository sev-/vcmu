/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:52
*
*   Name            intpost.c  --  Integer post function
*
*   Description     Integer post function converts the string
*                   back to its native data type.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT intpost(gi)
GETITEM *gi;
    {
    COUNT *ip;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "intpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ip = (COUNT *)gi->g_field;
    *ip = (COUNT)atoi(gi->gtmpfld);
    return(0);
    }


