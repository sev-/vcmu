/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:29
*
*   Name            statwdo.c  --  load file to window
*
*   Description     Returns the current status window
*
*   Return Value    Returns current status window pointer 
*                    
*
**/

#include <vcstdio.h>

WPTR statwdo()
    {
    return(msgwdo);
    }


