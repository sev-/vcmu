/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:39
*
*   Name            dist_str.c  --  Send string to terminal
*
*   Description     Distribute a string to the terminal or
*                   the terminal buffer.
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

extern TEXT vcpadbuf[];
extern COUNT vcpadcnt;

VOID dist_str(buf,len)
PFAST TEXT *buf;    /* Pointer to text to send to terminal          */
PFAST COUNT len;    /* If length not 0 then is a character          */
    {
    COUNT vcpadstr();
    COUNT size = 0;
    TEXT *outstr;
    COUNT strlen();
    VOID addtbuf();
    OUTDEF;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "dist_str:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(buf == NULLTEXT)
        return;
    switch(len)
        {
        case 1:
            size = 1;
            outstr = buf;
            break;
        case -1:
            if(buf != NULLTEXT)
                size = strlen(buf);
            outstr = buf;
            break;
        case 0:
            (*padfunc)(buf,1,vcpadstr);
            outstr = &vcpadbuf[0];
            size = vcpadcnt;
            vcpadcnt = 0;
            break;
        }
    if(bufon)
        addtbuf(outstr,size);
    else
        OUTFUNC(outstr,size);
    }

#endif


