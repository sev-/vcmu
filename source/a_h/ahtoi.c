/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:34
*
*   Name            ahtoi.c  --  ascii hex to integer
*
*   Description     This function converts two byte ascii hex
*                   to integer.
*
*   Return Value    Returns integer value of string
*
**/

#include <vcstdio.h>

COUNT ahtoi(str)
TEXT *str;          /* Pointer to string to convert                 */
    {
    COUNT fdig,sdig;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "ahtoi:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    *str = (TEXT) toupper(*str);
    *(str+1) = (TEXT) toupper(*(str+1));
    if( (*str >= 'A') && (*str <= 'F') )
        fdig = *str - 'A' + 10;
    else
        fdig = *str - '0';
    str++;
    if( (*str >= 'A') && (*str <= 'F') )
        sdig = *str - 'A' + 10;
    else
        sdig = *str - '0';
    return((fdig*16)+sdig);
    }


