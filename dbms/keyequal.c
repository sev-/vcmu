/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:37
*
*   Name            keyequal -- Key equal
*                                   
*   Description     Find an entry in key link list
*
*   Return Value    Returns pointer to list buffer control or
*                   NULL if not found
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

struct listbuf *keyequal(dbp,bp)
DBP dbp;
TEXT *bp;           /* Pointer to buffer with label looking for     */
    {
    struct listbuf *rbuf=(struct listbuf *) 0;
    struct listbuf *lbh;
    COUNT keycomp();
    COUNT cmp;
    TEXT *dbmscmgr();
    lbh = dbp->dbmshead;
    while(lbh != (struct listbuf *) 0)
        {
        cmp = keycomp(bp,dbmscmgr(dbp,&(lbh->listloc),DBMSGET),dbp->dbmskey);
        if(cmp == 0)
            {
            rbuf = lbh;
            break;
            }
        lbh = lbh->listnext;
        }
    return(rbuf);
    }
