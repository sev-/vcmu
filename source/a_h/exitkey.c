/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:58
*
*   Name            exitkey.c  --  Set exit key
*
*   Description     Set the global exit key to the key that is
*                   passed and returns the old exit key.
*
*   Return Value    Returns old exit key
*
**/

#include <vcstdio.h>

COUNT exitkey(ascii)
PFAST COUNT ascii;  /* New exit key                                 */
    {
    FAST COUNT oldkey;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "exitkey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldkey = spkey.xhkey;
    spkey.xhkey = ascii;
    return(oldkey);
    }


