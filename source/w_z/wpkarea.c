/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:22:00
*
*   Name            wpkarea.c  --  Pick an area of the screen
*
*   Description     This function marks an area 
*
*   Return Value    Returns -1 on error
*
**/

#include <vcstdio.h>

#ifdef WINDOW

COUNT wpkarea(upr,upc,lor,loc,mupr,mupc,mlor,mloc,attr,bd,depth,width,key)
COUNT *upr,*upc;    /* Upper row and column to start                */
COUNT *lor,*loc;    /* Lower row and column to start                */
COUNT mupr,mupc;    /* Max upper row and column                     */
COUNT mlor,mloc;    /* Max lower row and column                     */
COUNT attr;         /* Attribute for border                         */
COUNT bd;           /* If border                                    */
COUNT depth,width;  /* Max depth and width                          */
COUNT key;          /* Extra key to cause exit                      */
    {
    TEXT message1[80],message2[80],*strcpy();
    COUNT tmp,retval=0;
    WPTR wptr;
    COUNT ans,mode=0;
    WPTR wxopen();
    VOID wwtb();
    VOID watsay();
    COUNT getone();
    VOID wrtb();
    COUNT wclose();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "wpkarea:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if((wptr=wxopen(vcterm.rows-1,0,vcterm.rows-1,78,NULLTEXT,4,0,0)) ==
                                                            (WPTR) 0)
        return(-3);
    tmp = wdoctrl->wbgdisplay;
    wdoctrl->wbgdisplay = 1;
    depth--; width--;
    strcpy(message1,
" Use Arrows to Move Window -- Press End to Change Size -- Return to Quit");
    strcpy(message2,
" Use Arrows to Change Size -- Press End to Move Window -- Return to Quit");
    wwtb(*upr,*upc,*lor,*loc,attr);
    watsay(wptr,0,3,message1);
/* wclose(wptr); return(vckey.ret);*/
    while( TRUE )
        {
        ans=getone();
        if( ans == vckey.cur_up )
            {
            if(mode)
                {
                if(*lor > (*upr+(2*bd)))
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*lor)--;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            else
                {
                if(*upr > mupr)
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*upr)--;
                    (*lor)--;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            continue;
            }
        if( ans == vckey.cur_down )
            {
            if(mode)
                {
                if((*lor < (*upr+depth+(2*bd))) && (*lor < mlor))
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*lor)++;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            else
                {
                if(*lor < mlor)
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*upr)++;
                    (*lor)++;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            continue;
            }
        if( ans == vckey.cur_right )
            {
            if(mode)
                {
                if((*loc < (*upc+width+(2*bd))) && (*loc < mloc))
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*loc)++;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            else
                {
                if(*loc < mloc)
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*upc)++;
                    (*loc)++;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            continue;
            }
        if( ans == vckey.cur_left )
            {
            if(mode)
                {
                if(*loc > (*upc+(2*bd)))
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*loc)--;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            else
                {
                if(*upc > mupc)
                    {
                    wrtb(*upr,*upc,*lor,*loc);
                    (*upc)--;
                    (*loc)--;
                    wwtb(*upr,*upc,*lor,*loc,attr);
                    }
                }
            continue;
            }
        if( ans == vckey.end_key )
            {
            if(mode)
                {
                watsay(wptr,0,3,message1);
                mode=0;
                }
            else
                {
                watsay(wptr,0,3,message2);
                mode=1;
                }
            continue;
            }
        if(ans == spkey.abort)
            {
            retval = spkey.abort;
            break;
            }
        if(ans == vckey.ret)
            {
            retval = vckey.ret;
            break;
            }
        if(ans == key)
            {
            retval = key;
            break;
            }
        }
    wdoctrl->wbgdisplay=tmp;
    wrtb(*upr,*upc,*lor,*loc);
    wclose(wptr);
    return(retval);
    }

#endif


