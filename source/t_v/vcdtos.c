/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:19:03
*
*   Name            vcdtos.c  --  Double to string
*
*   Description     Converts a double to a string using prec as the
*                   the number of places to the right of the decimal
*                   to display.
*
*   Return Value    Returns pointer to string
*
**/

#include <vcstdio.h>

TEXT *vcdtos(str,num,prec)
TEXT *str;          /* Location to put converted number             */
double num;         /* Number to convert                            */
COUNT prec;         /* Number of decimal places                     */
    {
    TEXT buf[64];
    TEXT *vcnumfix();
    VOID empty();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vcdtos:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    empty(buf,64);
    buf[48]=0;
    sprintf(buf,"%.9lf",num);
    return(vcnumfix(str,buf,strlen(str),prec));
    }


