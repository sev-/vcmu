/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:25
*
*   Name            vceddele.c - delete
*                                   
*   Description     Executes the delete key function
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vceddelete(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VCEDLINE *cline;        /* Pointer to line to delete            */
    VCEDLINE *vcedmline();  /* Declare functions used               */
    if(vced->edaline != (DBDP)0)        /* If anchor droped         */
        {                               /*                          */
#ifdef VCEDFULL
        vcedblkcp(vced,1,TRUE);         /* Delete to scrap 1        */
#endif
        return(0);                      /* Exit function            */
        }                               /*                          */
    else                                /*                          */
        {                               /*                          */
        if(vced->edcline != (DBDP)0)    /* If current line          */
            {                           /*                          */
            cline = vcedmline(vced->edbuffer,vced->edcline);/*Get ln*/
            vcedxdelete(vced,cline,vced->edcchar);  /* Delete key   */
            vcedrline(vced->edbuffer,cline,vced->edcline);/* Updt ln*/
            }                           /*                          */
        }                               /*                          */
    return(0);                          /* Return O.K.              */
    }                                   /* ------------------------ */    

