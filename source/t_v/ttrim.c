/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:52
*
*   Name            ttrim -- temporary trim variable           
*                                   
*   Description     Temporary trims a variable.  Because this
*                   function uses a static buffer it should not
*                   be called more than once on any line.  Max
*                   length 80           
*
*   Return Value    Returns pointer to trim string
*                                   
**/                                 

#include <vcstdio.h>

static TEXT rbuf[180];

TEXT *ttrim(str)
TEXT *str;          /* Pointer to string to temporary trim          */
    {
    TEXT *strncpy();
    TEXT *trim();
    if(str == NULLTEXT)
        return(NULLTEXT);
    strncpy(rbuf,str,179);
    return(trim(rbuf));
    }
