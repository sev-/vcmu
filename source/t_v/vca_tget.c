/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:15:59
*
*   Name            vca_tget.c  --  Terminal get
*
*   Description     This program gets the information from the memory
*                   terminal buffer and moves to the window memory
*                   area.
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID vca_tget(row,col,buffer,len)
COUNT row,col;      /* Row and Column to get information            */
PFAST TEXT *buffer; /* Buffer to put information                    */
COUNT len;          /* Len of buffer in words (two bytes)           */
    {
    COUNT twidth;
    FAST TEXT *sptr;
    VOID vcmem();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vca_tget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    twidth = vcterm.cols << 1;
    sptr = tscreen+(row*twidth)+(col << 1) ;
    vcmem(buffer,sptr,len << 1);
    }

#endif


