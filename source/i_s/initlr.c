/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:36
*
*   Name            initlr.c  --  Initialize left to right input
*
*   Description     This init the left to right input
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VOID initlr(gi)
GETITEM *gi;
    {
    TEXT *pic;
    TEXT *fld;
    TEXT *ptr;
    TEXT *ttrim();
    COUNT evalpic();
    TEXT *vcalloc();
    VOID blank();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "initlr:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    mapstr(gi);
    if(gi->gcontrol & FLDPASSWD)
        {
        if(gi->g_picture == gi->gtmppic)
            {
            if(gi->g_picture != NULLTEXT)
                {
                gi->gtmppic = vcalloc(sizeof(TEXT),
                                strlen(gi->g_picture)+1,vcdebug);
                strcpy(gi->gtmppic,gi->g_picture);
                }
            else
                {
                gi->g_picture = vcalloc(sizeof(TEXT),
                                strlen(gi->gtmppic)+1,vcdebug);
                strcpy(gi->g_picture,gi->gtmppic);
                }
            }
        }
    pic = gi->gtmppic;
    fld = gi->gtmpfld;
    if(gi->gcontrol & FLDNOPIC)
        {
        ptr = ttrim(gi->gtmpfld);
        blank(gi->gtmpfld);
        while((*pic != '\0') && (*ptr != '\0') && (*fld != '\0'))
            {
            if(evalpic(*pic))
                {
                *fld = *ptr;
                ptr++;
                }
            else
                *fld = *pic;
            fld++;
            pic++;
            }
        }
    else
        {
        while((*pic != '\0') && (*fld != '\0'))
            {
            if(!evalpic(*pic))
                *fld = *pic;
            fld++;
            pic++;
            }
        }
    }


