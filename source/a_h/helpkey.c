/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:38
*
*   Name            helpkey.c  --  Set help key
*
*   Description     Set the global help key to the key that is
*                   passed and returns the old help key.
*
*   Return Value    Returns old help key
*
**/

#include <vcstdio.h>

COUNT helpkey(ascii)
PFAST COUNT ascii;  /* New help key                                 */
    {
    FAST COUNT oldkey;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "helpkey:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    oldkey = spkey.hkey;
    spkey.hkey = ascii;
    return(oldkey);
    }


