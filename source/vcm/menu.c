/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:14
*
*   Name            menu.c  --  execute menu by name
*
*   Description     This function executes a menu by name.  Note:
*                   name of a menu is also it's title.
*
*   Return Value    Returns -1 if error
*                    
*
**/

#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT menu(name) 
TEXT *name;
    {
    VCMENU *getmnuptr();
    COUNT vcmenu();
    return(vcmenu(getmnuptr(name)));
    }


