/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:27
*
*   Name            nocolor.c  --  Set nocolor on windows
*
*   Description     This function copies the mono table to the default
*                   window colors
*
*   Return Value    VOID
*
**/

#include <vcstdio.h> 

VOID nocolor()
    {
#ifdef WINDOW
    FAST COUNT x;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "nocolor:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    for(x=0;x<10;x++)
        {
        wtable[x].bd_t=wmono[x].bd_t;
        wtable[x].bg_t=wmono[x].bg_t;
        wtable[x].say_t=wmono[x].say_t;
        wtable[x].nget_t=wmono[x].nget_t;
        wtable[x].get_t=wmono[x].get_t;
        wtable[x].tit_t=wmono[x].tit_t;
        }
#endif
    }


