/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:04
*
*   Name            vcedload.c - load
*                                   
*   Description     Loads the editor buffer with file either from
*                   buffer or from file.  Also creates the buffer
*                   structure needed by vcedstart
*
*   Return Value    Returns pointer to editor buffer
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VCEDBUF *vcedload(fname,bloc,flag)
TEXT *fname;                /* Filename for file and buffer title   */
TEXT *bloc;                 /* Pointer to Buffer                    */
COUNT flag;                 /* Control Flags                        */
    {                       /* ------------------------------------ */
    VCEDBUF *newbuf;        /* Pointer to new buffer                */
    COUNT size;             /* Size of line with buffer and control */
    COUNT err = FALSE;      /* Error condition                      */
    DBP dbmsxopn();         /* Declare Functions Used               */
    TEXT *vcalloc();        /*    "        "      "                 */
    COUNT vcedfrmfil();     /*    "        "      "                 */
    COUNT vcedfrmbuf();     /*    "        "      "                 */
    newbuf = (VCEDBUF *)vcalloc(1,sizeof(*newbuf),vcdebug);/* Buffer*/
    newbuf->bflinelen = vcedval.linlen; /* Assign line len          */
    newbuf->bfbuffer = bloc;            /* Assign buffer            */
    newbuf->bfctrl = flag;              /* Assign control           */
    newbuf->bfnlines = 0l;              /* Reset line nums.         */
    newbuf->bffline = (DBDP)0;          /* Make first line empty    */
    newbuf->bfbline = (DBDP)0;          /* Set last line empty      */
    if(fname != NULLTEXT)               /* If there is file name    */
        {                               /*                          */
        newbuf->bfname = vcalloc(1,strlen(fname)+1,vcdebug);/* Alloc*/
        strcpy(newbuf->bfname,fname);   /* Assign File name         */
        }                               /*                          */
    else                                /*                          */
        newbuf->bfname = fname;         /* Assign NULL value        */
    newbuf->bfperm = 0;                 /* Assign permission        */
    size = sizeof(VCEDLINE) + newbuf->bflinelen;/* Calc line length */
    if((newbuf->bfdnum = dbmsxopn(-1,size,0,1,0,  /* Open database  */
            vcedval.pages,vcedval.slots)) == (DBP)0)/* for storage  */
        {                               /* If error                 */
        askmsg("Editor Message","Error opening internal File",0);
        return((VCEDBUF *)0);           /* Return NULL              */
        }                               /*                          */
    if(newbuf->bfctrl & VCEDFBUF)       /* Read from buffer?        */
        err = vcedfrmbuf(newbuf);       /*   read buffer            */
    else                                /* else                     */
        err = vcedfrmfil(newbuf);       /*   read file              */
    newbuf->bfchange = FALSE;           /* File not changed         */
    return(newbuf);                     /*   return buffer          */
    }                                   /* ------------------------ */

