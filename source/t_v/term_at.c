/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:18:24
*
*   Name            term_at.c  --  Terminal at
*
*   Description     Address the terminal to row and column
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID term_at(row,col)
PFAST COUNT row,col;/* Row and column to move cursor                */
    {
    TEXT *gotopram;
    VOID dist_str();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "term_at:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (trow == row) && (tcol == col) )
        return;
    trow = row;
    tcol = col;
    switch(ttranslate)
        {
        case 0:
            gotopram = (TEXT *)&(vcterm.cursor.before);
            break;
        case 1:
            gotopram = vcterm.cm;
            break;
        case 2:
            gotopram = vcterm.cm;
            break;
        }
    dist_str((*gotofunc)(gotopram,col,row),0);
    }
#endif
