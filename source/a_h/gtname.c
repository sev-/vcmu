/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:32
*                
*   Name            gtname.c  --  Get terminal name
*
*   Description     This function reads the termcap file to get the
*                   terminal name and return a pointer to the name.
*                   Also sets the pointer to COUNT to the length of
*                   the terminal name;
*
*   Return Value    Returns NULL or a pointer to the terminal name
*
**/

#include <vcstdio.h>

TEXT *gtname(tbuf,len)
TEXT *tbuf;         /* Pointer to termcap buffer                    */
COUNT *len;         /* Pointer to COUNT to set length of name       */
    {
    TEXT *strchr();
    TEXT *end,*begin;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gtname:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((end = strchr(tbuf,':')) != NULLTEXT)
        {
        begin = end;
        while((*begin != '|') && (begin >= tbuf))
            begin--;
        begin++;
        *len = end - begin;
        return(begin);
        }
    else
        {
        *len = 0;
        return(NULLTEXT);
        }
    }


