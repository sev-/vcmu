/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:14
*
*   Name            dbmsempty - database empty          
*                                   
*   Description     This function deletes all members of a databse 
*
*   Return Value    Returns 0 if no errors
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmsempty(db)
COUNT db;                   /* Number of data base to empty         */
    {                       /* ------------------------------------ */
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0) /* If not valid*/
        return(TRUE);                   /* Return error             */
    dbmsxempty(dbp);                    /* Empty database           */
    return(0);                          /* Return no errors         */
    }                                   /* ------------------------ */

COUNT dbmsxempty(dbp)
struct DbmsInfo *dbp;       /* Pointer to database structure        */
    {                       /* ------------------------------------ */
    struct listbuf *cur;    /* Current list structure               */
    VOID vcfree();          /* Declare functions used               */
    TEXT *dbmscmgr();       /*    "        "      "                 */
    if(dbp == (struct DbmsInfo *)0)     /* If NULL pointer          */
        return(-1);                     /* Return error             */
    cur = dbp->dbmshead;                /* Start at top             */
    while(cur != (struct listbuf *)0)   /* While more in key list   */
        {                               /*                          */
        dbp->dbmshead = cur->listnext;  /* Save next element        */
        vcfree(cur,vcdebug);            /* Free current element     */
        cur = dbp->dbmshead;            /* Assign next element      */
        }                               /*                          */
    dbp->dbmshead = (struct listbuf *)0;/* Clear head of list       */
    dbp->dbmstail = (struct listbuf *)0;/* Clear tail of list       */
    dbp->dbmscur = (struct listbuf *)0; /* Clear current list       */
    dbp->dbmsmemb = 0l;                 /* Zero number of members   */
    dbmscmgr(dbp,(DBDP *)0,DBMSCLEAR);  /* Clear any buffers        */
    return(FALSE);                      /* Return no errors         */
    }                                   /* ------------------------ */

