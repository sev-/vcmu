/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:23
*
*   Name            dbmsmatch -- match key
*
*   Description     This functions checks to see if the buffer 
*                   matches the key segment in data
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmsmatch(db,data,buf,nbr)
COUNT db;           /* Number of data base to work with             */
TEXT *data;         /* Pointer to buffer                            */
TEXT *buf;          /* Pointer to key to use for compare            */
COUNT nbr;          /* Key segment number                           */
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsKey *dbk;    /* Pointer to key structure             */
    TEXT *ttrim();  /* Temporary trim function                      */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    COUNT *cptr1,*cptr2;    /* Integer pointers for integers        */
    COUNT retval = FALSE;   /* Return value                         */
    COUNT strncmp();
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0)
        return(-1);         /* invalid database number              */
    dbk = dbp->dbmskey;
    while(nbr--)
        {
        if(dbk->dbkeynext == (struct DbmsKey *) 0)
            return(-1);
        dbk = dbk->dbkeynext;
        }
    data += dbk->dbkeyofst;
    switch(dbk->dbkeytype)
        {
        case 1:
            if(!strncmp(data,buf,dbk->dbkeylen-1))
                retval = TRUE;
            break;
        case 2:
            cptr1 = (COUNT *) data;
            cptr2 = (COUNT *) buf;
            if(*cptr1 == *cptr2)
                retval = TRUE;
            break;
        }
    return(retval);
    }
