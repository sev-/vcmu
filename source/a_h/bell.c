/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:55
*
*   Name            bell.c  --  Ring bell
*
*   Description     If bellstat is true it rings bell otherwise does
*                   nothing.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID bell()
    {
    VOID vcint();
    OUTDEF;
#ifdef IBM
    struct VCREGS ir,or;
#ifdef TERMINAL
    TEXT rbell[1];
#endif
    if(bellstat)
        {
#ifdef TERMINAL
        if(vctio != 5)
            {
#endif
            ir.ax = 0x200;
            ir.dx = (BELL);
            vcint(0x21,&ir,&or);
#ifdef TERMINAL
            }
        else
            {
            rbell[0] = (TEXT) BELL;
            OUTFUNC(rbell,1);
            }
#endif
        }
#endif
#ifdef UNIX
    TEXT rbell[1];
    rbell[0] = (TEXT) BELL;
    if(bellstat)
        OUTFUNC(rbell,1);
#endif
#ifdef VMS
    TEXT rbell[1];
    rbell[0] = (TEXT) BELL;
    if(bellstat)
        OUTFUNC(rbell,1);
#endif     
#ifdef PRIMOS
    TEXT rbell[1];
    rbell[0] = (TEXT) BELL;
    if(bellstat)
        OUTFUNC(rbell,1);
#endif     
#ifdef OS2
#ifdef TERMINAL
    TEXT rbell[1];
#endif
    if(bellstat)
        {
#ifdef TERMINAL
        if(vctio != 5)
            {
#endif
            DosBeep(800,75);
#ifdef TERMINAL
            }
        else
            {
            rbell[0] = (TEXT) BELL;
            OUTFUNC(rbell,1);
            }
#endif
        }
#endif
    }

