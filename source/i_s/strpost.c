/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:37
*
*   Name            strpost.c  --  Standard string post-function
*
*   Description     This is the standard string post function. Copies
*                   the edit copy of the field to the real location
*                   of the field.
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT strpost(gi)
GETITEM *gi;        /* Get item to act upon                         */
    {
    TEXT *pic,*fld,*ptr;
    TEXT *ttrim();
    TEXT *strcpy();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "strpost:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(gi->gcontrol & FLDNOALLOC)
        return(0);
    if(gi->gcontrol & FLDNOPIC)
        {
        pic = gi->gtmppic;
        fld = gi->gtmpfld;
        ptr = gi->g_field;
        while((*pic != '\0') && (*fld != '\0'))
            {
            if(evalpic(*pic))
                {
                *ptr = *fld;
                ptr++;
                }
            fld++;
            pic++;
            }
        *ptr = '\0';
        }
    else
        {
        if(gi->gcontrol & FLDTRIM)
            strcpy(gi->g_field,ttrim(gi->gtmpfld));
        else
            strcpy(gi->g_field,gi->gtmpfld);
        }
    return(0);
    }


