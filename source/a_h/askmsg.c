/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:03:40
*
*   Name            askmsg -- ask message
*                                   
*   Description     Stop and ask the operator a question or display
*                   message      
*
*   Return Value    Returns answer if question
*
**/

#include <vcstdio.h>

static TEXT *askwstyle = NULLTEXT;
static COUNT asktrow = 18;
static COUNT asktcol = 20;
static COUNT askbrow = 20;
static COUNT askbcol = 60;
static COUNT askcolor = 0;
static COUNT askctrl = BORDER;

COUNT askmsg(tit,msg,flag)
TEXT *tit;          /* Title for Window                             */
TEXT *msg;          /* Message to display                           */
COUNT flag;         /* Control flag: 0=wait:1=(def=Y):2=(def=N)     */
    {
    TEXT ans[2];
    COUNT col,retval = TRUE;
    VOID terror();
    COUNT strlen();
    VOID atsay();
    COUNT getone();
    VOID at();
    COUNT accept();
    COUNT strcmp();
    COUNT wclose();
    TEXT *strcpy();
    COUNT strlen();
    WPTR swptr,wxxopen();
    WPTR wstyleopen();
    COUNT ctrl = askctrl | ACTIVE;
    if(flag)
        ctrl |= CURSOR;
    if(askwstyle == NULLTEXT)
        swptr = wxxopen(asktrow,asktcol,askbrow,askbcol,tit,
                    ctrl,0,0,askcolor,' ');
    else
        swptr = wstyleopen(askwstyle,asktrow,asktcol,askbrow,askbcol,tit);
    if(swptr == (WPTR) 0)
        terror((TEXT *)"Error opening message window");
    col = max((swptr->width-strlen(msg)-2)/2,0);
    switch(flag)
        {
        case 0:
            atsay(0,col,msg);
            getone();
            break;
        case 'y':
        case 'Y':
            strcpy(ans,"Y");
            atsay(0,col,msg);
            at(0,col+strlen(msg));
            accept(ans,(TEXT *)"Y");
            if(strcmp(ans,"Y"))
                retval = FALSE;
            break;
        case 'n':
        case 'N':
            strcpy(ans,"N");
            retval = FALSE;
            atsay(0,col,msg);
            at(0,col+strlen(msg));
            accept(ans,(TEXT *)"Y");
            if(strcmp(ans,"N"))
                retval = TRUE;
            break;
        }
    wclose(swptr);
    return(retval);
    }

VOID setaskmsg(topr,topc,botr,botc,color,ctrl,style)
COUNT topr,topc;    /* Top row and column for askmsg window         */
COUNT botr,botc;    /* Bottom row and column for askmsg window      */
COUNT color;        /* Color scheme for askmsg window               */
COUNT ctrl;         /* Control byte for window                      */
TEXT *style;        /* Pointer to window style                      */
    {
    if(topr != -1)
        asktrow = topr;
    if(topc != -1)
        asktcol = topc;
    if(botr != -1)
        askbrow = botr;
    if(botc != -1)
        askbcol = botc;
    if(color != -1)
        askcolor = color;
    if(ctrl != -1)
        askctrl = ctrl;
    if(style != NULLTEXT)
        askwstyle = style;
    }
