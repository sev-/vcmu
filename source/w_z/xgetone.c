/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:23
*
*   Name            xgetone.c  --  low level input routine
*
*   Description     This is the low level input routine. This function
*                   waits until a key is pressed and returns the key.
*
*   Return Value    Returns the key pressed or the next key in the
*                   buffer.
*
**/

#include <vcstdio.h>

COUNT xgetone()
    {
    COUNT retval;
    COUNT bufkdy();
    COUNT gbufkey();
    INDEF;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xgetone:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(bufkdy())
        retval = gbufkey();
    else
        retval = (COUNT)INFUNC();
    return(retval);
    }


