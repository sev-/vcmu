/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:54
*
*   Name            vcedilin.c - insert line
*                                   
*   Description     Low level insert line routine
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcediline(edbuf,prev,next,tloc,cnt)
VCEDBUF *edbuf;             /* Edit buffer                          */
DBDP prev;                  /* Previous line                        */
DBDP next;                  /* Next line                            */
TEXT *tloc;                 /* Line of Text                         */
COUNT cnt;                  /* Number of characters used            */
    {                       /* ------------------------------------ */
    VCEDLINE *lptr;         /* Pointer to line to create            */
    VCEDLINE *tptr;         /* Pointer to temporary line            */
    COUNT size;             /* Size of line structure               */
    DBDP cdbdp;             /* Current database data pointer        */
    DBDP tdbdp;             /* Temporary database data pointer      */
    TEXT *ptr;              /* Text pointer for return character    */
    VCEDLINE *vcedcline();  /* Declare functions used               */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    lptr = vcedcline(edbuf,&cdbdp);     /* Create new line          */
    lptr->lused = cnt;                  /* Number of used characters*/
    lptr->lsize = edbuf->bflinelen-1;   /* Length of allocated line */
    vcmem(lptr->ltext,tloc,edbuf->bflinelen); /* Copy text location */
    cdbdp++;                            /* Store database ptr + 1   */
    lptr->lnext = next;                 /* Set next line            */
    lptr->lprev = prev;                 /* Set previous line        */
#ifdef VCEDFULL
    vcedunline(edbuf,(VCEDLINE *)0,prev,cdbdp,next,VCEDUNINS);/*Undo*/
#endif
    vcedrline(edbuf,lptr,cdbdp);        /* Save new line            */
    if(prev == (DBDP)0)                 /* If first line            */
        edbuf->bffline = cdbdp;         /* Set first line           */
    else                                /* else not first line      */
        {                               /*                          */
        tdbdp = lptr->lprev;            /* Assign previous value    */
        if((tptr = vcedgline(edbuf,tdbdp)) == (VCEDLINE *)0)
            {                           /* Get line                 */
            askmsg("Editor Message","Corrupt Memory in Ins Line",0);
            terror("Can not continue"); /* Error in data base       */
            }                           /*                          */
        tptr->lnext = cdbdp;            /* Set Previous line        */
        vcedrline(edbuf,tptr,tdbdp);    /* Save changes             */
        }                               /*                          */
    if(next == (DBDP)0)                 /* If last line             */
        edbuf->bfbline = cdbdp;         /* Set last line            */
    else                                /* else not last line       */
        {                               /*                          */
        tdbdp = lptr->lnext;            /* Assign next value        */
        if((tptr = vcedgline(edbuf,tdbdp)) == (VCEDLINE *)0)
            {                           /* Get next line            */
            askmsg("Editor Message","Corrupt Memory in Ins Line",0);
            terror("Can not continue"); /* Error in data base       */
            }                           /*                          */
        tptr->lprev = cdbdp;            /* Set next line            */
        vcedrline(edbuf,tptr,tdbdp);    /* Save changes             */
        }                               /*                          */
    edbuf->bfnlines++;                  /* Increment number of lines*/
    edbuf->bfchange = TRUE;             /* Flag buffer changed      */
    }                                   /* ------------------------ */

