/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:38
*
*   Name            strpre.c  --  Standard string pre-function
*
*   Description     This is the standard string pre-function. Is 
*                   call if a string input.
*
*   Return Value    Returns -1 if error and set vcerror
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>
           
COUNT strpre(gi)
GETITEM *gi;        /* Get item to copy                             */
    {
    COUNT fldsize = 0;
    COUNT picsize = 0;
    COUNT newsize = 0;
    TEXT *tmppic(),*vcalloc();
    COUNT strlen();
    TEXT *strncpy();
    COUNT gettype();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "strpre:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(gi->g_picture != NULLTEXT)
        picsize = strlen(gi->g_picture);
    if(gi->g_field != NULLTEXT)
        fldsize = strlen(gi->g_field);
    newsize = max(fldsize,picsize);
    newsize = max(newsize,gi->gdispsiz);
    if(gi->gcontrol & FLDNOALLOC)
        gi->gtmpfld = gi->g_field;
    else
        {
        if( (gi->gtmpfld = vcalloc(1,newsize+1,vcdebug)) == NULLTEXT)
            {
            vcerror= NOSTRMEM;  
            return(-1);
            }
        empty(gi->gtmpfld,newsize+1);
        if(fldsize)
            strncpy(gi->gtmpfld,gi->g_field,fldsize);
        }
    if(picsize < newsize)
        {
        gi->gtmppic = tmppic(gi->gtmpfld,'x');
        if(picsize)
            strncpy(gi->gtmppic,gi->g_picture,picsize);
        }
    else
        gi->gtmppic = gi->g_picture;
    gi->g_length = newsize;
    if( gi->gdispsiz <= 0 )
        gi->gdispsiz = newsize;
    gi->gmaxwid = 0;
    return(0);
    }



