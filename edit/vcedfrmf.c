/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:48
*
*   Name            vcedfrmf.c - from file
*                                   
*   Description     Moves information from file to edit database
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>
#include <sys/types.h>
#include <sys/stat.h>

COUNT vcedfrmfil(edbuf)
VCEDBUF *edbuf;             /* Edit buffer                          */
    {                       /* ------------------------------------ */
    TEXT *mptr;             /* Temporary memory pointer             */
    COUNT len;              /* Length of the line read              */
    COUNT retchr;           /* Return character                     */
    struct stat info;       /* File information structure           */
    FILE *tfptr,*vcfopen(); /* Temporary file pointer - for reading */
    VOID vcedexptab();      /* Declare functions used               */
    if(stat(edbuf->bfname,&info))       /* Get permission           */
        return(1);                      /* Error getting status     */
    if((tfptr = vcfopen(edbuf->bfname,VCF_R)) == (FILE *)0)
        return(1);                      /* Error opening file       */
    edbuf->bfperm = info.st_mode;       /* Save status of file      */
    vcedempty(vcedfbuf,edbuf->bflinelen);/* Empty work buffer       */
    while(fgets(vcedfbuf,edbuf->bflinelen,tfptr) != (char *)0)
        {                               /*                          */
        len = strlen(vcedfbuf);         /* Get length of line       */
        mptr = vcedfbuf + len - 1;      /* Point to end of line     */
        if(*mptr == '\n')               /* If new line character    */
            {                           /*                          */
            len--;                      /* Subtract for new line    */
            *mptr = '\0';               /* Remove new line character*/
            retchr = vcedval.hardret;   /* Has a hard return        */
            }                           /*                          */
        else                            /*   or                     */
            retchr = vcedval.softret;   /* Has a soft return        */
        vcedexptab(edbuf,vcedfbuf,len,retchr);/* Expand & save      */
        vcedempty(vcedfbuf,edbuf->bflinelen);/* Empty work buffer   */
        }                               /*                          */
    vcfclose(tfptr);                    /* Close file               */
    return(0);                          /* Return no errors         */
    }

