/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:15:57
*
*   Name            vca_put.c  --  Write to screen
*
*   Description     These are the function necessary to write 
*                   to the screen.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vca_put(row,col,buffer,len)
PFAST COUNT row,col;/* Row and column to put buffer                 */
PFAST COUNT len;    /* Length of buffer                             */
PFAST TEXT *buffer; /* Buffer to send of the screen                 */
    {
#ifdef OS2
    USHORT bufsize;
#endif
#ifdef IBM
    COUNT offset;
    VOID vcpoke();
    VOID vctioput();
    VOID vca_tput();
    VOID terror();
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vca_put:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef IBM
    switch(vctio)
        {
        case 1 :                              /* Direct to screen  */
            offset = ((row * vcterm.cols) + col) * 2;
            vcpoke(vcvram,offset,buffer,len*2);
            break;
        case 2 :                              /* Assembly language */
            vctioput(row,col,buffer,len);
            break;
#ifdef INTERUPT
        case 3 :                              /* Interupt driven  */
            vca_iput(row,col,buffer,len);
            break;
#endif
#ifdef TERMINAL
        case 5 :                              /* Terminal driven  */
            vca_tput(row,col,buffer,len);
            break;
#endif
        default :
            terror("Invalid Video I/O Mode (vctio)");
        }
#endif
#ifdef TERMONLY
    vca_tput(row,col,buffer,len);
#endif
#ifdef OS2
#ifdef TERMINAL
    switch(vctio)
        {
        case 5 :                              /* Terminal driven  */
            vca_tput(row,col,buffer,len);
            break;
        default :
            bufsize = len * 2;
            VioWrtCellStr(buffer,bufsize,row,col,0);
            break;
        }
#else
    bufsize = len << 1;
    VioWrtCellStr(buffer,bufsize,row,col,0);
#endif
#endif
    }


