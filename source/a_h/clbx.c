/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:12
*
*   Name            clbx.c  --  Clear box
*
*   Description     Clears a box on the terminal.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef TERMINAL

VOID clbx(up,lf,lo,rt,attr)
COUNT up,lf;        /* Upper left location                          */
COUNT lo,rt;        /* Lower right location                         */
COUNT attr;         /* Attribute for new line                       */
    {
    FAST COUNT row,col;
    TEXT *blank,*ptr,*vcalloc();
    VOID terror();
    VOID vca_put();
    VOID vcfree();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "clbx:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((blank=vcalloc(vcterm.cols << 1,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror((TEXT *)"error allocating memory in clbox");
    ptr = blank;
    for(col=lf;col <= rt; col++)
        {
        *(ptr++)=SPACE;
        *(ptr++)=attr;
        }
    col=rt-lf+1;
    for(row=up;row <= lo;row++)
        vca_put(row,lf,blank,col);
    vcfree(blank,vcdebug);
    }

#endif


