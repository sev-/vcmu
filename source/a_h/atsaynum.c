/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:52
*
*   Name            atsaynum.c  --  At say number
*
*   Description     Prints a numeric value at given coordinates
*                   according to a picture if one is supplied.
*
*   Return Value    Returns True if full, False if not
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID atsaynum(row,col,numptr,pic,type)
COUNT row,col;      /* Location to display field                    */
TEXT *numptr;       /* Pointer to number to convert                 */
TEXT *pic;          /* Pointer to picture to use for conversion     */
COUNT type;         /* Type of numeric a pointer INTEGER / REAL     */
    {
    VOID atsaytyp();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atsaynum:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    atsaytyp(row,col,numptr,pic,type,-1);
    }



