/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:54
*
*   Name            vcedtofi.c - to file
*                                   
*   Description     Move from editor buffer back to original file
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedtofil(edbuf)
VCEDBUF *edbuf;             /* Edit buffer                          */
    {                       /* ------------------------------------ */
    DBDP cdbdp;             /* Current database data pointer        */
    TEXT template[20];      /* File template name                   */
    TEXT *eptr;             /* End of line pointer for return char  */
    TEXT *newbuf;           /* Pointer to buffer without tabspaces  */
    COUNT len;              /* Length of line without tabspaces     */
    VCEDLINE *lptr;         /* Pointer to line to create            */
    FILE *tfptr,*vcfopen(); /* Temporary file pointer - for reading */
    TEXT *mktemp();         /* Declare functions used               */
    TEXT *vceduntab();      /*    "        "      "                 */
    VCEDLINE *vcednline();  /*    "        "      "                 */
    VCEDLINE *vcedgline();  /*    "        "      "                 */
    cdbdp = edbuf->bffline;             /* Start at top             */
    if(cdbdp == (DBDP)0)                /* If no first line         */
        return(1);                      /* Exit                     */
    if(!vcfaccess(edbuf->bfname,4) &&   /* If file exists           */
        vcfaccess(edbuf->bfname,2))     /* And no write access      */
        {                               /*                          */
        askmsg("Editor Message","Cannot Write File",0); /* Inform   */
        return(1);                      /* Return                   */
        }                               /*                          */
    strcpy(template,"edXXXXXX");        /* Setup template           */
    if((tfptr = vcfopen(mktemp(template),VCF_W)) == (FILE *)0)
        {                               /* Open file                */
        askmsg("Editor Message","Error opening temporary file",0);
        return(1);                      /* Tell them then exit      */
        }                               /*                          */
    lptr = vcedgline(edbuf,cdbdp);      /* Get first line           */
    while(lptr != (VCEDLINE *)0)        /* While more lines         */
        {                               /*                          */
        eptr = &lptr->ltext[0] + edbuf->bflinelen -1;/* Point to end*/
        len = lptr->lused;              /* Assign current length    */
        newbuf = vceduntab(&lptr->ltext[0],&len); /* Remove tabsp   */
        fwrite(newbuf,sizeof(TEXT),len,tfptr);  /* Write string     */
        if(*eptr == vcedval.hardret)    /* Assign hard return       */
            fwrite("\n",sizeof(TEXT),1,tfptr);  /* Write new line   */
        cdbdp = lptr->lnext;            /* Assign current dbase ptr */
        lptr = vcednline(edbuf,lptr);   /* Get next line of file    */
        }                               /*                          */
    vcfflush(tfptr);                    /* Flush buffer             */
    vcfclose(tfptr);                    /* Close file               */
    if(!vcfaccess(edbuf->bfname,0))     /* If backup file exists    */
        vcferase(edbuf->bfname);        /* Erase backup file        */    
    vcfmove(template,edbuf->bfname);    /* Rename new file          */
    if(edbuf->bfperm)                   /* If old file              */
        chmod(edbuf->bfname,edbuf->bfperm); /* Set proper permission*/
    return(0);                          /* Return no errors         */
    }                                   /* ------------------------ */

vcferase(filnam)
TEXT *filnam;
    {
    unlink(filnam);
    }

vcfmove(oldname,newname)
TEXT *oldname;
TEXT *newname;
    {
#ifdef MSC
    rename(oldname,newname);
#endif
#ifdef UNIX
    TEXT wrkbuf[256];
    strcpy(wrkbuf,"mv ");
    strcat(wrkbuf,oldname);
    strcat(wrkbuf," ");
    strcat(wrkbuf,newname);
    system(wrkbuf);
#endif
    }

COUNT vcfaccess(filnam,mode)
TEXT *filnam;
COUNT mode;
    {
    return(access(filnam,mode));
    }
