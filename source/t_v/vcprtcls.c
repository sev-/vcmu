/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:32
*
*   Name            vcprtcls.c  --  close printer file
*
*   Description     This function closes the printer for use by
*                   vcprtchr and vcprtstr
*
*   Return Value    Returns 0 if no error
*                    
*
**/

#include <vcstdio.h>

COUNT vcprtcls()
    {
    COUNT vcfclose();
    return(vcfclose(prthandle));
    }


