/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:40
*
*   Name            readgets.c  --  Read from get table
*
*   Description     This is the function calls xreadgets using
*                   the default get table then calls clrgets
*                   to clear the table.
*
*   Return Value    Returns the key that caused exit
*
**/

#define VCERROR_DEFS
#define VCGET_DEFS
#include <vcstdio.h>

COUNT readgets()
    {
    COUNT retval;
    COUNT xreadgets();
    COUNT clrgets();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "readgets:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( dftgettbl != (GETTABLE *) 0 )
        {
        retval = xreadgets(dftgettbl);
        clrgets(dftgettbl);
        return(retval);
        }
    else
        {
        vcerror=NOGETBL;
        return(-1);   /*No default get table has been created yet */
        }
    }




