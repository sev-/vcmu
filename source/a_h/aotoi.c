/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:39
*
*   Name            aotoi.c  --  ascii oct to integer
*
*   Description     This function converts three byte ascii oct
*                   to integer.
*
*   Return Value    Returns integer value of string
*
**/

#include <vcstdio.h>

COUNT aotoi(str)
TEXT *str;          /* Pointer to string to convert                 */
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "aotoi:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return( ((*str-'0')*64) + ((*(str+1)-'0')*8) + (*(str+2)-'0') );
    }


