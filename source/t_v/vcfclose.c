/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:24
*
*   Name            vcfclose.c  --  close file
*
*   Description     This function closes open file
*
*   Return Value    Returns -1 if error
*                    
*
**/

#include <vcstdio.h>

COUNT vcfclose(fp)
FILE *fp;
    {
    return( fclose(fp) );
    }


