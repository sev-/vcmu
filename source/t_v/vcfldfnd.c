/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:31
*
*   Name            vcfldfnd.c - Find field by name or number
*                                   
*   Description     Find a field in a get table
*
*   Return Value    Returns pointer to get item node of field
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

GETITEM *vcfldfnd(tbl,lbl,nbr,flag)
GETTABLE *tbl;              /* Pointer to get table                 */
TEXT *lbl;                  /* Field name to find                   */
COUNT nbr;                  /* Field number to find                 */
COUNT flag;                 /* Flag 0 by name or 1 by number        */
    {                       /* ------------------------------------ */
    GETITEM *retval = (GETITEM *)0; /* Return pointer to field node */
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcfldfnd:";     /* Assign function name     */
    if(vcdbfunc != NULLFUNC)            /* If debug function        */
        (*vcdbfunc)(CONTINUE);          /* Call debug function      */
#endif
    if(tbl == (GETTABLE *) 0)           /* If GETTABLE not passed   */
        tbl = dftgettbl;                /* Assign default table     */
    if(tbl == (GETTABLE *) 0)           /* If table still NULL or   */
        return(retval);                 /* Return not found         */
    retval = tbl->thead;                /* Start at head of list    */
    while(retval != (GETITEM *)0)       /* While more in list       */
        {                               /*                          */
        if(flag)                        /* If look by number        */
            {                           /*                          */
            if(retval->gid == nbr)      /* If number equal          */
                break;                  /* Exit loop                */
            }                           /*                          */
        else                            /*                          */
            {                           /*                          */
            if(!strcmp(lbl,retval->gptr))   /* If name equal        */
                break;                  /* Exit loop                */
            }                           /*                          */
        retval = retval->gnext;         /* Look at next item        */
        }                               /*                          */
    return(retval);                     /* Return pointer to node   */
    }                                   /* ------------------------ */


