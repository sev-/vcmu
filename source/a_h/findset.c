/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:03
*
*   Name            findset.c  --  find termcap entry
*
*   Description     This function finds the termcap entry in the
*                   sorted list.
*
*   Return Value    Returns pointer to entry, NULL if not found.
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

TEXT *findset(str2)
TEXT *str2;         /* Entry to find in table                       */
    {
    COUNT offset=0,trash;
    struct KEYTBLNODE *ptr1,*ptr2,*intable();     
    TEXT ch;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "findset:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ch = *(str2++);
    ptr1 = sorted;
    if((ptr2=intable(ptr1,ch,&trash)) == (struct KEYTBLNODE *) 0)
        return(NULLTEXT);
    ch = *str2;
    intable(ptr2,ch,&offset);
    if(offset)
        return(chbuf+offset);
    else
        return(NULLTEXT);
    }

#endif


