/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:34
*
*   Name            vcfldgo - go to a field
*                                   
*   Description     Sets up table to go to a field and location 
*
*   Return Value    Returns 0 for no error
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

GETITEM *vcfldgo(tbl,name,ofst)
GETTABLE *tbl;              /* Pointer to get table with field      */
TEXT *name;                 /* Name of field to goto                */
COUNT ofst;                 /* Offset of field starting at zero     */
    {                       /* ------------------------------------ */
    GETITEM *retval;        /* Return pointer to new node           */
    GETITEM *cur;           /* Node of selected field               */
    GETITEM *vcfldfnd();    /* Declare functions used               */
    cur = vcfldfnd(tbl,name,0,0);       /* Find node                */
    if(cur != (GETITEM *)0)             /* If found                 */
        {                               /*                          */
        if(tbl == (GETTABLE *)0)        /* If NULL table            */
            tbl = dftgettbl;            /* Assign default table     */
        tbl->tstartnode = cur;          /* Assign start node        */
        cur->gcndx = ofst;              /* Assign offset into field */
        }                               /*                          */
    return(cur);                        /* Return pointer to node   */
    }                                   /* ------------------------ */

