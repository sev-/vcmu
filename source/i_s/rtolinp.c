/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:43
*
*   Name            rtolinp.c  --  right to left input
*
*   Description     This is the input routine for right to left 
*                   input. 
*
*   Return Value    Returns the character that caused exit
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT rtolinp(table)
GETTABLE *table;    /* Get table to input field                     */
    {
    COUNT retval = 0;
    VOID rtoldraw();
    VOID rtolhpass();
    VOID rtolflip();
    VOID rtolcleft();
    VOID rtolcright();
    VOID rtolbksp();
    VOID rtoldel();
    VOID rtolichr();
    VOID rtolcls();
    VOID rtolldel();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "rtolinp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    rtolhpass(table);
    while(TRUE)
        {
        rtoldraw(table);
        table->tkeypress = getone();
        if( gethk1 )
            {
            if((*gethk1)(table))
                continue;
            }
        if( isexitkey(table->tkeypress))
            break;
        if( table->tkeypress == spkey.fld_cleft )
            {
            rtolcleft(table);
            continue;
            }
        if( table->tkeypress == spkey.fld_cright )
            {
            rtolcright(table);
            continue;
            }
        if(table->tkeypress == spkey.fld_bksp) 
            {
            rtolbksp(table);
            continue;
            }
        if(table->tkeypress == spkey.fld_del) 
            {
            rtoldel(table);
            continue;
            }
        if( table->tkeypress == spkey.fld_ins )
            {
            ltorins(table);
            continue;
            }
        if(table->tkeypress == spkey.fld_mode)
            {
            ltormode(table/*,&more,&retval*/);
            continue;
            }
        if(table->tkeypress == spkey.fld_blank)
            {
            rtolcls(table);
            continue;
            }
        if(table->tkeypress == vcdecimal)
            {
            rtolflip(table);
            continue;
            }
        rtolichr(table);
        } 
    return(retval);
    }

VOID rtoldraw(table)
GETTABLE *table;
    {
    GETITEM *gp;
    gp = table->tcurnode;
    if(gp->gredraw)
        {
        lightrl(gp);
        gp->gredraw = FALSE;
        if(gp->gstart && gp->gmaxwid && gp->gatend 
           && (gp->gcontrol & FLDNORET))
            vcpushkey(spkey.fld_ret);
        }
    at(gp->g_row,gp->g_col + gp->gcndx);
    }

VOID rtolhpass(table)
GETTABLE *table;
    {
    GETITEM *gp;
    TEXT *ptr;
    VOID rtolblank();
    gp = table->tcurnode;
    if(gp->gcontrol & FLDCLEAR)
        rtolblank(gp);
    if(gp->gmaxwid && (gp->gcontrol & FLDASSUME))
        gp->gmaxwid = 0;
    if(gp->gmaxwid)
        gp->gcndx = gp->gbegndx - 2;
    else
        gp->gcndx = strlen(gp->gtmpfld) - 1;
    gp->gstart = 1;
    gp->gfkey = TRUE;
    }

