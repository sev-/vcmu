/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:19:08
*
*   Name            vca_get.c  --  Write to screen
*
*   Description     These are the function necessary to read 
*                   the screen.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vca_get(row,col,buffer,len)
PFAST COUNT row,col;/* Row and column to start                      */
PFAST COUNT len;    /* Length to get                                */
PFAST TEXT *buffer; /* Location to put buffer                       */
    {
#ifdef OS2
    USHORT bufsize;
#endif
#ifdef IBM
    COUNT offset;
    VOID vcpeek();
    VOID vctioget();
    VOID vca_tget();
    VOID terror();
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vca_get:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef IBM
    switch(vctio)
        {
        case 1 :                              /* Direct to screen  */
            offset = ((row * vcterm.cols) + col) * 2; 
            vcpeek(vcvram,offset,buffer,len*2);
            break;
        case 2 :                              /* Assembly language */
            vctioget(row,col,buffer,len);
            break;
#ifdef INTERUPT
        case 3 :                              /* Interrupt driven  */
            vca_iget(row,col,buffer,len);
            break;
#endif
#ifdef TERMINAL
        case 5 :                              /* Terminal driven  */
            vca_tget(row,col,buffer,len);
            break;
#endif
        default :
            terror("Invalid Video I/O Mode (vctio)");
        }
#endif
#ifdef TERMONLY 
    vca_tget(row,col,buffer,len);
#endif
#ifdef OS2
#ifdef TERMINAL
    switch(vctio)
        {
        case 5 :                              /* Terminal driven  */
            vca_tget(row,col,buffer,len);
            break;
        default :
            bufsize = (len << 1);
            VioReadCellStr(buffer,&bufsize,row,col,0);
            break;
        }
#else
    bufsize = (len << 1);
    VioReadCellStr(buffer,&bufsize,row,col,0);
#endif
#endif
    }


