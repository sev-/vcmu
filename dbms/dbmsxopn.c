/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:30
*
*   Name            dbmsxopn - database create          
*                                   
*   Description     This creates new record in the data base       
*
*   Return Value    Returns pointer to database control structure
*                   or NULL if error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

DBP dbmsxopn(nbr,size,ofset,len,type,pages,slots)
COUNT nbr;    
COUNT size;
COUNT ofset;
COUNT len;
COUNT type;
COUNT pages;
COUNT slots;
    {
    DBP dbp = (DBP)0;       /* Pointer to current database info     */
    struct DbmsKey *dbk;    /* Pointer to key info                  */
    DBP dbmsfnbr();         /* Find data base by number             */
    TEXT *vcalloc();
    VOID dbmslink();
    if((nbr != -1) && (dbmsfnbr(nbr) != (DBP) 0))
        return(dbp); /* number currently being used */
    if((dbp = (struct DbmsInfo *)vcalloc(1,sizeof(*dbp),vcdebug)) ==
              (struct DbmsInfo *)0)
        return(dbp); /* error in allocation         */
    dbp->dbmsnext = (struct DbmsInfo *)0;
    dbp->dbmshead = (struct listbuf *)0;
    dbp->dbmstail = (struct listbuf *)0;
    dbp->dbmsnbr = nbr;
    dbp->dbmssize = size;
    dbp->dbmspags = pages;
    dbp->dbmsslots = slots;
    dbp->dbmsmemb = 0;
    dbp->dbmsapags = 0;
    dbp->dbmsdup = 0;
    dbp->dbmschead = (struct DbmsCashe *)0;
    dbp->dbmsctail = (struct DbmsCashe *)0;
    dbp->dbmsnslot = (DBDP ) 0;
    dbp->dbmsdslot = (DBDP ) 0;
    dbp->dbmsfname = NULL;
    dbp->dbmsfile = (FILE *) 0;
    dbp->dbmsfopn = FALSE;
    dbk = (struct DbmsKey *)vcalloc(1,sizeof(*dbk),vcdebug);
    dbk->dbkeyofst = ofset;
    dbk->dbkeylen = len;
    dbk->dbkeytype = type;
    dbk->dbkeynext = (struct DbmsKey *)0;
    dbp->dbmskey = dbk;
    dbmslink(dbp);
    return(dbp);
    }
