/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:50
*
*   Name            vcsdigit.c - is number or space
*                                   
*   Description     Tells if character is numeric or space
*
*   Return Value    Returns TRUE if a number or space
*                                   
**/

#include <vcstdio.h>

COUNT vcsdigit(c)
COUNT c;
    {
    COUNT retval;
    if((retval = isdigit(c)) < 0)
        retval = 0;
    if(!retval)
        retval = (c == ' ' ? 1 : 0);
    return(retval);
    }



