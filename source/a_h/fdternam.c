/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:00
*
*   Name            fdternam  -  Find terminal name                 
*                                   
*   Description     Find a terminal name in a termcap string
*
*   Return Value    Returns TRUE if the name in string
*                                   
**/                                 

#include <vcstdio.h>

COUNT fdternam(buffer,tname)
TEXT *buffer;
TEXT *tname;
    {
    TEXT *ptr;
    TEXT *strsset();
    TEXT *term;
    TEXT *ttrim();
    COUNT retval = FALSE;
    COUNT len;
    COUNT strlen();
    ptr = buffer;
    term = ttrim(tname);
    len = strlen(term);
    while(TRUE)
        {
        if( (ptr = strsset(ptr,term)) != NULLTEXT)
            {
            if( (ptr == buffer) || (*(ptr-1) == '|'))
                {
                if((*(ptr+len) == '|') || (*(ptr+len) == ':') ||
                   (*(ptr+len) == '\n') || (*(ptr+len) == '\0') )
                    {
                    retval = TRUE;
                    break;
                    }
                }
            ptr++;
            }
        else
            break;
        }
    return(retval);
    }
