/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:05
*
*   Name            fld2tmp.c  --  Refresh a gettable item
*
*   Description     This refreshs a item from the orginal location
*
*   Return Value    Return -1 if no gets or says in table
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT fld2tmp(gi,flag)
GETITEM *gi;        /* Pointer to get item to refresh               */
COUNT flag;         /* Flag 1 refresh screen                        */
    {
    COUNT datatype;
    VOID vcfree();
    VOID getsay();
    if(gi == (GETITEM *) 0)
        return(-1);
    if((gi->g_picture == NULLTEXT) || !(*gi->g_picture) )
        {
        vcfree(gi->gtmppic,vcdebug);
        gi->gtmppic = NULLTEXT;
        }
    if((gi->gtmpfld != NULLTEXT) && (gi->gtmpfld != gi->g_field))
        {
        vcfree(gi->gtmpfld,vcdebug);
        gi->gtmpfld = NULLTEXT;
        }
    datatype = (gi->gfldtyp >> 11) & 15;
    if(datapre[datatype] != NULLFUNC)
        {
        if((*datapre[datatype])(gi))
            return(-1);
        datatype = (gi->gfldtyp >> 7) & 15;
        if(datainit[datatype] != NULLFUNC)
            (*datainit[datatype])(gi);
        }
    else
        return(-1);
    if(flag)
        getsay(gi);
    return(0);
    }

