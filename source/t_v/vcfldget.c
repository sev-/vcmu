/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:32
*
*   Name            vcfldget - get field by name
*                                   
*   Description     Gets a field from a gettable by field name
*
*   Return Value    Returns pointer to field
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

TEXT *vcfldget(tbl,name,flag)
GETTABLE *tbl;              /* Pointer to get table with field      */
TEXT *name;                 /* Name of field to get                 */
COUNT flag;                 /* Get temporary or real location       */
    {                       /* ------------------------------------ */
    TEXT *retval = NULLTEXT;/* Return pointer to field              */
    GETITEM *cur;           /* Node of selected field               */
    GETITEM *vcfldfnd();    /* Declare functions used               */
    cur = vcfldfnd(tbl,name,0,0);       /* Find node                */
    if(cur != (GETITEM *)0)             /* If found                 */
        {                               /*                          */
        if(flag & FLDLOCREAL)           /* If real location wanted  */
            retval = cur->g_field;      /* Assign real location     */
        else                            /*                          */
            retval = cur->gtmpfld;      /* Assign temporary location*/
        }                               /*                          */
    return(retval);                     /* Return field             */
    }                                   /* ------------------------ */
