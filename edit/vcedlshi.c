/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:06
*
*   Name            vcedlshi.c - line shift
*                                   
*   Description     Used by vcedadjtab to shift the line
*
*   Return Value    VOID
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VOID vcedlshift(str,start,amount,length)
TEXT *str;                  /* Pointer to string to shift           */
COUNT start;                /* Starting location to shift           */
COUNT amount;               /* Number of characters to shift        */
COUNT length;               /* Length of string before shift        */
    {                       /* ------------------------------------ */
    TEXT *sour;             /* Source for memory move               */
    TEXT *dest;             /* Destination for memory move          */
    COUNT quant;            /* Quantity to move                     */
    dest = str + start;                 /* Find destination         */
    sour = dest + amount;               /* Find source              */
    quant = length - start - amount;    /* Calculate amount to move */
    vcmem(dest,sour,quant);             /* Move string              */
    str += length-1;                    /* Point to end of line     */
    while(amount--)                     /* While more to blank      */
        *(str--) = '\0';                /* Blank item               */
    }                                   /* ------------------------ */

