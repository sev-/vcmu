/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:31
*
*   Name            adtoi.c  --  ascii decimal to integer
*
*   Description     This function converts three byte ascii 
*                   decimal to integer.
*
*   Return Value    Returns integer value of string
*
**/

#include <vcstdio.h>

COUNT adtoi(str)
TEXT *str;          /* Pointer to string to convert                 */
    {
    COUNT mag,retval=0;
    COUNT strlen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "adtoi:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    mag = strlen(str);
    if(mag > 2)
        {
        if((*str >= '0') && (*str <= '9'))
            retval = (*(str++) - '0') * 100;
        else
            str++;
        }
    if(mag > 1)
        {
        if((*str >= '0') && (*str <= '9'))
            retval += (*(str++) - '0') * 10;
        else
            str++;
        }
    if((*str >= '0') && (*str <= '9'))
        retval += (*(str++) - '0');
    return(retval);
    }



