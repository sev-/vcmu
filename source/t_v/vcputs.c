/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:45
*
*   Name            vcputs.c  --  put a string to display
*
*   Description     This puts a string with attribute to the screen
*                   by calling vcputc(). 
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcputs(str,attr) 
PFAST TEXT *str;    /* Pointer to string to display                 */
PFAST COUNT attr;   /* Attribute to use                             */
    {
#ifdef TERMINAL
    COUNT flow=0;
#endif
    COUNT wputchr();
    VOID vcputc();
    VOID vcflush();
    COUNT vcpee();
    VOID wplace_cur();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcputs:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
#endif
    if(wdoctrl->wno_opn && !override)
        {
        cur_switch = FALSE;
        while(*str)
            wputchr(wdoctrl->wcurrent,*(str++),attr);
        cur_switch = TRUE;
        wplace_cur(wdoctrl->wcurrent);
        }
    else
        {
        while(*str)
            vcputc(*(str++),attr);
        }
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif

#else

#ifdef TERMONLY
    flow=vcpee();
    if(attr != termattr)
        flipattr(attr);
    dist_str(str,-1);
    if(vcterm.ms != 1)
        flipattr(NORM_ATTR);
    if(flow)
        vcflush();
#endif
#ifdef IBM
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
        if(attr != termattr)
            flipattr(attr);
        dist_str(str,-1);
        if(vcterm.ms != 1)
            flipattr(NORM_ATTR);
        }
    else
#endif
        while(*str)
            vcputc(*(str++),attr);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
#endif
#ifdef OS2
#ifdef TERMINAL
    if(vctio == 5)
        flow=vcpee();
        if(attr != termattr)
            flipattr(attr);
        dist_str(str,-1);
        if(vcterm.ms != 1)
            flipattr(NORM_ATTR);
        }
    else
#endif
        while(*str)
            vcputc(*(str++),attr);
#ifdef TERMINAL
    if(flow)
        vcflush();
#endif
#endif

#endif
    }
