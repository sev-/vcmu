/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:04:37
*
*   Name            dfvclist.c 
*
*   Description     This is the default function used in plist  
*                   
*   Return Value    This function returns to getfield whether to
*                   recieve input go field left or field right
*
**/

#define SEL_DEFS
#define VCGET_DEFS

#include <vcstdio.h>

#ifdef WINDOW

#ifdef USESHORT
#define SCANVALUE "%hd %hd %hd %hd "
#else
#define SCANVALUE "%d %d %d %d "
#endif

COUNT dfvclist(table)
GETTABLE *table;    /* Pointer to select set structure              */
    {
    SELSET *itmptr,*head,*tail;
    SELSET *lst;
    SELSET *picked;
    GETITEM *node;
    TEXT *srce,*dest;
    COUNT nbr=1;
    COUNT width=0;
    COUNT cnt=1;
    COUNT hi,lo,pg;
    COUNT bottom;
    COUNT ctrlbyte;
    COUNT bd=0,more=1;
    COUNT ofst;
    COUNT up=999,lf=999,pgsiz=999,start=1;
    COUNT editfld = FALSE;
    TEXT *ttl;
    COUNT n;
    WPTR wptr;
    WPTR wxopen();
    COUNT strlen();
    COUNT strcmp();
    VOID atsay();
    VOID at();
    COUNT wrows();
    COUNT wshow();
    VOID vcflush();
    VOID selbar();
    COUNT getone();
    VOID bell();
    COUNT ungetone();
    COUNT wclose();
    COUNT numstrcpy();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "clect:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    node = table->tcurnode;

    lst = (SELSET *)node->gselset;

    if( sscanf(lst->idisplay,SCANVALUE,&up,&lf,&pgsiz,&start) != 4 )
        {
        if( up == 999 )
            up = 0;
        if( lf == 999 )
            lf = 0;
        }

    ttl=lst->idisplay;
    while( !vcalpha(*ttl) && *ttl )
        ttl++;

    if( pgsiz == 1 )
        ctrlbyte = 0;
    else
        {
        bd=1;
        ctrlbyte = BORDER+BD1;
        }

    itmptr=lst->inext;
    while(itmptr)
        {
        width=max(width,strlen(itmptr->idisplay));
        itmptr=itmptr->inext;
        nbr++;
        }
    nbr--;

    width = max(width,(strlen(ttl)));

    if( lf+width-1+bd+bd > vcterm.cols-1 )
        lf=vcterm.cols-width-(bd+bd);

    bottom=min(nbr,pgsiz);

    if( up+bottom-1+bd+bd > vcterm.rows-1 )
        up=vcterm.rows-bottom-(bd+bd);

    if( pgsiz==1 )
        ofst = -1;
    else
        ofst=1;

    wptr=wxopen(up,lf,up+bottom+ofst,lf+width+ofst,ttl,ctrlbyte,nbr,0);
    tail=head=itmptr=lst->inext;
    while( itmptr )
        {
        tail=itmptr;
        atsay(cnt-1,0,itmptr->idisplay);
        cnt++;
        itmptr=itmptr->inext;
        }
    hi=wptr->get_at;
    lo=wptr->say_at;
    pg=wrows(wptr);
    if(!isblank(node->gtmpfld))
        {
        start = 1;
        itmptr = lst->inext;
        while(itmptr != (SELSET *)0)
            {
            cnt = min(strlen(node->gtmpfld),strlen(itmptr->ivalue));        
            if(!strncmp(node->gtmpfld,itmptr->ivalue,cnt))
                break;
            start++;
            itmptr = itmptr->inext;
            }
        if(itmptr == (SELSET *)0)
            start = 0;
        }
    cnt=start;
    wshow(wptr);
    picked=head;
    if(cnt)
        {
        picked = head;
        cnt--;
        while(cnt && (picked != (SELSET *)0))
            {
            picked = picked->inext;
            cnt--;
            }
        }
    cnt = start;
#ifdef TERMINAL
    if(vctio == 5)
        vcflush();
#endif
    while( more )
        {
        if(cnt)
            selbar(wptr,cnt-1,0,hi,width);

        table->tkeypress=getone();

        if( gethk1 )
            {
            if((*gethk1)(table))
                continue;
            }
        if( table->tkeypress == spkey.list_up )
            {
            if( cnt-1 < 1 )
                {
                if( pgsiz==1 )
                    {
                    cnt=nbr;
                    picked = tail;
                    }
                else
                    bell();
                }
            else
                {
                selbar(wptr,cnt-1,0,lo,width);
                cnt--;
                picked = picked->iprev;
                }
            continue;
            }
        if( table->tkeypress == spkey.list_dn )
            {
            if( cnt+1 > nbr )
                {
                if( pgsiz==1 )
                    {
                    picked = head;
                    cnt=1;
                    }
                else
                    bell();
                }
            else
                {
                selbar(wptr,cnt-1,0,lo,width);
                cnt++;
                if(cnt == 1)
                    picked = head;
                else
                    picked = picked->inext;
                }
            continue;
            }
        if( table->tkeypress == spkey.list_pgdn )
            {
            if( cnt == nbr )
                bell();
            else
                {
                selbar(wptr,cnt-1,0,lo,width);
                n=pg;
                while( n && cnt < nbr )
                    {
                    n--;
                    cnt++;
                    if(cnt == 1)
                        picked = head;
                    else
                        picked = picked->inext;
                    }
                }
            continue;
            }
        if( table->tkeypress == spkey.list_pgup )
            {
            if( (cnt == 1) || (cnt == 0) )
                bell();
            else
                {
                selbar(wptr,cnt-1,0,lo,width);
                n=pg;
                while( n && cnt > 1 )
                    {
                    n--;
                    picked = picked->iprev;
                    cnt--;
                    }
                }
            continue;
            }
        if( table->tkeypress == spkey.list_home )
            {
            if( cnt==1 )
                bell();
            else
                {
                selbar(wptr,cnt-1,0,lo,width);
                picked = head;
                cnt=1;
                }
            continue;
            }
        if( table->tkeypress == spkey.list_end )
            {
            if( cnt==nbr )
                bell();
            else
                {
                selbar(wptr,cnt-1,0,lo,width);
                picked = tail;
                cnt=nbr;
                }
            continue;
            }
        if( table->tkeypress == spkey.fld_ret )
            {
            more = 0;
            continue;
            }
        if( (table->tkeypress == spkey.fld_mode) &&
            !(table->tcurnode->gcontrol & FLDSET) )
            {
            selmode = !selmode;
            cnt = -1;
            editfld = TRUE;
            more = 0;
            continue;
            }
        if( (table->tkeypress < 256) &&
            !(table->tcurnode->gcontrol & FLDSET) )
            {
            editfld = TRUE;
            ungetone(table->tkeypress);
            cnt = -1;
            more = 0;
            continue;
            }
        if( table->tkeypress == spkey.fld_left ||
            table->tkeypress == spkey.fld_right ||
            table->tkeypress == spkey.fld_up ||
            table->tkeypress == spkey.fld_down ||
            table->tkeypress == spkey.fld_pgup ||
            table->tkeypress == spkey.fld_pgdn ||
            table->tkeypress == spkey.fld_end ||
            table->tkeypress == spkey.fld_home ||
            table->tkeypress == spkey.abort ||
            table->tkeypress == spkey.done ||
            table->tkeypress == '.'  ||
            table->tkeypress >= 9000 )
            {
            more=0;
            cnt = -1;
            continue;
            }
        bell();
        }
    wclose(wptr);
    if(cnt > 0)
        {
        srce = picked->ivalue;
        dest = node->gtmpfld;
        while( *srce && *dest )
            *dest++ = *srce++;
        while( *dest )
            *dest++ = ' ';
        }
    return(editfld);
    }
#endif
