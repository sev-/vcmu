/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:58
*
*   Name            itoap.c  --  Integer to ascii with precision
*
*   Description     This function takes an integer value and convert
*                   to an ascii value of the correct length.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

COUNT itoap(number,str,precision)
COUNT number;       /* Number to convert                            */
COUNT precision;    /* Precision of string value                    */
TEXT *str;          /* Pointer to string to place value             */
    {
    COUNT tmp,flag=0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "itoap:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    tmp=number/100;
    if(tmp || (precision > 2))
        {
        *(str++) = '0'+tmp;
        number %= 100;
        flag=1;
        }
    tmp=number/10;
    if(flag || (tmp) || (precision > 1))
        {
        *(str++) = '0'+tmp;
        number %= 10;
        }
    *(str++) = '0'+number;
    *str = '\0';
    return(0);
    }


