/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:41
*
*   Name            dbms -- data base                     
*                                   
*   Description     This is the interface into the simple link list
*                   data base
*
*   Return Value    Returns postive if error - zero if no error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT dbms(db,buffer,mode)
COUNT db;           /* Data Base Number                             */
TEXT *buffer;       /* Pointer to buffer                            */
COUNT mode;         /* Operation                                    */
    {
    struct listbuf *lbp;    /* Used as temporary pointer to buffer  */
    struct listbuf *keyfind(); /* Function to find GTE in list      */
    struct listbuf *keyequal();/* Function to find buffer in list   */
    struct DbmsInfo *dbp;   /* Pointer to current database info     */
    struct DbmsInfo *dbmsfnbr();/* Find pointer to database control */
    TEXT *dbmscmgr(); /* Database data cashe manager                */
    COUNT retval;   /* Return Value                                 */
    TEXT *bufptr;   /* Buffer pointer for creating buffers          */
    LONG *lptr;     /* Long pointer for count                       */
    DBDP dataptr;   /* Database pointer value                       */
    TEXT *vcalloc();
    VOID vcmem();
    struct listbuf *keysort();
    VOID keydel();
    if((dbp = dbmsfnbr(db)) == (struct DbmsInfo *)0)
        return(FALSE); /* wrong database number       */
    switch(mode)
        {
        case DBMSNXTREC:
            if( dbp->dbmscur != (struct listbuf *) 0)
                {
                lbp = dbp->dbmscur->listnext;
                if(lbp != (struct listbuf *) 0)
                    {
                    vcmem(buffer,dbmscmgr(dbp,&(lbp->listloc),DBMSGET)
                             ,dbp->dbmssize);
                    dbp->dbmscur = lbp;
                    retval = TRUE;
                    }
                else
                    retval = FALSE;
                break;
                }
        case DBMSFRSREC:
            if(dbp->dbmshead != (struct listbuf *)0)
                {
                vcmem(buffer,dbmscmgr(dbp,&(dbp->dbmshead->listloc),DBMSGET)
                         ,dbp->dbmssize);
                dbp->dbmscur = dbp->dbmshead;
                retval = TRUE;
                }
            else
                retval = FALSE;
            break;
        case DBMSPRVREC:
            if( dbp->dbmscur != (struct listbuf *) 0)
                {
                lbp = dbp->dbmscur->listprev;
                if(lbp != (struct listbuf *) 0)
                    {
                    vcmem(buffer,dbmscmgr(dbp,&(lbp->listloc),DBMSGET)
                             ,dbp->dbmssize);            
                    dbp->dbmscur = lbp;
                    retval = TRUE;
                    }
                else
                    retval = FALSE;
                break;
                }
        case DBMSLSTREC:
            if(dbp->dbmstail != (struct listbuf *)0)
                {
                vcmem(buffer,dbmscmgr(dbp,&(dbp->dbmstail->listloc),DBMSGET)
                         ,dbp->dbmssize);            
                dbp->dbmscur = dbp->dbmstail;
                retval = TRUE;
                }
            else
                retval = FALSE;
            break;
        case DBMSEQUREC:
            if((lbp = keyequal(dbp,buffer)) == (struct listbuf *)0)
                retval = FALSE;
            else
                {
                vcmem(buffer,dbmscmgr(dbp,&(lbp->listloc),DBMSGET)
                         ,dbp->dbmssize);
                dbp->dbmscur = lbp;
                retval = TRUE;
                }
            break;
        case DBMSGTEREC:          
            if((lbp = keyfind(dbp,buffer)) == (struct listbuf *)0)
                retval = FALSE;
            else
                {
                vcmem(buffer,dbmscmgr(dbp,&(lbp->listloc),DBMSGET)
                         ,dbp->dbmssize);            
                dbp->dbmscur = lbp;
                retval = TRUE;
                }
            break;
        case DBMSADDREC:
            if( (bufptr = dbmscmgr(dbp,&dataptr,DBMSPUT)) == NULL)
                retval = FALSE;
            else
                {
                vcmem(bufptr,buffer,dbp->dbmssize);
                dbp->dbmscur = keysort(dbp,dataptr,buffer);
                retval = TRUE;
                }
            break;
        case DBMSDELREC:
            if(dbp->dbmscur != (struct listbuf *) 0)
                {
                lbp = dbp->dbmscur;
                if( lbp->listnext != (struct listbuf *) 0)
                    dbp->dbmscur = lbp->listnext;
                else
                    {
                    if( lbp->listprev != (struct listbuf *)0)
                        dbp->dbmscur = lbp->listprev;
                    else
                        dbp->dbmscur = (struct listbuf *) 0;
                    }
                keydel(dbp,lbp);
                dbmscmgr(dbp,&(lbp->listloc),DBMSFREE);
                }                
            break;
        case DBMSRWTREC:
            if((lbp = keyequal(dbp,buffer)) == (struct listbuf *)0)
                retval = FALSE;
            else
                {
                vcmem(dbmscmgr(dbp,&(lbp->listloc),DBMSGET),buffer
                         ,dbp->dbmssize);
                dbp->dbmscur = lbp;
                retval = TRUE;
                dbmscmgr(dbp,&(dbp->dbmscur->listloc),DBMSSAVE);
                }
            break;
        case DBMSCNTREC:
            lptr = (LONG *) buffer;
            *lptr = dbp->dbmsmemb;
            retval = TRUE;
            break;
        }
    return(retval);
    }
