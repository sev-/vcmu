/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:20
*
*   Name            dbmsklink - link new key            
*                                   
*   Description     This function adds a new key to database structure
*
*   Return Value    VOID
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

VOID dbmsklink(dbk,ndbk)
struct DbmsKey **dbk;
struct DbmsKey *ndbk;
    {
    struct DbmsKey *cdbk;    /* Pointer to current database key      */
    if(*dbk == (struct DbmsKey *)0)
        {
        *dbk = ndbk;
        }
   else
        {
        cdbk = *dbk;
        while(cdbk->dbkeynext != (struct DbmsKey *)0)
             cdbk = cdbk->dbkeynext;
        cdbk->dbkeynext = ndbk;
        }
    }
