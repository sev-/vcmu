/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:31
*
*   Name            wsetup.c  --  setup window structure information
*
*   Description     This function allocates the memory for the 
*                   virtual window and set all the values in the 
*                   window structure. The dth and wth are adjusted
*                   to the minimum requirements for the window.
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef WINDOW

WPTR wsetup(name,ctrl,up_r,up_c,lo_r,lo_c,ch,bg_atr,bd_atr,sy_at,
              gt_at,ngt_at,ti_at,tit,dth,wth)
TEXT *name;         /* Pointer to window name                       */
COUNT ctrl;         /* Window control byte                          */
COUNT up_r,up_c;    /* Upper left row and column                    */
COUNT lo_r,lo_c;    /* Lower right row and column                   */
COUNT ch;           /* Background fill character                    */
COUNT bg_atr;       /* Background attribute                         */
COUNT bd_atr;       /* Border attribute                             */
COUNT sy_at;        /* Say attribute                                */
COUNT gt_at;        /* Active get attribute                         */
COUNT ngt_at;       /* Non active get attribute                     */
COUNT ti_at;        /* Title attribute                              */
TEXT *tit;          /* Pointer to Title for window                  */
COUNT dth;          /* Depth of virtual window                      */
COUNT wth;          /* Width of virtual window                      */
    {
    FAST COUNT bd;
    TEXT *vcalloc();
    FAST WPTR wptr;
    COUNT len;      /* Length of title for allocating               */
    COUNT strlen();
    TEXT *strcpy();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wsetup:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((wptr = (WPTR) vcalloc(sizeof(*wptr),(UCOUNT)1,vcdebug)) == 
                           (WPTR)0)
        {
        vcerror=WPTRMEM;
        return((WPTR) 0);
        }
    bd=(ctrl & BORDER ? 1 : 0);
    wptr->wdlist = (WPTR) 0;
    wptr->wnext = (WPTR) 0;
    wptr->wprevious = (WPTR) 0;
    if(wdoctrl->whead != (WPTR) 0)
        wdoctrl->wtail->wdlist = wptr;
    else
        wdoctrl->whead = wptr;
    wdoctrl->wtail = wptr;
    wptr->wname = name;
    wptr->wctrl = ctrl;
    if((up_r < 0) || (up_r > vcterm.rows-1))
        up_r=0;
    if((up_c < 0) || (up_c > vcterm.cols-1))
        up_c=0;
    if((lo_r < up_r) || (lo_r > vcterm.rows-1))
        up_r=vcterm.rows-1;
    if((lo_c < up_c) || (lo_c > vcterm.cols-1))
        up_c=vcterm.cols-1;
    wptr->upper_r=up_r;
    wptr->upper_c=up_c;
    wptr->lower_r=lo_r;
    wptr->lower_c=lo_c;
    if(dth < (lo_r-up_r+1-(2*bd)))
        dth=lo_r-up_r+1-(2*bd);
    if(wth < (lo_c-up_c+1-(2*bd)))
        wth=lo_c-up_c+1-(2*bd);
    wptr->depth=dth;
    wptr->width=wth;
    wptr->border_at=bd_atr;
    wptr->fill_ch=ch;
    wptr->bg_at=bg_atr;
    wptr->say_at=sy_at;
    wptr->get_at=gt_at;
    wptr->nget_at=ngt_at;
    wptr->c_pos=0;
    wptr->r_pos=0;
    wptr->cur_r=0;
    wptr->cur_c=0;
    wptr->smerge=0;
    if(tit != NULLTEXT)
        {
        len = strlen(tit);
        if((wptr->title = vcalloc(sizeof(TEXT),(UCOUNT)len+1,vcdebug)) == 
                                  NULLTEXT)
            {
            vcerror=WPTRMEM;
            return((WPTR) 0);
            }
        strcpy(wptr->title,tit);
        }
    else
        wptr->title = NULLTEXT;
    wptr->tit_at=ti_at;
    if((wptr->location=vcalloc((UCOUNT)(wth*dth)<< 1,(UCOUNT)1,
                                                vcdebug)) == NULLTEXT)
        {
        vcerror=WLOCMEM;
        return((WPTR) 0);
        }
    return(wptr);
    }
#endif

