/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:23
*
*   Name            gettblptr.c  --  Get table pointer
*
*   Description     Get a pointer to the get table node associated
*                   with the given symbolic name
*
*   Return Value    Returns pointer to node or NULL if not found
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

GETTABLE *gettblptr(nam)
TEXT *nam;
    {
    GETTABLE *np;
    COUNT strcmp();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "gettblptr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( nam == NULLTEXT )
        {
        vcerror = SYMREQ;  
        return((GETTABLE *) 0);
        }
    if( (np = dftgettbl) == (GETTABLE *) 0 )
        {
        vcerror = NOTABLE;
        return((GETTABLE *)0);
        }
    while(np)
        {
        if( strcmp(np->table_name,nam)==0 )
            {
            if( np->tmagic == GETTBLMAGIC )
                return(np);
            else
                {
                vcerror = BADTABLE;
                return((GETTABLE *) 0);
                }
            }
        np=np->tnext;
        }
    vcerror = NOSYM;  
    return((GETTABLE *) 0);
    }


