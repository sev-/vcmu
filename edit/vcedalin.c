/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:14
*
*   Name            vcedalin.c - add line
*                                   
*   Description     Adds a line to the file
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

DBDP vcedaline(edbuf,tloc,cnt)
VCEDBUF *edbuf;             /* Edit buffer                          */
TEXT *tloc;                 /* Line of Text                         */
COUNT cnt;                  /* Number of characters used            */
    {                       /* ------------------------------------ */
    DBDP retval = (DBDP)0;  /* Return value                         */
    VCEDLINE *lptr;         /* Pointer to line to create            */
    VCEDLINE *pptr;         /* Pointer to previous line             */
    COUNT size;             /* Size of line structure               */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT *ptr;              /* Text pointer for return character    */
    VCEDLINE *vcedcline();  /* Declare functions used               */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    lptr = vcedcline(edbuf,&cdbdp);     /* Create new line          */
    lptr->lused = cnt;                  /* Number of used characters*/
    lptr->lsize = edbuf->bflinelen-1;   /* Length of allocated line */
    vcmem(lptr->ltext,tloc,edbuf->bflinelen); /* Copy text to loc   */
    cdbdp++;                            /* Store database ptr + 1   */
    retval = cdbdp;                     /* Assign return value      */
    if(edbuf->bffline == (DBDP)0)       /* If first line            */
        {                               /*                          */
        edbuf->bffline = cdbdp;         /* Set first line           */
        edbuf->bfbline = cdbdp;         /* Set last line            */
        lptr->lnext = (DBDP)0;          /* Set next line            */
        lptr->lprev = (DBDP)0;          /* Set previous line        */
        vcedrline(edbuf,lptr,cdbdp);    /* Save new line            */
        }                               /*                          */
    else                                /* Not first line           */
        {                               /*                          */
        lptr->lnext = (DBDP)0;          /* Set next line            */
        lptr->lprev = edbuf->bfbline;   /* Set previous line        */
        edbuf->bfbline = cdbdp;         /* Set last line            */
        vcedrline(edbuf,lptr,cdbdp);    /* Save new line            */
        if((pptr = vcedgline(edbuf,lptr->lprev)) == (VCEDLINE *)0)
            {                           /* Get previous line        */
            askmsg("Editor Message","Corrupt Memory in add line",0);    
            terror("Can not continue"); /* Database error           */
            }                           /*                          */
        pptr->lnext = edbuf->bfbline;   /* Set Previous line        */
        vcedrline(edbuf,pptr,lptr->lprev);  /* Save results         */
        }                               /*                          */
#ifdef VCEDFULL
    vcedunline(edbuf,(VCEDLINE *)0,lptr->lprev,     /* Tell undo    */
                edbuf->bfbline,(DBDP)0,VCEDUNINS);  /* about line   */
#endif
    edbuf->bfnlines++;                  /* Increment number of lines*/
    edbuf->bfchange = TRUE;             /* Flag buffer changed      */
    return(retval);                     /* Return database address  */
    }                                   /* ------------------------ */

