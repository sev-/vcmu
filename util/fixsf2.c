/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .2 on 8/31/90 at 23:24:42
*
*   Name            fixsf2 -- fix the shift f2 key        
*                                   
*   Description     This program is only for XENIXV on PC or
*                   compatibles and only for the console. It 
*                   redefines shift-f2 from <ESC>[Z to ^A[Z             
*
*   Return Value    None
*                                   
**/

#include <stdio.h>
#include <sys/keyboard.h>

main()
    {
    strmap_t strtab;
    if(ioctl(0,GIO_STRMAP,strtab) == -1)
        {
        printf("error reading");
	exit(1);
        }
    strtab[13*4] = (char) 1;
    if(ioctl(0,PIO_STRMAP,strtab) == -1)
        {
        printf("error writing");
	exit(1);
        }
    }
