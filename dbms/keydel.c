/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:34
*
*   Name            keydel -- list delete 
*                                   
*   Description     Delete buffer from key list
*
*   Return Value    VOID
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

VOID keydel(dbp,lbp)
DBP dbp;
struct listbuf *lbp;    /* Pointer buffer to delete                 */
    {
    VOID vcfree();
    if(lbp == (struct listbuf *) 0)
        return;
    if(lbp == dbp->dbmshead)
        {
        dbp->dbmshead = lbp->listnext;
        if(lbp->listnext != (struct listbuf *) 0 )
            lbp->listnext->listprev = (struct listbuf *) 0;
        }
    else
        {
        lbp->listprev->listnext = lbp->listnext;
        }
    if(lbp == dbp->dbmstail)
        {
        dbp->dbmstail = lbp->listprev;
        if(lbp->listprev != (struct listbuf *)0)
            lbp->listprev->listnext = (struct listbuf *)0;
        }
    else
        {
        lbp->listnext->listprev = lbp->listprev;
        }
    vcfree((TEXT *)lbp,vcdebug);
    dbp->dbmsmemb--;
    }
