/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:48
*
*   Name            vcfopen.c  --  file open
*
*   Description     This function opens a file for reading and writing
*                   for portability use defines for mode paramiters
*
*   Return Value    Returns file pointer or NULL  if error
*                    
*
**/

#include <vcstdio.h>

FILE *vcfopen(nam,mode)
TEXT *nam;          /* Name of file to open                         */
TEXT *mode;         /* Mode for open                                */
    {
    FILE *fopen();
    return(fopen(nam,mode));
    }


