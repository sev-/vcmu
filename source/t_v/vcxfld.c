/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:15
*
*   Name            vcxfld.c - Extended field 
*                                   
*   Description     Extended Add field to table
*
*   Return Value    Returns pointer to field node
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

GETITEM *vcxfld(row,col,fld,pic,opt,ctrl,nam,val,msg)
COUNT row,col;              /* Row and column for input             */
TEXT *fld;                  /* Pointer to field to place input      */
TEXT *pic;                  /* Pointer to picture to use for input  */
COUNT opt;                  /* Field options                        */
COUNT ctrl;                 /* Field control functions              */
TEXT *nam;                  /* Name for field or NULL               */
PFI val;                    /* Pointer to Validation function       */
TEXT *msg;                  /* Pointer to status message            */
    {                       /* ------------------------------------ */
    GETITEM *vcxxtfld();    /* Low level routine to add field item  */ 
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcxfld:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(vcxxtfld((GETTABLE *)0,(WPTR) 0,row,col,fld,pic,opt,ctrl,nam,
                    val,msg,NULLTEXT,-1,-1,-1,NULLTEXT,NULLFUNC,NULLFUNC,
                    NULLFUNC,0,(COUNT *)0,NULLTEXT));
    }



