/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:24
*
*   Name            wsaveimg.c - save image
*                                   
*   Description     Saves current window image to a file
*
*   Return Value    Returns pointer to window image
*                                   
**/

#include <vcstdio.h>

#ifdef TERMINAL

TEXT *wsaveimg(fname)
TEXT *fname;                /* Name of file to save image to        */
    {                       /* ------------------------------------ */
    TEXT *retval = NULLTEXT;/* Pointer to return screen location    */
    COUNT scrsize;          /* Size of screen                       */
    FILE *vcfopen(),*fp;    /* File pointer to open file with       */
    COUNT vcfclose();       /* Declare functions used               */
    if((fp = vcfopen(fname,VCF_WB)) == (FILE *)0)   /* If error     */
        return(retval);                 /* Return Error             */
    wstack((WPTR)0);                    /* Make sure screen correct */
    scrsize = (vcterm.rows*vcterm.cols) << 1;   /* Calc screen size */
    if(fwrite(wscreen,sizeof(TEXT),scrsize,fp) == scrsize)
        retval = wscreen;               /* Assign screen location   */
    fclose(fp);                         /* Close file               */
    return(retval);                     /* Return screen location   */
    }                                   /* ------------------------ */

#endif
