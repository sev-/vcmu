/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:37
*
*   Name            initrl.c  --  Init right to left input
*
*   Description     This initializes right to left (numeric) input
*
*   Return Value    VOID
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

VOID initrl(gi)
GETITEM *gi;
    {
    TEXT buf[50];
    TEXT *ptr;
    COUNT rtolprec();
    TEXT *vcnumfix();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "initrl:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    gi->gmaxwid = rtolprec(gi->gtmppic);
    strcpy(buf,gi->gtmpfld);
    vcnumfix(gi->gtmpfld,buf,gi->g_length,gi->gmaxwid);
    if(gi->gmaxwid && (gi->gcontrol & FLDASSUME))
        gi->gmaxwid = 0;
    if(gi->gmaxwid)
        {
        gi->gendndx = gi->g_length - 1;
        gi->gbegndx = gi->gendndx - gi->gmaxwid + 1;
        ptr = gi->gtmpfld + gi->gbegndx;
        while(*ptr != '\0')
            {
            if(*ptr == ' ')
                *ptr = '0';
            ptr++;
            }
        }
    else
        {
        gi->gendndx = -1;
        gi->gbegndx = -1;
        }
    if(gi->gcontrol & FLDSPACE)
        {
        ptr = gi->gtmpfld;
        while(*ptr != '\0')
            {
            if((*ptr == '0') || 
               (*ptr == vcdecimal) || 
               (*ptr == ' ')        )
                ptr++;
            else
                break;
            }
        if(*ptr == '\0')
            {
            while(ptr != gi->gtmpfld)
                {
                if(*ptr == '0')
                    *ptr = ' ';
                ptr--;
                }
            }
        } 
    }


