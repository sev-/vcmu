/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:13
*
*   Name            vcltos.c  --  Long to string
*
*   Description     Converts long to a string with prec number of
*                   decimal places.
*
*   Return Value    Returns pointer to string
*
**/

#include <vcstdio.h>

TEXT *vcltos(str,num,prec)
TEXT *str;          /* Location to put converted number             */
long num;           /* Number to convert                            */
COUNT prec;         /* Number of decimal places                     */
    {
    TEXT buf[64];
    TEXT *vcnumfix();
    VOID empty();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcltos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    empty(buf,64);
    buf[48]=0;
    sprintf(buf,"%.16f",(float)num);
    return(vcnumfix(str,buf,strlen(str),prec));
   }


