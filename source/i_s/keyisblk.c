/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:59
*
*   Name            keyisblk.c -- Key is blocked
* 
*   Description     Checks to see if a certain key is currently 
*                   blocked from input.
*
*   Return Value    Returns True if currently blocked or False
*                   if not blocked
*
**/

#include <vcstdio.h>

COUNT keyisblk(key)
COUNT key;
    {
    COUNT cnt=0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "keyisblk:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while(cnt<keysblocked)
        if(blocked[cnt] == key)
            return(TRUE);
        else
            cnt++;
    return(FALSE);
    }


