/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:34
*
*   Name            vcprtfls.c  --  flush printer file
*
*   Description     This function flushes the printer file
*
*   Return Value    Return 0 if no error    
*                    
*
**/

#include <vcstdio.h>

COUNT vcprtfls()
    {
    COUNT vcfflush();
    return(vcfflush(prthandle));
    }


