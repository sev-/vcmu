/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:18
*
*   Name            dbmsikey -- put key
*
*   Description     This functions put the key into the proper 
*                   location in the buffer
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmsikey(db,data,buf,nbr)
COUNT db;           /* Number of data base to work with             */
TEXT *data;         /* Pointer to buffer needing key                */
TEXT *buf;          /* Pointer to key to insert into buffer area    */
COUNT nbr;          /* Key segment number                           */
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsKey *dbk;    /* Pointer to key structure             */
    TEXT *ttrim();  /* Temporary trim function                      */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    COUNT *cptr1,*cptr2;    /* Integer pointers for integers        */
    TEXT *strncpy();
    COUNT strlen();
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
            if(strlen(buf) > dbk->dbkeylen)
                {
                strncpy(data,buf,dbk->dbkeylen-1);
                *(data+dbk->dbkeylen) = '\0';
                }
            else
                strcpy(data,buf);
            break;
        case 2:
            cptr1 = (COUNT *) data;
            cptr2 = (COUNT *) buf;
            *cptr1 = *cptr2;
            break;
        }
    return(FALSE);
    }
