/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:57
*
*   Name            blank.c  --  Blank a string 
*
*   Description     This function blanks a NULL terminated string
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID blank(str)
PFAST TEXT *str;    /* Pointer to string to blank                   */
    {
    while(*str)
        *(str++)=' ';
    }

