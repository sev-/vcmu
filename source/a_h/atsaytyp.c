/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:54
*
*   Name            atsaytyp.c  --  At say datatype
*
*   Description     Prints a data type value at given coordinates
*                   according to a picture if one is supplied.
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

VOID atsaytyp(row,col,numptr,pic,type,attr)
COUNT row,col;      /* Location to display field                    */
TEXT *numptr;       /* Pointer to number to convert                 */
TEXT *pic;          /* Pointer to picture to use for conversion     */
COUNT type;         /* Type of pointer FLDINT / FLDDOUBLE / ...     */
COUNT attr;         /* Attribute to use or -1 for default           */
    {
    GETITEM *gi;
    COUNT datatype;
    COUNT inptype;
    VOID vcfree();
    VOID getsay();
    TEXT *vcalloc();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "atsaytyp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    gi = (GETITEM *)vcalloc(1,sizeof(*gi),vcdebug);
    gi->g_field = (TEXT *)numptr;
    gi->g_picture = pic;
    gi->g_row = row;
    gi->g_col = col;
    gi->gdispsiz = -1;
    if(attr == -1)
        {
#ifdef WINDOW
        if(wdoctrl->wno_opn && !override)
            gi->gcurattr = gi->gattrag = gi->gattrnag = wdoctrl->wcurrent->say_at;
        else
#endif
            gi->gcurattr = gi->gattrag = gi->gattrnag = attrsay;
        }
    else
        gi->gcurattr = gi->gattrag = gi->gattrnag = attr;        
    datatype = (type >> 11) & 15;
    if( datapre[datatype] != NULLFUNC)
        {
        if((*datapre[datatype])(gi))
            return;
        gi->gfldtyp = gettype(gi->gtmppic);
        if(datainit[gi->gfldtyp] != NULLFUNC)
            (*datainit[gi->gfldtyp])(gi);
        gi->gfldtyp = gi->gfldtyp << 7;
        getsay(gi);
        if((pic == NULLTEXT) || !(*pic))
            vcfree(gi->gtmppic,vcdebug);
        if( gi->gtmpfld != NULLTEXT)
            vcfree(gi->gtmpfld,vcdebug);
        }
    vcfree(gi,vcdebug);
    }



