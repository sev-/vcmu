/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:30
*
*   Name            timeloc.c  --  sets time display location
*
*   Description     Sets location and attribute for the loop
*                   function timeloop().
*
*   Return Value    VOID
*                    
*
**/

#include <vcstdio.h>

extern COUNT vctimrow,vctimcol,vctimattr;
extern WPTR vctimwdo;

VOID timeloc(wptr,row,col,attr)
WPTR wptr;          /* Window to display time                       */
COUNT row,col;      /* Coordinates to display time                  */
COUNT attr;         /* Attribute to use when displaying time        */
   {
   vctimwdo = wptr;
   vctimrow = row;
   vctimcol = col;
   vctimattr= attr;
   }


