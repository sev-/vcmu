/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:51
*
*   Name            atsayget.c  --  At location display and get string 
*
*   Description     This function displays a NULL terminated string
*                   at location row,col using default say attribute.
*                   Then it sets up an entry into a get table to input
*                   at row,col+strlen(sfld) using the default attributes. 
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

COUNT atsayget(row,col,sfld,gfld,pic)
COUNT row,col;      /* Location to display string                   */
TEXT *sfld;         /* String to display                            */
TEXT *gfld;         /* Pointer to location of input string          */
TEXT *pic;          /* Pointer to picture to use for input          */
    {
    FAST COUNT c;
    COUNT atget();
    VOID atsay();
    COUNT strlen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atsayget:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    atsay(row,col,sfld);
    c = col + strlen(sfld);
    return(atget(row,c,gfld,pic));
    }

