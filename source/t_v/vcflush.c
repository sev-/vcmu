/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:46
*
*   Name            vcflush.c  --  Flush buffer
*
*   Description     Flushes the buffer to the terminal and checks to
*                   see if the cursor should be on or off.
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

extern TEXT vcpadbuf[];
extern COUNT vcpadcnt;

VOID vcflush()
    {
    FAST COUNT length;
    VOID sendpstr();
    OUTDEF;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcflush:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(!bufon)
        return;
    length = tbufptr - termbuf;
    if(length < 1)
        {
        bufon = 0;
        return;
        }
    if(vccursor <= 2)
        if(vcterm.cf != NULLTEXT)
            sendpstr(vcterm.cf);
    OUTFUNC(termbuf,length);
    bufon=0;
    if(vccursor <= 2)
        { 
        if(vcterm.co != NULLTEXT)
            sendpstr(vcterm.co);
        if(vccursor == 1)
            {
            if(vcterm.ve != NULLTEXT)
                sendpstr(vcterm.ve);
            }
        else
            {
            if(vcterm.vs != NULLTEXT)
                sendpstr(vcterm.vs);
            }
        }
    }


VOID sendpstr(str)
TEXT *str;
    {
    COUNT vcpadstr();
    VOID vcmem();
    TEXT tmppadbuf[128];
    OUTDEF;
    vcmem(tmppadbuf,vcpadbuf,127);
    (*padfunc)(str,1,vcpadstr);
    OUTFUNC(&vcpadbuf[0],vcpadcnt);
    vcmem(vcpadbuf,tmppadbuf,vcpadcnt);
    vcpadcnt = 0;
    }

#endif


