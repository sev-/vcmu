/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:55
*
*   Name            ungetone.c  --  Put back a single character
*
*   Description     This ungetone() pushes a character back so the
*                   next call to getone() returns this character.
*
*   Return Value    Returns a -1 if the buffer is full.
*
**/

#include <vcstdio.h>

COUNT ungetone(ans)
PFAST COUNT ans;    /* Character to put into buffer                 */
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "ungetone:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    kbbuftl++;
    if(kbbuftl > kbbufed)
        kbbuftl = &kbbuffer[0];
    if(kbbuftl == kbbufhd)
        {
        kbbufhd++;
        if(kbbufhd > kbbufed)
            kbbufhd = &kbbuffer[0];
        }
    return(*kbbuftl = ans);
    }


