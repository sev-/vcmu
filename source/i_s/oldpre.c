/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:34
*
*   Name            oldpre.c  --  Old string pre-function
*
*   Description     This is the old string pre-function. It does not
*                   make a copy of the string for editing.
*
*   Return Value    Returns -1 if error and set vcerror
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT oldpre(gi)
GETITEM *gi;        /* Get item to copy                             */
   {
   TEXT *tmppic(),*vcalloc();
   COUNT gettype();
   COUNT strlen();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "strpre:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    gi->gtmpfld = gi->g_field;
    if(gi->g_picture != NULLTEXT)
        gi->gtmppic = gi->g_picture;
    else
        gi->gtmppic = tmppic(gi->gtmpfld,'x');
    gi->g_length = strlen(gi->gtmpfld);
    if( gi->gdispsiz == -1 )
        gi->gdispsiz = min(gi->g_length,strlen(gi->gtmppic));
    else
        gi->gdispsiz = min(gi->gdispsiz,gi->g_length);
    gi->gmaxwid = 0;
   return(0);
   }



