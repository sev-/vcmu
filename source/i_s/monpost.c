/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:23
*
*   Name            monpost.c  --  Money post function
*
*   Description     Money post function converts the string
*                   back to its native data type.
*
*   Return Value    Returns -1 if error
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT monpost(gi)
GETITEM *gi;
    {
    COUNT cnt;
    TEXT *ptr1,*ptr2;
    TEXT buf[32];
    LONG *lp;
    LONG atol();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "monpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ptr1 = buf;
    ptr2 = gi->gtmpfld;
    while(*ptr2 != '\0')
        {
        if(*ptr2 != '.')
            *(ptr1++) = *ptr2;
        ptr2++;
        }
    *ptr1 = '\0';
    lp = (LONG *)gi->g_field;
    *lp = atol(buf);
    return(0);
    }


