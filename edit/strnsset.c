/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 8/31/90 at 21:50:07
*
*   Name            strnsset.c  --  String subset
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

TEXT *strnsset(str1,str2,len)
TEXT *str1,*str2;
COUNT len;
    {
    TEXT *retval = NULLTEXT;
    TEXT *strnchr();
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
    while((len > 0) && ((ptr2 = strnchr(ptr1,ch,len)) != NULLTEXT))
        {
        if(strncmp(ptr2,str2,strlen(str2)) == 0)
            {
            retval = ptr2;
            break;
            }
        else
            {
            len -= (COUNT)(ptr2 - ptr1);
            ptr1 = ptr2+1;
            }
        }
    return(retval);
    }

TEXT *strnchr(str,ch,len)
TEXT *str;
TEXT ch;
COUNT len;
    {
    TEXT *retval = NULLTEXT;
    if(len)
        while(len)
            {
            if(*(str++) == ch)
                break;
            len--;
            }
    if(len)
        retval = --str;
    return(retval);
    }
#endif


