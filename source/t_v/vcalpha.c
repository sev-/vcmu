/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:08
*
*   Name            vcalpha.c - is alpha 
*                                   
*   Description     Tells if character is alpha 
*
*   Return Value    Returns TRUE if alpha 
*                                   
**/

#include <vcstdio.h>

COUNT vcalpha(c)
COUNT c;
    {
    COUNT retval;
    if((retval = isalpha(c)) < 0)
        retval = 0;
    return(retval);
    }



