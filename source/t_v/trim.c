/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:38
*
*   Name            trim.c --  Trim string
*
*   Description     Trims trailing blanks     
*                   
*   Return Value    Returns pointer to string   
*
**/

#include <vcstdio.h>

TEXT *trim( str )
TEXT *str;
    {
    TEXT *ptr;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "trim:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ptr=str;
    while( *ptr )
        ptr++;
    ptr--;
    while( ptr >= str && *ptr==' ' )
        ptr--;
    ++ptr;
    *ptr='\0';
    return(str);
    }


    
        
