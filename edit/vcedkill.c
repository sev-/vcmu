/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:01
*
*   Name            vcedkill.c - kill
*                                   
*   Description     Kills an editor buffer
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedkill(edbuf)
VCEDBUF *edbuf;             /* Edit buffer                          */
    {                       /* ------------------------------------ */
    dbmsxcls(edbuf->bfdnum);            /* Close database           */
    if(edbuf->bfname != NULLTEXT)       /* If buffer name           */
        vcfree(edbuf->bfname,vcdebug);  /* Free name                */
    vcfree(edbuf,vcdebug);              /* Free buffer              */
    return(0);                          /* Return everything O.K.   */
    }                                   /* ------------------------ */


