/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:20
*
*   Name            vcedclin.c - current line
*                                   
*   Description     Get the line address by DBDP
*
*   Return Value    Returns pointer to line structure or
*                   NULL if not found
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VCEDLINE *vcedcline(edbuf,line)
VCEDBUF *edbuf;             /* Edit buffer                          */
DBDP *line;                 /* Line to retrieve                     */
    {                       /* ------------------------------------ */
    VCEDLINE *retval = (VCEDLINE *)0;   /* Pointer to line          */
    TEXT *dbmscmgr();       /* Declare functions used               */
    retval = (VCEDLINE *)dbmscmgr(edbuf->bfdnum,line,DBMSPUT);
    return(retval);                     /* Return line              */
    }                                   /* ------------------------ */

