/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:09
*
*   Name            vcedmlin.c - get line for modification
*                                   
*   Description     Retrieves the line from the cashe manager and
*                   stores line in undo list
*
*   Return Value    Returns a pointer to the line in buffer or
*                   NULL if not found
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VCEDLINE *vcedmline(edbuf,line)
VCEDBUF *edbuf;             /* Edit buffer                          */
DBDP line;                  /* Line to retrieve                     */
    {                       /* ------------------------------------ */
    VCEDLINE *retval = (VCEDLINE *)0;   /* Pointer to line          */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT *dbmscmgr();       /* Declare functions used               */
    VOID vcedunalin();      /*    "        "      "                 */
    if(line != (DBDP)0)                 /* If not zero              */
        {                               /*                          */
        cdbdp = line - 1;               /* Get real address         */
        retval = (VCEDLINE *)dbmscmgr(edbuf->bfdnum,&cdbdp,DBMSGET);
#ifdef VCEDFULL
        vcedunline(edbuf,retval,(DBDP)0,line,(DBDP)0,VCEDUNRWT);
#endif
        }                               /* Get line                 */
    return(retval);                     /* Return line              */
    }                                   /* ------------------------ */

