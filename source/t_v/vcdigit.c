/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:21
*
*   Name            vcdigit.c - is number 
*                                   
*   Description     Tells if character is numeric
*
*   Return Value    Returns TRUE if a number
*                                   
**/

#include <vcstdio.h>

COUNT vcdigit(c)
COUNT c;
    {
    COUNT retval;
    if((retval = isdigit(c)) < 0)
        retval = 0;
    return(retval);
    }



