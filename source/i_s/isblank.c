/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:55
*
*   Name            isblank.c  --  is a string blank
*
*   Description     checks to see if the NULL terminated string
*                   is blank
*
*   Return Value    Returns 1 if blank, 0 if not
*
**/

#include <vcstdio.h>

COUNT isblank(str)
PFAST TEXT *str;    /* Pointer to string to check                   */
    {
    while(*str)
        {
        if(*str != ' ')
            return(0); /*  NOT ALL BLANK  */
        str++;
        }
    return(1);
    }

