/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:16
*
*   Name            dbmsfromfile - get database from file
*                                   
*   Description     This function gets a database from a file
*                   written by dbmstofile function      
*
*   Return Value    Returns 0 if no errors
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmsfromfile(db,ofile)
COUNT db;           /* Number of data base to work with             */
FILE *ofile;        /* Pointer to file to write on                  */
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    TEXT *ptr;
    COUNT cnt;
    DBDP dataptr;
    TEXT *vcalloc();
    TEXT *dbmscmgr();
    VOID keyadd();
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0)
        return(TRUE);      /* invalid database number               */
    fread(&cnt,sizeof(cnt),1,ofile);
    while(cnt)
        {
        ptr = dbmscmgr(dbp,&dataptr,DBMSPUT);
        fread(ptr,dbp->dbmssize,1,ofile);
        keyadd(dbp,dataptr);
        cnt--;
        }
    return(FALSE);
    }
