/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:29
*
*   Name            getwdef -- get window definition
*                                   
*   Description     Gets a pointer to the window definition
*
*   Return Value    Returns pointer to structure or NULL
*                   if not found
*                                   
**/                                 

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

WDEF *getwdef(name)
TEXT *name;
    {
    WDEF *cptr = (WDEF *)0;
    COUNT strcmp();
    if(name != NULL)
        {
        cptr = wdoctrl->wdefine;
        while(cptr != (WDEF *)0)
            {
            if(!strcmp(name,cptr->wdefname))
                break;
            cptr = cptr->wdefnext;
            }
        }
    return(cptr);
    }
