/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 8/31/90 at 21:51:51
*
*   Name            vcedtobu.c - to buffer
*                                   
*   Description     Move from edit buffer to original buffer
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtobuf(edbuf)
VCEDBUF *edbuf;             /* Edit buffer                          */
    {                       /* ------------------------------------ */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT template[10];      /* File template                        */
    TEXT *eptr;             /* End of line pointer for return char  */
    VCEDLINE *lptr;         /* Pointer to line to create            */
    FILE *tfptr,*vcfopen(); /* Temporary file pointer - for reading */
    TEXT *mktemp();         /* Declare functions used               */
    VCEDLINE *vcednline();  /*    "        "      "                 */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    strcpy(template,"edXXXXXX");
    if((tfptr = vcfopen(mktemp(template),VCF_RW)) == (FILE *)0)
        {                               /* Open file                */
        askmsg("Editor Message","Error opening temporary file",0);
        return(1);                      /* Tell them then exit      */
        }                               /*                          */
    cdbdp = edbuf->bffline;             /* Start at top             */
    if(cdbdp == (DBDP)0)                /* If no first line         */
        {                               /*                          */
        vcfclose(tfptr);                /* Close file               */
        return(1);                      /* and exit                 */
        }                               /*                          */
    lptr = vcedgline(edbuf,cdbdp);      /* Get first line           */
    while(lptr != (VCEDLINE *)0)        /* While more lines         */
        {                               /*                          */
        eptr = &lptr->ltext[0] + edbuf->bflinelen -1;/* Point to end*/
        fwrite(&lptr->ltext[0],sizeof(TEXT),lptr->lused,tfptr);
        if(*eptr == vcedval.hardret)    /* Assign hard return       */
            fwrite("\n",sizeof(TEXT),1,tfptr);  /* Write new line   */
        cdbdp = lptr->lnext;            /* Assign current dbase ptr */
        lptr = vcednline(edbuf,lptr);   /* Get next line of file    */
        }                               /*                          */
    return(0);                          /* Return no errors         */
    }                                   /* ------------------------ */

