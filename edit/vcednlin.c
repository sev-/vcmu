/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:18
*
*   Name            vcednlin.c - next line
*                                   
*   Description     Retrieves the next line from the cashe manager
*
*   Return Value    Returns a pointer to the line in buffer or
*                   NULL if not found
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VCEDLINE *vcednline(edbuf,lptr)
VCEDBUF *edbuf;             /* Edit buffer                          */
VCEDLINE *lptr;             /* Current line                         */
    {                       /* ------------------------------------ */
    VCEDLINE *retval = (VCEDLINE *)0;   /* Pointer to next line     */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT *dbmscmgr();       /* Declare functions used               */
    if(lptr->lnext != (DBDP)0)          /* If there is a next line  */
        {                               /*                          */
        cdbdp = lptr->lnext - 1;        /* Get real address         */
        retval = (VCEDLINE *)dbmscmgr(edbuf->bfdnum,&cdbdp,DBMSGET);
        }                               /* Get next line            */
    return(retval);                     /* Return next line         */
    }                                   /* ------------------------ */

