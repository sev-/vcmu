/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:21
*
*   Name            dbmslink - add database control    
*                                   
*   Description     This function adds a new database control      
*
*   Return Value    VOID
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

VOID dbmslink(dbp)
struct DbmsInfo *dbp;
    {
    struct DbmsInfo *cdbp;   /* Pointer to current database info     */
    if(dbmsinfo == (struct DbmsInfo *)0)
        {
        dbmsinfo = dbp;
        }
   else
        {
        cdbp = dbmsinfo;
        while(cdbp->dbmsnext != (struct DbmsInfo *)0)
             cdbp = cdbp->dbmsnext;
        cdbp->dbmsnext = dbp;
        }
    }
