/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:56
*
*   Name            vcgetnum.c  --  get numeric value
*
*   Description     This function retrieves the termcap information
*                   for a numeric value.
*
*   Return Value    Returns the numeric value.
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

COUNT vcgetnum(id)
TEXT *id;           /* Pointer to name of numeric value             */
    {
    TEXT retval[5],*ptr,*sptr,*findset();
    COUNT adtoi();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcgetnum:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(id == NULLTEXT)
        return(-1);
    if( (ptr = findset(id)) == NULLTEXT)
        return(-1);
    ptr += 2;
    if ( *(ptr++) == '@')
        return(0);
    sptr = retval;
    while( *ptr != ':')
        *(sptr++) = *(ptr++);
    *sptr = '\0';
    return(adtoi(retval));
    }

#endif


