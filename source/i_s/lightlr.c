/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:10
*
*   Name            lightlr.c  --  display left to right field 
*
*   Description     This function displays a NULL terminated string
*                   at the current location (vcrow,vccol) using
*                   default say attribute.
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS

#include <vcstdio.h>

VOID lightlr(gi)
GETITEM *gi;
    {
    VOID sayseg();
    TEXT *displfield;
    TEXT *fld,*loc;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "lightlr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(gi->gcontrol & FLDPASSWD)
        {
        blank(gi->gtmppic);
        fld = gi->gtmpfld;
        loc = gi->gtmppic;
        while((*fld != '\0') && (*loc != '\0'))
            {
            if(*fld != ' ')
                *loc = '*';
            fld++;
            loc++;
            }
        displfield = gi->gtmppic;
        }
    else
        displfield = gi->gtmpfld;
    sayseg(gi->gwptr,gi->g_row,gi->g_col,displfield,gi->gstart,
              gi->gdispsiz,gi->gcurattr);
    if(gi->gcontrol & FLDPASSWD)
        strcpy(gi->gtmppic,gi->g_picture);
    }

