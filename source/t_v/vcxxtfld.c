/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:18
*
*   Name            vcxxtfld.c - Extended field 
*                                   
*   Description     Extended Add field to table
*
*   Return Value    Returns pointer to field node
*                                   
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

GETITEM *vcxxtfld(tblptr,wptr,row,col,fld,pic,opt,ctrl,nam,val,msg,help,
                          act,nact,width,lst,pre,post,pl,id,cnt,xptr)
GETTABLE *tblptr;           /* Pointer to fldtable to use           */
WPTR wptr;                  /* Pointer to Window                    */
COUNT row,col;              /* Row and column for input             */
TEXT *fld;                  /* Pointer to field to place input      */
TEXT *pic;                  /* Pointer to picture to use for input  */
COUNT opt;                  /* Option byte for field                */
COUNT ctrl;                 /* Control Byte for field               */
TEXT *nam;                  /* Field name                           */
PFI val;                    /* Pointer to Validation function       */
TEXT *msg;                  /* Pointer to status message            */
TEXT *help;                 /* Pointer to help text                 */
COUNT act;                  /* Active attribute                     */
COUNT nact;                 /* Non Active attribute                 */
COUNT width;                /* Input width to use                   */
TEXT *lst;                  /* Pointer to list structure            */
PFI pre;                    /* Pointer to pre-function              */
PFI post;                   /* Pointer to post-function             */
PFI pl;                     /* Pointer to pick list function        */
COUNT id;                   /* Item id number                       */
COUNT *cnt;                 /* Extra COUNT pointer for programmer   */
TEXT *xptr;                 /* Extra TEXT pointer for programmer    */
    {
    GETTABLE *tblalloc();
    GETITEM *nodeptr, *getalloc();
    TEXT *vcalloc(), *tmppic();
    COUNT attr;
    COUNT datatype;
    COUNT gettype();
    VOID getsay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcxxtfld:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef WINDOW
    if(wptr == (WPTR)0)
        wptr = wdoctrl->wcurrent;
#endif
    if(tblptr == (GETTABLE *)0)
        tblptr = dftgettbl;
    if(tblptr == (GETTABLE *)0)
        {
        if((tblptr=tblalloc(NULLTEXT,-1,NULLFUNC)) == (GETTABLE *)0 )
            return((GETITEM *)0);
#ifdef WINDOW
        tblptr->twptr = wptr;
#endif
        }
    if( (nodeptr=getalloc()) == (GETITEM *)0 )
        {
        vcerror=NOGETMEM;
        return((GETITEM *)0);
        }
    if( tblptr->thead == (GETITEM *)0 )
        tblptr->thead = tblptr->ttail = nodeptr;
    else
        {
        tblptr->ttail->gnext=nodeptr;
        tblptr->ttail=nodeptr;
        }
#ifdef WINDOW
    if(!wdoctrl->wno_opn || override)
#endif
        wptr = (WPTR) 0;
    if(opt == -1)
        {
        datatype = (ctrl >> 7) & 15;
        opt = datactrl[datatype];
        }
    nodeptr->g_row = row;
    nodeptr->g_col = col;
    nodeptr->g_field = fld;
    nodeptr->g_picture = pic;
    nodeptr->gdispsiz = width;
    nodeptr->gcontrol = opt;
    nodeptr->gfldtyp = ctrl;
    nodeptr->gselset = lst;
    nodeptr->gprefunc=pre;
    nodeptr->gpostfunc=post;
    nodeptr->gplist = pl;
    nodeptr->gwptr = wptr;
    nodeptr->gcndx = -1;
    nodeptr->gid = id;
    nodeptr->gptr = nam;
    nodeptr->gnbr = cnt;
    nodeptr->gxptr = xptr;
    nodeptr->g_msg = msg;
    nodeptr->g_help = help;
    nodeptr->g_funptr = val;
    nodeptr->gstart = FALSE;
    nodeptr->gredraw = FALSE;
    nodeptr->gfkey = TRUE;

    datatype = (nodeptr->gfldtyp >> 11) & 15;

    if( datapre[datatype] )
        {
        if((*datapre[datatype])(nodeptr))
            return((GETITEM *)0);
        }
    else
        return((GETITEM *)0);

      if(nact == vc.dflt)
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            nodeptr->gcurattr = nodeptr->gattrnag = attr = wptr->nget_at;
        else
#endif
            nodeptr->gcurattr = nodeptr->gattrnag = attr = attrnag;
    else
        nodeptr->gcurattr = nodeptr->gattrnag = attr = nact;
    if(act == vc.dflt)
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            nodeptr->gattrag = wptr->get_at;
        else
#endif
            nodeptr->gattrag = attrag;
    else
        nodeptr->gattrag = act;
    nodeptr->gcurattr = attr;

    datatype = (nodeptr->gfldtyp >> 7) & 15;

    if(datainit[datatype] != NULLFUNC)
        (*datainit[datatype])(nodeptr);

    if(!(tblptr->tctrl & QDISPLAY))
        getsay(nodeptr);
    return(nodeptr);
    }
