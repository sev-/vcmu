/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:06
*
*   Name            vcalnum.c - is alpha / number
*                                   
*   Description     Tells if character is alpha or number
*
*   Return Value    Returns TRUE if alpha or number
*                                   
**/

#include <vcstdio.h>

COUNT vcalnum(c)
COUNT c;
    {
    COUNT retval;
    if((retval = isalnum(c)) < 0)
        retval = 0;
    return(retval);
    }



