/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:21
*
*   Name            weraeos.c  --  Erase to end of screen
*
*   Description     This function erases the selected window (number)
*                   from the current col (winfo[number].c_pos) to the
*                   end of the line then erases from current row+1
*                   (winfo[number].r_pos+1) to the end of screen.
*                   This function is can be called for the current window
*                   (wcurrent) using the functions eraeos() and xeraeos().
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef WINDOW

VOID weraeos(wptr,attr)
WPTR wptr;          /* Pointer to window to erase                   */
COUNT attr;         /* Attribute to use                             */
    {
    FAST TEXT *pointer;
    FAST COUNT cnt;
    COUNT width;
    TEXT *sptr;
    COUNT offset;
    VOID vcmem();
    VOID weraeol();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "weraeos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(attr < 0)
        attr=wptr->bg_at;
    if(wptr->r_pos < wptr->depth-1)
        {
        offset = ((wptr->r_pos+1)*wptr->width) << 1;
        pointer=wptr->location+offset;
        sptr = pointer;
        width = wptr->width << 1;
        for(cnt=1;cnt <= wptr->width;cnt++)
            {
            *(pointer++)=wptr->fill_ch;
            *(pointer++)=attr;
            }
        for(cnt=wptr->r_pos+2;cnt < wptr->depth;cnt++)
            {
            vcmem(pointer,sptr,width);
            pointer += width;
            }
        }
    weraeol(wptr,attr);
    }

#endif


