/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 8/31/90 at 23:18:31
*
*   Name            keyadd -- list add
*                                   
*   Description     Add buffer to Key list
*
*   Return Value    Return 0 if no error
*                                   
**/                                 

#include <vcstdio.h>
#include <vcdbms.h>

COUNT keyadd(dbp,dbdp)
DBP dbp;
DBDP dbdp;
    {
    TEXT *vcalloc();
    struct listbuf *cl; /* Pointer to new node of get pointer       */
    cl = (struct listbuf *)vcalloc(sizeof(*cl),1,vcdebug);
    cl->listloc = dbdp;
    cl->listnext = (struct listbuf *)0;
    if(dbp->dbmshead == (struct listbuf *)0)
        {
        dbp->dbmshead  = cl;
        dbp->dbmstail = cl;
        cl->listprev = (struct listbuf *) 0;
        }
    else
        {
        dbp->dbmstail->listnext = cl;
        cl->listprev = dbp->dbmstail;
        dbp->dbmstail = cl;
        }
    dbp->dbmsmemb++;
    return(0);
    }
