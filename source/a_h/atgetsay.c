/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:48
*
*   Name            atgetsay.c  --  Place an Display entry in que
*
*   Description     This function sets up default values and calls
*                   xatgetsay.  Sets up an entry into the say table.
*
*   Return Value    Returns -1 if error
*
**/

#include <vcstdio.h>

COUNT atgetsay(row,col,fld,attr)
COUNT row,col;      /* Row and column for display                   */
COUNT attr;         /* Attribute for display                        */
TEXT *fld;          /* Pointer to field to display                  */
    {
    COUNT xatgetsay();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atgetsay:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    return(xatgetsay(NULLTEXT,NULLTEXT,row,col,fld,attr,0,0,GETSAY));
    }


