/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:18
*
*   Name            vcdelay.c  --  Delay function
*
*   Description     Delays 
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcdelay(no)
COUNT no;           /* Number to delay                              */
    {
    COUNT cnt;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcdelay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(no > 1)
        for(cnt=1;cnt<no;cnt++);
    }


