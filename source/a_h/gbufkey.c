/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:08
*
*   Name            gbufkey.c  --  Get buffer key
*
*   Description     Gets the next key from the buffer and removes the
*                   key from the buffer.
*
*   Return Value    Returns a -1 if the buffer is empty or the next
*                   key if not empty.
*
**/

#include <vcstdio.h>

COUNT gbufkey()
    {
    FAST COUNT retval;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gbufkey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(kbbufhd != kbbuftl)
        {
        kbbufhd++;
        if(kbbufhd > kbbufed)
            kbbufhd = &kbbuffer[0];
        retval = *kbbufhd;
        }
    else
        retval = -1;
    return(retval);
    }


