/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:54
*
*   Name            unblkkey.c -- Unblock key 
* 
*   Description     This function removes a value from the blocked
*                   key array.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID unblkkey(key)
COUNT key;
    {
    COUNT cnt = 0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "unblkkey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while((cnt < keysblocked) && (key != blocked[cnt]))
        cnt++;
    while(cnt < 19)
        {
        blocked[cnt] = blocked[cnt+1];
        cnt++;
        }
    }


