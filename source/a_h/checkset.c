/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:07
*
*   Name            checkset  --  Check set
*
*   Description     Check to see if input is in selection set
*
*   Return Value    Returns GOOD or BAD
*
**/

#define VCGET_DEFS
#define SEL_DEFS

#include <vcstdio.h>

COUNT checkset(fld,table)
TEXT *fld;          /* Current temporary field                      */
GETTABLE *table;    /* Pointer to get table                         */
    {
    SELSET *getselitm();
    VOID bell();
    COUNT retval = GOOD;
    if(getselitm(table->tcurnode->gselset,NULLTEXT,fld) == (SELSET *) 0)
        {
        bell();
        retval = BAD;
        }
    return(retval);
    }


