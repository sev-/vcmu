/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:02
*
*   Name            wclr.c  --  Clear the virtual window
*
*   Description     Clears the virtual window to an attribute and character.
*                   If -1 is given as the attribute will clear with default.
*                   Gets the character to use from winfo[number].fill_ch. This
*                   function need not be called directly but by werase() or
*                   erase().
*
*   Return Value    VOID 
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID wclr(wptr,attr)
WPTR wptr;          /* Pointer to window to clear                   */
COUNT attr;         /* Attribute to use -1 for default              */
    {
    FAST TEXT *pointer;
    TEXT *source;
    FAST COUNT cnt;
    COUNT width;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wclr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(attr == -1)
        attr=wptr->bg_at;
    pointer=wptr->location;
    source=pointer;
    for(cnt=1;cnt<=wptr->width;cnt++)
        {
        *(pointer++)=wptr->fill_ch;
        *(pointer++)=attr;
        }
    width = wptr->width << 1;
    for(cnt=1;cnt < wptr->depth;cnt++)
        {
        vcmem(pointer,source,(UCOUNT)width);
        pointer += width;
        }
    }

#endif

