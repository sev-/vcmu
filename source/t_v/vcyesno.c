/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:20
*
*   Name            vcyesno.c - is y or n
*                                   
*   Description     Tells if character is 'y', 'Y','n' or 'N'
*
*   Return Value    Returns TRUE if 'y' or 'n'
*                                   
**/

#include <vcstdio.h>

COUNT vcyesno(key)
COUNT key;
    {
    COUNT retval = FALSE;
    if((key == 'Y') || (key == 'y') ||
       (key == 'N') || (key == 'n')   )
        retval = TRUE;
    return(retval);
    }




