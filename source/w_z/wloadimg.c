/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:44
*
*   Name            wloadimg.c - load image
*                                   
*   Description     Loads current window image from a file
*
*   Return Value    Returns pointer to window image
*                                   
**/

#include <vcstdio.h>

#ifdef TERMINAL

TEXT *wloadimg(fname)
TEXT *fname;                /* Name of file to save image to        */
    {                       /* ------------------------------------ */
    TEXT *retval = NULLTEXT;/* Pointer to return screen location    */
    COUNT scrsize;          /* Size of screen                       */
    FILE *vcfopen(),*fp;    /* File pointer to open file with       */
    COUNT vcfclose();       /* Declare functions used               */
    VOID rd_scrn();         /*    "        "      "                 */
    if((fp = vcfopen(fname,VCF_RB)) == (FILE *)0)   /* If error     */
        return(retval);                 /* Return Error             */
    scrsize = (vcterm.rows*vcterm.cols) << 1;   /* Calc screen size */
    if(fread(tscreen,sizeof(TEXT),scrsize,fp) == scrsize)
        retval = wscreen;               /* Assign screen location   */
    wrd_scrn();                         /* Read screen to back loc. */
    wstack((WPTR)0);                    /* Make sure screen correct */
    fclose(fp);                         /* Close file               */
    return(retval);                     /* Return screen location   */
    }                                   /* ------------------------ */

#endif
