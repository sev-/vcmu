/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:40
*
*   Name            strsset.c  --  String subset
*
*   Description     String subset function finds the second string 
*                   in the first string.
*
*   Return Value    Returns pointer where the second string is 
*                   located in the first string.
*
**/

#include <vcstdio.h>

#ifdef TERMCAP

TEXT *strsset(str1,str2)
TEXT *str1,*str2;
    {
    TEXT *strchr();
    TEXT *ptr1,*ptr2,ch;
    COUNT strncmp();
    COUNT strlen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "strsset:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ch = *str2;
    ptr1 = str1;
    while(( ptr2 = strchr(ptr1,ch)) != NULLTEXT)
        if( strncmp(ptr2,str2,strlen(str2)) == 0)
            return(ptr2);
        else
            ptr1 = ptr2+1;
    return(NULLTEXT);
    }

#endif


