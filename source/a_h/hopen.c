/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:45
*
*   Name            hopen.c  --  opens help file and index
*
*   Description     Opens the help file and the index file and calls
*                   hload to load index.
*
*   Return Value    Returns
*                    0 if everything ok
*                   -1 if help file cannot be opened
*                   -2 if index file cannot be opened
*                   -3 if index file cannot be closed
*
*
**/

#include <vcstdio.h>

COUNT hopen(msgfil,ndxfil)
TEXT *msgfil;       /* Help file                                    */
TEXT *ndxfil;       /* Index to help file                           */
    {
    FILE *ifp,*vcfopen();
    COUNT hload();
    /* hlpfil is global help file pointer defined as FILE *hlpfil;  */
#ifdef VCDEBUG
    vcdebug = (TEXT *) "hopen:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (hlpfil=vcfopen(msgfil,VCF_R)) == (FILE *)0)
        return(-1);
    if( (ifp=vcfopen(ndxfil,VCF_RB)) == (FILE *)0)
        return(-2);
    hload(ifp);
    if( fclose(ifp))
        return(-3);
    return(0);
    }



