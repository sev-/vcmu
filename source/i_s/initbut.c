/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:32
*
*   Name            initbut - Initialize button entry
*                                   
*   Description     Start button field
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID initbut(gi)
GETITEM *gi;
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "initbut:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    gi->g_length = strlen(gi->gtmppic) - 1;
    }





