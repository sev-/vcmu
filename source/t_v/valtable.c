/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:19:01
*
*   Name            valtable.c  --  Validate a get table
*
*   Description     This function validate the entire get table
*                   by calling each validation function
*
*   Return Value    Returns NULL or invalid item
*
**/

#define VCGET_DEFS

#include <vcstdio.h>

GETITEM *valtable(table)
GETTABLE *table;
    {
    GETITEM *ci;
    GETITEM *gi;
    ci = table->tcurnode;
    gi = table->thead;
    while(gi != (GETITEM *) 0)
        {
        table->tcurnode = gi;
        if(gi->g_funptr != NULLFUNC)
            {
            if((*gi->g_funptr)(gi->gtmpfld,table) != GOOD)
                break;
            }
        gi = gi->gnext;
        }
    table->tcurnode = ci;
    return(gi);
    }

