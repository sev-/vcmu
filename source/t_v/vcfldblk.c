/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:29
*
*   Name            vcfldblk.c - field blank
*                                   
*   Description     Blanks out the area that a field is located in.
*
*   Return Value    VOID
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID vcfldblk(gi)
GETITEM *gi;
    {                       /* ------------------------------------ */
    TEXT buf[255];
    if(gi != (GETITEM *)0)
        {
        empty(buf,255);
        buf[gi->gdispsiz+1] = '\0';
#ifdef WINDOW
        if((gi->gwptr != (WPTR) 0) && !override)
            wxatsay(gi->gwptr,gi->g_row,gi->g_col,buf,gi->gwptr->bg_at);
        else
#endif
            xatsay(gi->g_row,gi->g_col,buf,normattr);
        }
    }
