/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:39
*
*   Name            prnnum.c  --  Display a formatted number
*
*   Description     This function display the field at the desired
*                   location using the selected picture and attr.
*                   if during formatting the program needs more room
*                   or is full the function returns a 1.
*
*   Return Value    Returns True if full, False if not
*
**/

#include <vcstdio.h>

COUNT prnnum(row,col,fld,pic,attr)
COUNT row,col;      /* Location to display field                    */
TEXT *fld;          /* Pointer to field to display                  */
TEXT *pic;          /* Pointer to picture for field                 */
COUNT attr;         /* Attribute to use                             */
    {
    COUNT full;
    TEXT buf[50];
    COUNT sprtnum();
    VOID xatsay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "prnnum:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    full=sprtnum(buf,fld,pic);
    xatsay(row,col,buf,attr);
    return(full);
    }


