/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:42
*
*   Name            vcfldiput - put field by id
*                                   
*   Description     Put string into a field from a gettable by field id
*
*   Return Value    Returns pointer to field
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

TEXT *vcfldiput(tbl,id,val,flag)
GETTABLE *tbl;              /* Pointer to get table with field      */
COUNT id;                   /* Id of field to put                   */
TEXT *val;                  /* New value of field                   */
COUNT flag;                 /* Put in real or temp. and maybe update*/
    {                       /* ------------------------------------ */
    TEXT *retval = NULLTEXT;/* Return pointer to field              */
    COUNT inptype;          /* Used to calculate input type         */
    GETITEM *cur;           /* Node of selected field               */
    GETITEM *vcfldfnd();    /* Declare functions used               */
    VOID vctoreal();        /* Moves from temp location to real loc.*/
    cur = vcfldfnd(tbl,NULLTEXT,id,1);  /* Find node                */
    if(cur != (GETITEM *)0)             /* If found                 */
        {                               /*                          */
        if(flag & FLDLOCTEMP)           /* If temp location         */
            {                           /*                          */
            retval = cur->gtmpfld;      /* Assign temporary location*/
            blank(retval);              /* Blank field              */
            strncpy(retval,val,strlen(val));/* Move field not NULL  */
            }                           /*                          */
        if(flag & FLDLOCREAL)           /* If real location         */
            vctoreal(cur);              /* Save to real location    */
        if(flag & FLDLOCUPDATE)         /* If update requested      */
            {                           /*                          */
            inptype = (cur->gfldtyp >> 7) & 15; /* Calculate display*/
            if(datalight[inptype] != NULLFUNC)  /* If display func  */
                (*datalight[inptype])(cur);     /* Redisplay        */
            }                           /*                          */
        }                               /*                          */
    return(retval);                     /* Return field location    */
    }                                   /* ------------------------ */

