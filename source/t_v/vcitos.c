/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:10
*
*   Name            vcitos.c  --  Integer to string
*
*   Description     Converts integer to string
*
*   Return Value    Returns pointer to string
*
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd"
#else
#define SCANVALUE "%d"
#endif

TEXT *vcitos(str,num)
TEXT *str;
COUNT num;
    {
    TEXT buf[64];
    TEXT *vcnumfix();
    VOID empty();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcitos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    empty(buf,64);
    buf[48]=0;
    sprintf(buf,SCANVALUE,num);
    return(vcnumfix(str,buf,strlen(str),0));
    }


