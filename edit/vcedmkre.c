/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:07
*
*   Name            vcedmkre.c - make real
*                                   
*   Description     Makes the current line real by adding enough
*                   lines to editor buffer
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedmkreal(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    LONG start;             /* Starting address                     */
    TEXT *ptr;              /* Temporary pointer                    */
    DBDP cdbdp;             /* Current database data pointer        */
    DBDP vcedaline();       /* Declare functions used               */
    vcedempty(vcedfbuf,vced->edbuffer->bflinelen); /* Empty line    */
    ptr = vcedfbuf + vced->edbuffer->bflinelen -1;  /* Calc offset  */
    *ptr = vcedval.hardret;             /* Give lines hard returns  */
    start = vced->edbuffer->bfnlines;   /* Start with the current no*/
    while(start <= vced->edcrow)        /* While more lines to add  */
        {                               /*                          */
        cdbdp = vcedaline(vced->edbuffer,vcedfbuf,0);/* Add to db   */
        start++;                        /* Increment count          */
        if(start == (vced->edtrow+1))   /* If happen to be top row  */
            vced->edtline = cdbdp;      /* Assign top row           */
        }                               /*                          */
    vced->edcline = cdbdp;              /* Assign current data ptr  */
    }                                   /* ------------------------ */

