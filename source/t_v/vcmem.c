/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:15
*
*   Name            vcmem.c  --  Memory move
*
*   Description     If available uses block move by processor to
*                   move a block of memory.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID vcmem(end,start,len)
PFAST TEXT *end;    /* Pointer to destination                       */
PFAST TEXT *start;  /* Pointer to orgination                        */
UCOUNT len;         /* Number of bytes to move                      */
    {
#ifdef UNIX
#ifdef MEMCPY
    TEXT *memcpy();
#else
    COUNT cnt;
#endif
#endif
#ifdef VMS
    COUNT cnt;
#endif
#ifdef PRIMOS
    COUNT cnt;
#endif
#ifdef MSC
    TEXT *memmove();
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcmem:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
#ifdef CI
    movmem(start,end,len);
#endif
#ifdef AZ
    movmem(start,end,len);
#endif
#ifdef LC
    movmem(start,end,len);
#endif
#ifdef MSC
    memmove(end,start,len);
#endif
#ifdef MW
    if(sizeof(end)==4)
        _copy(VC_OFF(end),VC_SEG(end),VC_OFF(start),VC_SEG(start),len); 
    else
        _copy(end,dsreg(),start,dsreg(),len);
#endif
#ifdef UNIX
#ifdef MEMCPY
    memcpy(end,start,len);
#else
    for(cnt=0;cnt < len;cnt++)
        *(end++) = *(start++);
#endif
#endif
#ifdef VMS
#ifdef MEMCPY
    memcpy(end,start,len);
#else
    for(cnt=0;cnt < len;cnt++)
        *(end++) = *(start++);
#endif
#endif
#ifdef PRIMOS
#ifdef MEMCPY
    memcpy(end,start,len);
#else
    for(cnt=0;cnt < len;cnt++)
        *(end++) = *(start++);
#endif
#endif
    }
