/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:19
*
*   Name            dbmskadd - add data base key        
*                                   
*   Description     This function adds a new key to data base      
*
*   Return Value    Returns 0 if no errors
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmskadd(nbr,ofset,len,type)
COUNT nbr;
COUNT ofset;
COUNT len;
COUNT type;
    {
    struct DbmsKey *dbk;    /* Pointer to key info                  */
    struct DbmsInfo *dbp;   /* Pointer to database structure        */
    struct DbmsInfo *dbmsfnbr();
    VOID dbmsklink();
    TEXT *vcalloc();
    if( (dbp = dbmsfnbr(nbr)) == (DBP) 0)
        return(-1);
    dbk = (struct DbmsKey *)vcalloc(1,sizeof(*dbk),vcdebug);
    dbk->dbkeyofst = ofset;
    dbk->dbkeylen = len;
    dbk->dbkeytype = type;
    dbk->dbkeynext = (struct DbmsKey *)0;
    dbmsklink(&(dbp->dbmskey),dbk);
    return(0);
    }
