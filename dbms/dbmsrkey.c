/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:25
*
*   Name            dbmsrkey -- return key
*
*   Description     This functions places key into the area pointed
*                   to by buf             
*
*   Return Value    Returns -1 if error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbmsrkey(db,data,buf,nbr)
COUNT db;           /* Number of data base to work with             */
TEXT *data;         /* Pointer to buffer with key                   */
TEXT *buf;          /* Pointer to location to put key               */
COUNT nbr;          /* Key segment number                           */
    {
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsKey *dbk;    /* Pointer to key structure             */
    TEXT *ttrim();  /* Temporary trim function                      */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    COUNT *cptr1,*cptr2;    /* Integer pointers for integers        */
    COUNT strlen();
    TEXT *strncpy();
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
            strncpy(buf,data,min((strlen(ttrim(buf))),dbk->dbkeylen));
            break;
        case 2:
            cptr1 = (COUNT *) data;
            cptr2 = (COUNT *) buf;
            *cptr2 = *cptr1;
            break;
        }
    return(FALSE);
    }
