/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:40
*
*   Name            keysort -- key sort
*                                   
*   Description     This function inserts into the list in sorted
*                   order
*
*   Return Value    Return 0 if no error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

struct listbuf *keysort(dbp,dbdp,bp)
DBP dbp;
DBDP dbdp;
TEXT *bp;           /* Pointer to buffer to add to the list         */
    {
    COUNT found = FALSE;
    COUNT cmp;      /* -1 for less, 0 for equal ,1 for greater      */
    TEXT *vcalloc();
    TEXT *dbmscmgr();
    struct listbuf *cur;/* Pointer to cur node of list pointer      */
    struct listbuf *cl; /* Pointer to new node of list pointer      */
    DBDP dataptr;       /* Pointer to free duplicate record         */
    COUNT keycomp();
    COUNT askmsg();
    VOID vcfree();
    cl = (struct listbuf *)vcalloc(sizeof(*cl),1,vcdebug);
    cl->listloc = dbdp;
    if(dbp->dbmshead == (struct listbuf *)0)
        {
        dbp->dbmshead = cl;
        dbp->dbmstail = cl;
        cl->listprev = (struct listbuf *)0;
        cl->listnext = (struct listbuf *)0;
        dbp->dbmsmemb++;
        }
    else
        {
        cur = dbp->dbmshead;
        while(cur != (struct listbuf *)0)
            {
            cmp = keycomp(bp,dbmscmgr(dbp,&(cur->listloc),DBMSGET),
                             dbp->dbmskey);
            if(cmp == 0)
                {
                switch(dbp->dbmsdup)
                    {
                    case 0:     /* Reject duplicates                    */
                    case 1:     /* Except duplicates (not working)      */
                        askmsg("Error","Duplicate Key <Not Entered>",0);
                        break;
                    case 2:     /* OverWrite duplicates                 */
                        dbmscmgr(dbp,&(cur->listloc),DBMSFREE);
                        cur->listloc = dbdp;
                        break;
                    }
                vcfree(cl,vcdebug);
                cl = (struct listbuf *)0;
                found = TRUE;
                break;
                }
            if(cmp == -1)
                {
                cl->listprev = cur->listprev;
                cl->listnext = cur;
                if(cur->listprev != (struct listbuf *)0)
                    cur->listprev->listnext = cl;
                cur->listprev = cl;
                if(cur == dbp->dbmshead)
                    dbp->dbmshead = cl;
                dbp->dbmsmemb++;
                found = TRUE;
                break;
                }
            else
                cur = cur->listnext;
            }
        if(!found)
            {
            dbp->dbmstail->listnext = cl;
            cl->listprev = dbp->dbmstail;
            cl->listnext = (struct listbuf *) 0;
            dbp->dbmstail = cl;
            dbp->dbmsmemb++;
            }
        }
    return(cl);
    }
