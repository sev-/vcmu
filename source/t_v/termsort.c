/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:25
*
*   Name            termsort.c  --  termcap entries sort
*
*   Description     This function sorts the termcap entries so
*                   that next calls to termcap programs have 
*                   better response.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

VOID termsort()
    {
    TEXT *ptr1,*ptr2;
    TEXT tempbuf[3],*strchr();
    COUNT offset;
    COUNT addtable();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "termsort:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ptr1 = chbuf;
    while((ptr2 = strchr(ptr1,':'))  != NULLTEXT)
        {
        if((ptr2 != chbuf) && (*(ptr2-1) == '\\'))
            {
            ptr1 = ptr2+1;
            continue;
            }
        ptr2++;
        offset = ptr2-chbuf;
        if(*ptr2 != '\0')
            {
            tempbuf[0] = *(ptr2++);
            tempbuf[1] = *ptr2;
            tempbuf[2]='\0';
            addtable(&sorted,tempbuf,offset);
            }
        ptr1 = ptr2;
        }
    }

#endif


