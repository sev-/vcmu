/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:27
*
*   Name            vcpoke.c  --  Poke buf into memory
*
*   Description     Pokes a ranged of values to any segment and offset
*                   starting at buf and moving bytes number of bytes.
*                   used mostly for screen I/O.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef IBM

VOID vcpoke(seg,ofst,buf,bytes)
PFAST COUNT seg;    /* Segment of destination                       */
PFAST COUNT ofst;   /* Offset of destination                        */
TEXT buf[];         /* Location of source                           */
PFAST COUNT bytes;  /* Number of bytes to move                      */
    {
#ifdef CI
 COUNT n;
 for(n=0;n<bytes;n++)
  pokeb(ofst+n,seg,buf[n]);
#endif
#ifdef LC
 poke(seg,ofst,buf,bytes);
#endif
#ifdef MSC
    VOID movedata();
    VOID segread();
    COUNT model;
    struct  VCSR
        {
        unsigned int es;
        unsigned int cs;
        unsigned int ss;
        unsigned int ds;
        } sr;
    model = sizeof(buf);
    if( model == 4)
        movedata(VC_SEG(buf),VC_OFF(buf),seg,ofst,bytes);
    else
        {
        segread(&sr);
        movedata(sr.ds,buf,seg,ofst,bytes);
        }
#endif
#ifdef AZ
    unsigned segs[4];
        segread(segs);
    if(sizeof(TEXT *) == 4)
        movblock( buf,ofst,seg,bytes);
    else
        {
        movblock(buf,segs[2],ofst,seg,bytes);
        }
#endif
#ifdef MW
    if(sizeof(buf)==4)
        _copy(ofst,seg,VC_OFF(buf),VC_SEG(buf),bytes); 
    else
        _copy(ofst,seg,buf,dsreg(),bytes);
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcpoke:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    }

#endif