VOID rtolflip(table)
GETTABLE *table;
    {
    GETITEM *gp;
    TEXT *ptr;
    TEXT *tptr;
    COUNT tcnt;
    COUNT full = FALSE;
    TEXT buf[60];
    TEXT *ttrim();
    COUNT rtolprec();
    COUNT sprtnum();
    VOID bell();
    gp = table->tcurnode;
    if(gp->gstart)
        {
        if(!gp->gmaxwid && (gp->gcontrol & FLDASSUME))
            {
            gp->gmaxwid = rtolprec(gp->gtmppic);
            if(gp->gmaxwid)
                {
                table->tkeypress = '0';
                tcnt = gp->gmaxwid;
                ptr = ttrim(gp->gtmpfld);
                if(!gp->gfkey)
                    {
                    while(tcnt && !full)
                        {
                        rtolichr(table);
                        full = sprtnum(buf,gp->gtmpfld,gp->gtmppic);
                        tcnt--;
                        }
                    }
                if(full && tcnt)
                    {
                    gp->gmaxwid = 0;
                    strcpy(gp->gtmpfld,ptr);
                    }
                else
                    {
                    gp->gendndx = gp->g_length - 1;
                    gp->gbegndx = gp->gendndx - gp->gmaxwid + 1;
                    ptr = gp->gtmpfld + gp->gbegndx;
                    while(*ptr != '\0')
                        {
                        if(*ptr == ' ')
                            *ptr = '0';
                        ptr++;
                        }
                    }
                }
            }
        if(gp->gmaxwid)
            {
            ptr = gp->gtmpfld + gp->gbegndx;
            gp->gstart = 0;
            tptr = gp->gtmpfld + gp->gendndx;
            if((*tptr == ' ') || (*tptr == '0'))
                gp->gatend = FALSE;
            else
                gp->gatend = TRUE;
            while(tptr >= ptr)
                {
                if((*tptr == ' ') || (*tptr == '0'))
                    tptr--;
                else
                    break;
                }
            gp->gcndx = min(((COUNT)(tptr - gp->gtmpfld) + 1),gp->gendndx);
            }
        else
            bell();
        }
    else
        {
        gp->gstart = 1;
        gp->gcndx = gp->gbegndx - 2;
        gp->gatend = sprtnum(buf,gp->gtmpfld,gp->gtmppic);
        }
    gp->gfkey = FALSE;
    }

VOID rtolcleft(table)
GETTABLE *table;
    {
    GETITEM *gp;
    VOID bell();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->gstart)
        bell();
    else
        {
        if(gp->gcndx == gp->gbegndx)
            rtolflip(table);
        else
            ltorcleft(table);
        }
    }

VOID rtolcright(table)
GETTABLE *table;
    {
    GETITEM *gp;
    VOID bell();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->gstart)
        {
        if(gp->gmaxwid)
            rtolflip(table);
        else
            bell();
        }
    else
        ltorcright(table);
    }

VOID rtolbksp(table)
GETTABLE *table;
    {
    GETITEM *gp;
    TEXT *ptr;
    VOID rtolldel();
    VOID ltorbksp();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->gstart)
        rtolldel(table);
    else
        {
        if(gp->gcndx == gp->gbegndx)
            rtolflip(table);
        else
            {
            ptr = gp->gtmpfld + gp->gcndx;
            ltorbksp(table);
            *ptr = '0';
            }
        }
    }

VOID rtoldel(table)
GETTABLE *table;
    {
    GETITEM *gp;
    TEXT *ptr;
    VOID bell();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->gstart)
        rtolldel(table);
    else
        {
        ltordel(table);
        ptr = gp->gtmpfld + gp->gendndx;
        *ptr = '0';
        }
    }

VOID rtolblank(gp)
GETITEM *gp;
    {
    TEXT *ofset;
    COUNT current;
    VOID blank();
    VOID initlr();
    gp->gfkey = FALSE;
    blank(gp->gtmpfld);
    current = gp->gcndx;
    initrl(gp);
    gp->gredraw = TRUE;
    gp->gcndx = current;
    gp->gatend = FALSE;
    }

VOID rtolichr(table)
GETTABLE *table;
    {
    TEXT opic;
    COUNT key;
    GETITEM *gp;
    COUNT vcvalchr();
    COUNT picok();
    VOID rtolblank();
    COUNT hasdata();
    VOID ltorichr();
    VOID rtolsign();
    VOID rtolrins();
    gp = table->tcurnode;
    key = table->tkeypress;
    opic = gp->gtmppic[gp->gcndx];
    if(((opic == '#') || (opic == '9')) && 
            ((key == '-') || (key == '+')) )
        rtolsign(table);
    else
        {
        if(!vcvalchr(key) || !(picok(key,opic)))
            {
            bell();
            return;
            }
        if(gp->gfkey && (gp->gcontrol & FLDBLANK) && 
           hasdata(gp->gtmpfld,gp->gtmppic) )
            rtolblank(gp);
        if(gp->gatend)
            {
            bell();
            return;
            }
        gp->gfkey = FALSE;
        if(gp->gstart)
            rtolrins(table);
        else
            ltorichr(table);
        }
    }

