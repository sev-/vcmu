/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:36
*
*   Name            keydup -- dupicate keys
*                                   
*   Description     Set duplicate flag for database on or off
*
*   Return Value    Return previous value of flag
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT keydup(db,flag)
COUNT db;       /* Data Base Number                                 */
COUNT flag;     /* 0 = reject : 1 = accept : 2 overwrite            */
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    COUNT retval;
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0)
        return(-1); /* wrong database number       */
    retval = dbp->dbmsdup;
    dbp->dbmsdup = ((flag >= 0) && (flag <=2) ? flag :  0);
    return(retval);
    }

