/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:23:12
*
*   Name            xatgetsay.c - extended atgetsay
*
*   Description     Places the entry into the get table say node
*                   and displays if QDISPLAY is not in effect
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#define VCGET_DEFS
#include <vcstdio.h>

COUNT xatgetsay(tblptr,wptr,row,col,fld,attr,lr,lc,control)
GETTABLE *tblptr;   /* Pointer to get table                         */
WPTR wptr;          /* Pointer to Window                            */
COUNT row,col;      /* Row and Column or Upper left coord. for box  */
TEXT *fld;          /* Pointer to field or NULL for box             */
COUNT attr;         /* Attribute to use                             */
COUNT lr,lc;        /* Lower right row and column                   */
COUNT control;      /* Control byte                                 */
    {
    GETTABLE *tblalloc();
    SAYITEM *nodeptr, *getsayalloc();
    VOID sayget();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "xatgetsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(tblptr == (GETTABLE *)0)
        tblptr = dftgettbl;
    if(tblptr == (GETTABLE *)0)
        {
        if((tblptr=tblalloc(NULLTEXT,-1,NULLFUNC)) == (GETTABLE *)0 )
            return(-1);
#ifdef WINDOW
        tblptr->twptr = wptr;
#endif
        }
#ifdef WINDOW
    if( wptr == (WPTR)0)
        if(wdoctrl->wno_opn)
            wptr=wdoctrl->wcurrent;
#endif
    if( (nodeptr=getsayalloc())== (SAYITEM *)0 )
        {
        vcerror=NOSAYMEM;
        return(-1);
        }
    if( tblptr->tsayhead == (SAYITEM *) 0)
        {
        tblptr->tsayhead=tblptr->tsaytail=nodeptr;
        }
    else
        {
        tblptr->tsaytail->snnext=nodeptr;
        tblptr->tsaytail=nodeptr;
        }
    nodeptr->snrow = row;
    nodeptr->sncol = col;
    nodeptr->snfld = fld;
    nodeptr->snbrow = lr;
    nodeptr->snbcol = lc;
    nodeptr->snctrl = control;
    nodeptr->snwptr = wptr;
    if(attr == vc.dflt)
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            nodeptr->snattr = wptr->say_at;
        else
#endif
            nodeptr->snattr = attrsay;
    else
        nodeptr->snattr = attr;
    if(!wdoctrl->wno_opn || override)
        wptr = (WPTR) 0;
    if(!(tblptr->tctrl & QDISPLAY))
        sayget(nodeptr);
    return(0);
    }

/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 64946  
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 10/27/88 at 10:41:33
*
*   Name            getsayalloc.c  --  Allocate space for get
*
*   Description     This function allocates space for an entry in the
*                   get table.
*
*   Return Value    Returns NULL if error 
*
**/

SAYITEM *getsayalloc()
    {
    TEXT *vcalloc();
    SAYITEM *node;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "getsayalloc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    node=(SAYITEM *)vcalloc(1,sizeof(SAYITEM),vcdebug);
    if( node == (SAYITEM *)0 )
        {
        vcerror = NOSAYMEM;
        return((SAYITEM *)0);
        }
    return(node);
    }






