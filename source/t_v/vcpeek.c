/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:26
*
*   Name            vcpeek.c  --  Read a value from memory
*
*   Description     This function reads an address from any location
*                   (segment and offset) to a buffer. This is used
*                   for direct screen I/O.
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

#ifdef IBM

VOID vcpeek(seg,ofst,buf,bytes)
PFAST COUNT seg;    /* Segment of source                            */
PFAST COUNT ofst;   /* Offset of source                             */
TEXT buf[];         /* Location to put source                       */
PFAST COUNT bytes;  /* Number of bytes to get                       */
    {
#ifdef CI
 FAST COUNT n,b;
 for(n=0;n<bytes;n++)
  buf[n]=peek(ofst+n,seg);
#endif
#ifdef LC
 peek(seg,ofst,buf,bytes);
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
    if(model == 4)
        {
        movedata(seg,ofst,VC_SEG(buf),VC_OFF(buf),bytes);
        }
    else
        {
        segread(&sr);
        movedata(seg,ofst,sr.ds,buf,bytes);
        }
#endif
#ifdef AZ
    unsigned segs[4];
        segread(segs);
    if(sizeof(TEXT *) == 4)
        movblock( ofst,seg,buf,bytes);
    else
        {
        movblock(ofst,seg,buf,segs[2],bytes);
        }
#endif
#ifdef MW
    if(sizeof(buf)==4)
        _copy(VC_OFF(buf),VC_SEG(buf),ofst,seg,bytes); 
    else
        _copy(buf,dsreg(),ofst,seg,bytes);
#endif
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcpeek:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    }

#endif


