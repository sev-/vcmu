/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:51:19
*
*   Name            vcedopen.c - editor open
*                                   
*   Description     Executes an editor open command 
*
*   Return Value    Returns VCED buffer used by vcedit()
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

VCED *vcedopen(urow,ucol,lrow,lcol,title,wctrl,ectrl,edbuf,rmar,lmar,wp)
COUNT urow,ucol;            /* Upper row and column                 */
COUNT lrow,lcol;            /* Lower row and column                 */
TEXT *title;                /* Pointer to title for window          */
COUNT wctrl;                /* Control value for window             */
COUNT ectrl;                /* Control value for editor             */
VCEDBUF *edbuf;             /* Edit buffer                          */
COUNT rmar,lmar;            /* Right / Left margin                  */
WPTR wp;                    /* Optional pointer to status window    */
    {                       /* ------------------------------------ */
    VCED *newed;            /* Pointer to new buffer                */
    TEXT *vcalloc();        /* Declare functions used               */
    VOID vcedwopen();       /*    "        "      "                 */
    COUNT vcedptrbuf();     /*    "        "      "                 */
    newed = (VCED *)vcalloc(1,sizeof(*newed),vcdebug); /* Get struct*/
    if(rmar == -1)                      /* If right margin -1       */
        newed->edrmar = vcedval.dftrmar;/*   use default            */
    else                                /* else                     */
        newed->edrmar = rmar;           /*   use value passed       */
    if(lmar == -1)                      /* If left margin -1        */
        newed->edlmar = vcedval.dftlmar;/*   use default            */
    else                                /* else                     */
        newed->edlmar = lmar;           /*   use value passed       */
    newed->edurow = urow;               /* Assign upper row         */
    newed->educol = ucol;               /* Assign upper column      */
    newed->edlrow = lrow;               /* Assign lower row         */
    newed->edlcol = lcol;               /* Assign lower column      */
    if(wctrl == -1)                     /* If window control == -1  */
        wctrl = wdoctrl->wstdctrl;      /*   use default value      */
    wctrl |= NOAUTO;                    /* Do not auto move         */
    newed->edctrl = wctrl;              /* Assign window control    */
    newed->edtitle = title;             /* Assign title             */
    newed->edtline = edbuf->bffline;    /* Start with first line    */
    newed->edcline = edbuf->bffline;    /* Make first line current  */
    newed->edcchar = 0;                 /* Make first character cur.*/
    newed->edtrow = 0l;                 /* Make top row first line  */
    newed->edcrow = 0l;                 /* Current row first line   */
    newed->edmode = ectrl;              /* Assign editor control    */
    newed->edbuffer = edbuf;            /* Assign buffer to edit    */
    newed->edswptr = wp;                /* Assign status window     */
    if(!(newed->edmode & VCEDNOSHOW))   /* If not show later        */
        {                               /*                          */
        vcedwopen(newed);               /* Open window              */ 
        vcedprtbuf(newed);              /* Display buffer           */
        }                               /*                          */
    return(newed);                      /* Return new structure     */
    }                                   /* ------------------------ */

