/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:21
*
*   Name            vcnumfix.c - Fix number at decimal places
*                                   
*   Description     Makes a string formated for a decimal
*
*   Return Value    VOID
*                                   
**/

#include <vcstdio.h>

TEXT *vcnumfix(des,org,siz,dec)
TEXT *des;                  /* Destination of formatted number      */
TEXT *org;                  /* Orginal number                       */
COUNT siz;                  /* Size of text string                  */
COUNT dec;                  /* Number of decimal places             */
    {                       /* ------------------------------------ */
    TEXT *dper,*oper;       /* Period location in field             */
    TEXT *dcur,*ocur;       /* Current loction in fields            */
    TEXT *strchr();         /* Declare functions used               */
    TEXT *ttrim();          /*    "        "      "                 */
    empty(des,siz+1);                   /* Blank destination string */
    if(dec)                             /* If there is a decimal    */
        {                               /*                          */
        dper = des + (siz - dec - 1);   /* Point to decimal         */
        *dper = (TEXT )vcdecimal;       /* Insert decimal           */
        dcur = dper - 1;                /* Start infront of decimal */
        }                               /*                          */
    else                                /*                          */
        {                               /*                          */
        dper = des + (siz - 1);         /* Point to end of field    */
        dcur = dper;                    /* Start at end of field    */
        }                               /*                          */
    if((oper = strchr(org,vcdecimal)) == NULLTEXT)  /* If no decimal*/
        {                               /*                          */
        oper = org + (strlen(ttrim(org)) -1 ); /* Point to end of field */
        ocur = oper;                    /* Set starting location    */
        }                               /*                          */
    else                                /*                          */
        ocur = oper - 1;                /* Start infront of decimal */
    while((dcur >= des) && (ocur >= org))/* While not at beginning  */
        *(dcur--) = *(ocur--);          /* Move data                */
    ocur = org + (strlen(org) -1);      /* Move to end of field     */
    dcur = des + (siz - 1);             /* Move to end of dest.     */
    oper++;                             /* Point to next loc        */
    dper++;                             /* Point to next des        */
    while(dec-- && (oper <= ocur) &&    /* While more to move       */
                (dper <= dcur))         /*                          */
        *(dper++) = *(oper++);          /* Move decimals            */
    return(des);                        /* Return the destination   */
    }                                   /* ------------------------ */
