/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:19
*
*   Name            mapnum.c  --  Build map for numeric input
*
*   synopsis        mapnum(in,pic,decireal,deciscrn,hassign);
*                   TEXT *in;  field to map
*                   TEXT *pic; picture to use
*                   COUNT *decireal;
*                   COUNT *deciscrn;
*
*   Description     This function maps a field with picture
*
*   Return Value    Returns True is decimal point found
*
**/

#include <vcstdio.h>

COUNT mapnum(in,pic,decireal,deciscrn,hassign)
TEXT *in;           /* Field to map                                 */
TEXT *pic;          /* Picture to use                               */
COUNT *decireal;    /*                                              */
COUNT *deciscrn;    /*                                              */
COUNT *hassign;     /*                                              */
    {
    COUNT n;
    COUNT havdeci;
    COUNT v;        /* the value field index                        */
    COUNT p;        /* the picture index                            */
    COUNT strlen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "mapnum:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    for(v=0;in[v] && in[v]!='.';v++);    /* v = deci locn in fld        */

    for(p=0;pic[p] && pic[p]!='.';p++);  /* p = deci locn in pic        */

    if(pic[p])                  /* if have decimal in picture   */
        havdeci=1;
    else
        havdeci=0;

    *decireal = v;
    if(in[*decireal] != '\0')
        *deciscrn = p;
    else
        *deciscrn = p;

    if(!havdeci && *deciscrn==0 )
        *deciscrn=strlen(pic);

    for(n=0;pic[n] && pic[n]!='-';n++);
    if(pic[n]=='-')
        *hassign=1;
    else
        *hassign=0;

    if(!(*hassign))
        {
        for(n=0;in[n] && in[n]!='-';n++);
        if(in[n]=='-')
            in[n]=' ';
        }

    return(havdeci);
    }


