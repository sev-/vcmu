/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:05
*
*   Name            vcalloc.c --  alloc memory
*
*   Description     Allocates memory using calloc     
*                   
*   Return Value    Returns pointer to allocated memory or
*                   NULL if error
*       
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "Allocation error: amount = %hd, size = %hd"
#else
#define SCANVALUE "Allocation error: amount = %d, size = %d"
#endif

TEXT *vcalloc(amount,size,calledby)
UCOUNT amount;      /* Quantity of objects to allocate              */
UCOUNT size;        /* Size of objects to allocate                  */
TEXT *calledby;     /* Program calling this function                */
    {
    TEXT *tmp,*calloc();
    TEXT buf[180];
    TEXT *strcpy();
    TEXT *strcat();
    VOID terror();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcalloc:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if( (tmp = calloc(amount,size)) == NULLTEXT)
        {
        sprintf(buf,SCANVALUE,amount,size);
        if(calledby != NULLTEXT)
            strcat(buf,calledby);
        terror(buf);
        }
    return(tmp);
    }


