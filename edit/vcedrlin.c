/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:35
*
*   Name            vcedrlin.c - rewrite line
*                                   
*   Description     Low level routine to tell cashe manager to rewrite
*                   line
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedrline(edbuf,lptr,addr)
VCEDBUF *edbuf;             /* Edit buffer                          */
VCEDLINE *lptr;             /* Current line                         */
DBDP addr;                  /* Address of current line              */
    {                       /* ------------------------------------ */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT *dbmscmgr();       /* Declare functions used               */
    if(lptr != (DBDP)0)                 /* If valid line            */
        {                               /*                          */
        cdbdp = addr - 1;               /* Get real address         */
        dbmscmgr(edbuf->bfdnum,&cdbdp,DBMSSAVE);/* Put new values   */
        edbuf->bfchange = TRUE;         /* Flag buffer changed      */
        }                               /*                          */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */

