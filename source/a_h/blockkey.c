/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:01
*
*   Name            blockkey.c 
* 
*   Description     This function adds a value to the blocked key
*                   array.
*
*   Return Value    Returns -1 if the array is full
*
**/

#include <vcstdio.h>

COUNT blockkey(key)
COUNT key;          /* Value of key to block                        */
    {
    COUNT cnt = 0;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "blockkey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(keysblocked > 19)
        return(-1);
    while((cnt<keysblocked) && (key != blocked[cnt]))
        cnt++;
    if(key != blocked[cnt])
        {
        blocked[cnt] = key;
        keysblocked++;
        }
    return(0);
    }


