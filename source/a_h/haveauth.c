/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:35
*
*   Name            haveauth.c  --  have authority
*
*   Description     Decides if the user has the authority to use 
*                   field for task specified.
*
*   Return Value    Returns True if user has can do specified task
*                   False if not.
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT haveauth(authlevel,task)
COUNT authlevel;
COUNT task;              /* VIEW, EDIT    (EDIT implies VIEW)    */ 
    {
#ifdef VCDEBUG
    vcdebug = (TEXT *) "haveauth:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( task == FLDVIEW )
        {
        if( (userlevel - ((userlevel / 10)*10)  ) >= 
            (authlevel - ((authlevel / 10)*10)  ) )
            return(TRUE);
        return(FALSE);
        }
    if( task == FLDEDIT )
        {
        if( (userlevel / 10) >= (authlevel / 10) )
            return(TRUE);
        return(FALSE);
        }
    return(FALSE);
    }


