/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:04
*
*   Name            bufkdy.c  --  buffer ready
*
*   Description     bufkdy() determines if a key is waiting in the
*                   buffer.
*
*   Return Value    Returns False if no key in buffer True if a key
*                   is in the buffer.
*
**/

#include <vcstdio.h>

COUNT bufkdy()
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "bufkdy:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(kbbufhd == kbbuftl)
        return(FALSE);
    else
        return(TRUE);
    }



