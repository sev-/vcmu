/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:27
*
*   Name            terror.c  --  Terminal error routine
*
*   Description     This function prints a string on the screen then
*                   exits the program. Useful when unexplained or
*                   untraped error has occured
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID terror(msg)
PFAST TEXT *msg;    /* Pointer to message or NULL                   */
    {
    COUNT bye = TRUE;
    VOID sendpstr();
    VOID exit();
    VOID set_normal();
    COUNT strlen();
    OUTDEF;
#ifdef TERMONLY
    VOID set_normal();
#endif
#ifdef VCDEBUG
    if(vcdbfunc != NULLFUNC)
        {
        vcdebug = msg;
        bye = (*vcdbfunc)(CONTINUE);
        }
#endif
    if(bye)
        {
        OUTFUNC(msg,strlen(msg));
        OUTFUNC("\n\r",2);
#ifdef TERMONLY
        if(vcterm.es != NULLTEXT)
            sendpstr(vcterm.es);
        set_normal();
#endif
        exit(0);
        }
    }

