/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:13
*
*   Name            sintpost.c  --  Short integer post function
*
*   Description     Short integer post function converts the string
*                   back to its native data type.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

#ifdef PRIMOS
#define SCANVALUE "%d"
#else
#define SCANVALUE "%hd"
#endif

COUNT sintpost(gi)
GETITEM *gi;
    {
#ifdef PRIMOS
    COUNT tmp;
    SHORT *realval;
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "sintpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef PRIMOS
    realval = (SHORT *)gi->g_field;
    sscanf(gi->gtmpfld,SCANVALUE,&tmp);
    *realval = (SHORT) tmp;
#else
    sscanf(gi->gtmpfld,SCANVALUE,(SHORT *)gi->g_field);
#endif
    return(0);
    }




