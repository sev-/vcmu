/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:43
*
*   Name            dbmscls -- close data base                     
*                                   
*   Description     This closes a database and frees all memory
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmscls(db)
COUNT db;                   /* Data Base Number                     */
    {                       /* ------------------------------------ */
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0) /* Valid dbms  */
        return(-1);                     /* Invalid database number  */
    dbmsxcls(dbp);                      /* Clear database           */
    return(0);                          /* Return no errors         */
    }                                   /* ------------------------ */

COUNT dbmsxcls(dbp)
struct DbmsInfo *dbp;       /* Data Base Data Pointer               */
    {                       /* ------------------------------------ */
    struct listbuf *lbp;    /* Used as temporary pointer to buffer  */
    struct DbmsInfo *pdbp;  /* Pointer to previous database info    */
    struct DbmsInfo *cdbp;  /* Pointer to current database info     */
    struct DbmsKey *dbk;    /* Pointer to key structure             */
    VOID vcfree();          /* Declare functions used               */
    TEXT *dbmscmgr();       /*    "        "      "                 */
    if(dbp == (struct DbmsInfo *)0)     /* If NULL pointer          */
        return(-1);                     /* Return error             */
    dbmsxempty(dbp);                    /* Empty database           */
    dbk = dbp->dbmskey;                 /* Find key structure       */
    while(dbk != (struct DbmsKey *)0)   /* While more key           */
        {                               /*                          */
        dbp->dbmskey = dbk->dbkeynext;  /* Store next key           */
        vcfree(dbk,vcdebug);            /* Free key node            */
        dbk = dbp->dbmskey;             /* Assign next key          */
        }                               /*                          */
    cdbp = dbmsinfo;                    /* Start at top of dbms list*/
    pdbp = (struct DbmsInfo *)0;        /* Null out previous entry  */
    while(cdbp != (struct DbmsInfo *)0) /* While more dbms struct   */
        {                               /*                          */
        if(cdbp == dbp)                 /* If current found         */
            {                           /*                          */
            if(dbp == dbmsinfo)         /* If the first in list     */
                dbmsinfo = dbp->dbmsnext;       /* Assign next first*/
            if(pdbp != (struct DbmsInfo *)0)    /* If a previous    */
                pdbp->dbmsnext = dbp->dbmsnext; /* Assign prev      */
            break;                      /* Break from loop          */
            }                           /*                          */
        pdbp = cdbp;                    /* Assign previous structure*/
        cdbp = cdbp->dbmsnext;          /* Get next structure       */
        }                               /*                          */
    vcfree(dbp,vcdebug);                /* Free info structure      */
    return(0);                          /* Return no error          */
    }                                   /* ------------------------ */
