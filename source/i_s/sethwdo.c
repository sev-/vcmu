/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:05
*
*   Name            sethwdo.c  --  Set help window variables
*
*   Description     Sets the global help window variables
*
*   Return Value    VOID
*
**/

#include <vcstdio.h>

VOID sethwdo(topr,topc,botr,botc,title,ctrl,depth,width,color)
COUNT topr,topc;    /* Top row and column for help window           */
COUNT botr,botc;    /* Bottom row and column for help window        */
TEXT *title;        /* Title for help Window                        */
COUNT ctrl;         /* Control value for help window                */
COUNT depth,width;  /* Depth and width of help window               */
COUNT color;        /* Color scheme for help window                 */
    {
    if(topr != -1)
        hlptrow = topr;
    if(topc != -1)
        hlptcol = topc;
    if(botr != -1)
        hlpbrow = botr;
    if(botc != -1)
        hlpbcol = botc;
    if(title != NULLTEXT)
        hlptitle = title;
    if(ctrl != -1)
        hlpctrl = ctrl;
    if(depth != -1)
        hlpdepth = depth;
    if(width != -1)
        hlpwidth = width;
    if(color != -1)
        hlpcolor = color;
    }


