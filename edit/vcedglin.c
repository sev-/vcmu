/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:49
*
*   Name            vcedglin.c - get line
*                                   
*   Description     Gets a line from the database
*
*   Return Value    Returns pointer to line structure of line
*                   requested or NULL
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VCEDLINE *vcedgline(edbuf,line)
VCEDBUF *edbuf;             /* Edit buffer                          */
DBDP line;                  /* Line to retrieve                     */
    {                       /* ------------------------------------ */
    VCEDLINE *retval = (VCEDLINE *)0;   /* Pointer to line          */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT *dbmscmgr();       /* Declare functions used               */
    if(line != (DBDP)0)                 /* If not zero              */
        {                               /*                          */
        cdbdp = line - 1;               /* Get real address         */
        retval = (VCEDLINE *)dbmscmgr(edbuf->bfdnum,&cdbdp,DBMSGET);
        }                               /* Get line                 */
    return(retval);                     /* Return line              */
    }                                   /* ------------------------ */

