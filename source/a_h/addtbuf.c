/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:27
*
*   Name            addtbuf.c  --  Add to terminal buffer
*
*   Description     This program adds to the terminal buffer
*                   if the buffer is full it flushes the buffer
*                   then adds to the new buffer.
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID addtbuf(buf,len)
TEXT *buf;          /* Pointer to text to send to terminal          */
PFAST COUNT len;    /* If length not 0 then is a character          */
    {
    VOID vcflush();
    VOID vcmem();
    COUNT vcpee();
    OUTDEF;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "addtbuf:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(len == 1)
        {
        *(tbufptr++) = *buf;
        if(tbufptr > tbufend)
            {
            vcflush();
            vcpee();
            }
        }
    else
        {
        if(buf != NULLTEXT)
            {
            if((tbufptr+len) > tbufend)
                {
                vcflush();
                vcpee();
                }
            if(len > SCRNBUFSIZ)
                OUTFUNC(buf,len);
            else
                {
                vcmem(tbufptr,buf,len);
                tbufptr += len;
                }
            }
        }
    }
#endif


