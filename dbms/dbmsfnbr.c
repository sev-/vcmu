/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:15
*
*   Name            dbmsfnbr - database find number     
*                                   
*   Description     This function finds a data base control by
*                   number     
*
*   Return Value    Returns pointer to data base control for this
*                   number
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

struct DbmsInfo *dbmsfnbr(nbr)
PFAST nbr;
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    dbp = dbmsinfo;
    while(dbp != (struct DbmsInfo *)0)
        {
        if(dbp->dbmsnbr == nbr)
            break;
        else
            dbp = dbp->dbmsnext;
        }
    return(dbp);
    }
