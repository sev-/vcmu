/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:26
*
*   Name            vcfflush.c  --  flush open file
*
*   Description     This function flushes a open file 
*
*   Return Value    Returns file pointer or NULL  if error
*                    
*
**/

#include <vcstdio.h>

COUNT vcfflush(fptr)
FILE *fptr;         /* File pointer of file to flush                */
    {
    return(fflush(fptr));
    }


