/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:38
*
*   Name            keyfind -- key list find
*                                   
*   Description     Finds greater than or equal key in link list
*
*   Return Value    Returns list buffer control or NULL if end of list
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

struct listbuf *keyfind(dbp,bp)
DBP dbp;
TEXT *bp;           /* Pointer to buffer with label looking for     */
    {
    struct listbuf *lbh;
    struct listbuf *rbuf=(struct listbuf *)0;
    TEXT *dbmscmgr();
    COUNT cmp;
    COUNT keycomp();
    lbh = dbp->dbmshead;
    while(lbh != (struct listbuf *)0)
        {
        cmp = keycomp(bp,dbmscmgr(dbp,&(lbh->listloc),DBMSGET),
                                     dbp->dbmskey);
        if((cmp == -1) || (cmp == 0))
            {
            rbuf = lbh;
            break;
            }
        lbh = lbh->listnext;
        }
    return(rbuf);
    }
