/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:24
*
*   Name            startstyle - Start windows styles     
*                                   
*   Description     Starts window styles and definitions                 
*
*   Return Value    VOID               
*                                   
**/                                 

#define VCGET_DEFS
#include <vcstdio.h>

VOID startstyle(sp,dp)
struct STR_WSTYLE *sp;
struct STR_WDEF *dp;
    {
    VOID addwstyle();
    VOID addwdef();
#ifdef VCDEBUG
    vcdebug = (TEXT *)"startstyle";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    while(sp->wssnam != NULL)
        {
        addwstyle(sp->wssnam,sp->wssctrl,sp->wssfch,sp->wssbd,
                    sp->wssbg,sp->wsssay,sp->wssget,sp->wssnget,
                    sp->wsstit,sp->wssrtit,sp->wssltit,sp->wssbtit,
                    sp->wssstat);
        sp++;
        }
    while(dp->wdsname != NULL)
        {
        addwdef(dp->wdsname,dp->wdsstyle,dp->wdstitle,dp->wdsrtitle,
                dp->wdsltitle,dp->wdsbtitle,dp->wdsur,dp->wdsuc,
                dp->wdslr,dp->wdslc,dp->wdswid,dp->wdsdep,dp->wdssmer,
                dp->wdsbmer);
        dp++;
        }
    }
