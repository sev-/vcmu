/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:30
*
*   Name            getwstyle -- get window style
*                                   
*   Description     Gets a pointer to the window style
*
*   Return Value    Returns pointer to structure or NULL
*                   if not found
*                                   
**/                                 

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

WSTYLE *getwstyle(name)
TEXT *name;
    {
    WSTYLE *cptr = (WSTYLE *)0;
    COUNT strcmp();
    if(name != NULL)
        {
        cptr = wdoctrl->wstyle;
        while(cptr != (WSTYLE *)0)
            {
            if(!strcmp(name,cptr->wstylnam))
                break;
            cptr = cptr->wstylnext;
            }
        }
    return(cptr);
    }
