/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:35
*
*   Name            vcprtopn.c  --  open printer file
*
*   Description     This function opens the printer for use by
*                   vcprtchr and vcprtstr
*
*   Return Value    Returns the previous prthandle    
*                    
*
**/

#include <vcstdio.h>

#ifdef VMS
#include <file.h>
#endif

FILE *vcprtopn(printer)
TEXT *printer;
    {
    FILE *retval;
    FILE *vcfopen();
    retval = prthandle;
    if(printer == NULLTEXT)
        printer = (TEXT *)PRINTDEV;
    if((prthandle = vcfopen(printer,VCF_W)) == (FILE *)0)
        prthandle = retval;
    return(retval);
    }


