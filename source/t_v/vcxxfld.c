/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:16
*
*   Name            vcxxfld.c - Extended field 
*                                   
*   Description     Extended Add field to table
*
*   Return Value    Returns pointer to field node
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

GETITEM *vcxxfld(row,col,fld,pic,opt,ctrl,nam,val,msg,help,width,lst,id)
COUNT row,col;              /* Row and column for input             */
TEXT *fld;                  /* Pointer to field to place input      */
TEXT *pic;                  /* Pointer to picture to use for input  */
COUNT opt;                  /* Field options                        */
COUNT ctrl;                 /* Field control functions              */
TEXT *nam;                  /* Name for field or NULL               */
PFI val;                    /* Pointer to Validation function       */
TEXT *msg;                  /* Pointer to status message            */
TEXT *help;                 /* Pointer to help text                 */
COUNT width;                /* Input width to use                   */
TEXT *lst;                  /* Pointer to list structure            */
COUNT id;                   /* Id number for field                  */
    {                       /* ------------------------------------ */
    GETITEM *vcxxtfld();    /* Low level routine to add field item  */ 
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcxxfld:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(vcxxtfld((GETTABLE *)0,(WPTR) 0,row,col,fld,pic,opt,ctrl,nam,
                    val,msg,help,-1,-1,width,lst,NULLFUNC,NULLFUNC,
                    NULLFUNC,id,(COUNT *)0,NULLTEXT));
    }