VOID rtolcls(table)
GETTABLE *table;
    {
    GETITEM *gp;
    VOID rtolblank();
    gp = table->tcurnode;
    if(hasdata(gp->gtmpfld,gp->gtmppic) )
        rtolblank(gp);
    }

VOID rtolsign(table)
GETTABLE *table;
    {
    TEXT *ptr;
    GETITEM *gp;
    TEXT *strchr();
    VOID bell();
    VOID rtolblank();
    gp = table->tcurnode;
    if((strchr(gp->gtmppic,'-') == NULLTEXT) &&
         (strchr(gp->gtmppic,'+') == NULLTEXT) )
        bell();
    else
        {
        if(gp->gfkey && (gp->gcontrol & FLDBLANK) && 
           hasdata(gp->gtmpfld,gp->gtmppic) )
            rtolblank(gp);
        gp->gfkey = FALSE;
        ptr = gp->gtmpfld;
        while(*(ptr+1) != '\0')
            {
            if((*(ptr+1) == ' ') || (*(ptr+1) == vcdecimal) ||
               (*(ptr+1) == '+') || (*(ptr+1) == '-') )
                ptr++;
            else
                break;
            }
        if(*ptr == vcdecimal)
            ptr--;
        if(table->tkeypress == '-')
            *ptr = table->tkeypress;
        else
            *ptr = ' ';
        gp->gredraw = TRUE;
        }
    }

VOID rtolrins(table)
GETTABLE *table;
    {
    TEXT schar,ochar,opic;
    TEXT *ptr;
    COUNT key;
    GETITEM *gp;
    COUNT vcvalchr();
    VOID bell();
    VOID rtolblank();
    gp = table->tcurnode;
    key = table->tkeypress;
    opic = gp->gtmppic[gp->gcndx];
    if(((opic == 'X') || (opic == 'A')) && islower(key))
        key = toupper(key);
    ochar = *(gp->gtmpfld + gp->gcndx);
    *(gp->gtmpfld + gp->gcndx) = (TEXT )key;
    ptr = gp->gtmpfld + gp->gcndx;
    if(!((ochar == '0') && !isalnum(*(ptr-1)) ) ||
       (gp->gcontrol & FLDZEROS) )
        {
        while(ptr > gp->gtmpfld)
            {
            ptr--;
            if(*ptr == vcdecimal)
                ptr--;
            schar = *ptr;
            *ptr = ochar;
            ochar = schar;
            }
        }
    gp->gredraw = TRUE;
    }

VOID rtolldel(table)
GETTABLE *table;
    {
    TEXT ochar,schar;
    TEXT *ptr;
    GETITEM *gp;
    VOID bell();
    gp = table->tcurnode;
    if(gp->gfkey && (gp->gcontrol & FLDBLANK) && 
          hasdata(gp->gtmpfld,gp->gtmppic) )
        rtolblank(gp);
    gp->gfkey = FALSE;
    gp->gatend = FALSE;
    ptr = gp->gtmpfld;
    ochar = *ptr;
    *ptr = ' ';
    while(ptr < (gp->gtmpfld + gp->gcndx))
        {
        ptr++;
        if(*ptr == vcdecimal)
            ptr++;
        schar = *ptr;
        *ptr = ochar;
        ochar = schar;
        }
    ptr = gp->gtmpfld + gp->gcndx;
    if(!(gp->gcontrol & FLDZEROS) && !isalnum(*ptr))
        *ptr = '0';
    gp->gredraw = TRUE;
    }

