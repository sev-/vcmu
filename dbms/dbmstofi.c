/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:27
*
*   Name            dbmstofile - database to file       
*                                   
*   Description     This function writes entire database to file
*                   for later retrieval   
*
*   Return Value    Returns 0 if no errors
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmstofile(db,ofile)
COUNT db;           /* Number of data base to work with             */
FILE *ofile;        /* Pointer to file to write on                  */
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    COUNT cnt;      /* Counting variable                            */
    TEXT *dbmscmgr();
    struct listbuf *lbh;
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0)
        return(TRUE);      /* invalid database number               */
    cnt = (COUNT)dbp->dbmsmemb;
    fwrite(&cnt,sizeof(cnt),1,ofile);
    lbh = dbp->dbmshead;
    while(lbh != (struct listbuf *) 0)
        {
        fwrite(dbmscmgr(dbp,&(lbh->listloc),DBMSGET),dbp->dbmssize,1,ofile);
        lbh = lbh->listnext;
        }
    return(FALSE);
    }
