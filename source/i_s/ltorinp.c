/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:09:17
*
*   Name            ltorinp.c  --  Left to right input
*
*   Description     This is the input routine for left to right
*                   input. It skips special characters and only
*                   allows characters that fit the picture to be
*                   entered.
*
*   Return Value    Returns the character that caused exit
*
**/

#define VCGET_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT ltorinp(table)
GETTABLE *table;    /* Get table to input field                     */
    {
    COUNT retval = 0;
    VOID ltordraw();
    VOID ltorhpass();
    VOID ltorcleft();
    VOID ltorcright();
    VOID ltorbksp();
    VOID ltordel();
    VOID ltorins();
    VOID ltormode();
    VOID ltorblank();
    VOID ltorichr();
    VOID ltorcls();
    VOID ltordeof();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "ltorinp:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    ltorhpass(table);
    while(TRUE)
        {
        ltordraw(table);
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
            ltorcleft(table);
            continue;
            }
        if( table->tkeypress == spkey.fld_cright )
            {
            ltorcright(table);
            continue;
            }
        if( table->tkeypress == spkey.fld_bksp )
            {
            ltorbksp(table);
            continue;
            }
        if( table->tkeypress == spkey.fld_del)
            {
            ltordel(table);
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
            ltorcls(table);
            continue;
            }
        if(table->tkeypress == spkey.fld_deof)
            {
            ltordeof(table);
            continue;
            }
        ltorichr(table);
        } 
    return(retval);
    }

VOID ltordraw(table)
GETTABLE *table;
    {
    GETITEM *gp;
    gp = table->tcurnode;
    if( gp->gmagic != GETNODEMAGIC )
        {
        vcerror = LTORBADGET;
        return;
        }
    if( gp->gcndx < gp->gstart )
        {
        gp->gstart = gp->gcndx;
        gp->gredraw = TRUE;
        }                    
    if( gp->gcndx > (gp->gstart + gp->gdispsiz - 1) )
        {
        gp->gstart = gp->gcndx - gp->gdispsiz + 1;
        gp->gredraw = TRUE;
        }                    
    if(gp->gredraw)
        {
        lightlr(gp);
        gp->gredraw = FALSE;
        }
    at(gp->g_row,gp->g_col + gp->gcndx - gp->gstart);
    }

VOID ltorhpass(table)
GETTABLE *table;
    {
    GETITEM *gp;
    COUNT evalpic();
    gp = table->tcurnode;
    if(gp->gcontrol & FLDCLEAR)
        ltorblank(gp,0);
    if(gp->gcndx > gp->gendndx)
        gp->gcndx = gp->gendndx;
    if((gp->gcndx < gp->gbegndx) || !evalpic(gp->gtmppic[gp->gcndx]))
        gp->gcndx = gp->gbegndx;
    if(gp->gcndx != gp->gbegndx)
        gp->gfkey = FALSE;
    else
        gp->gfkey = TRUE;
    }

VOID ltorcleft(table)
GETTABLE *table;
    {
    GETITEM *gp;
    COUNT evalpic();
    VOID bell();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->gcndx > gp->gbegndx)
        while(!evalpic(gp->gtmppic[--(gp->gcndx)]));
    else
        bell();
    }

VOID ltorcright(table)
GETTABLE *table;
    {
    GETITEM *gp;
    COUNT evalpic();
    VOID bell();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->gcndx < gp->gendndx)
        while(!evalpic(gp->gtmppic[++(gp->gcndx)]));
    else
        bell();
    }

VOID ltorbksp(table)
GETTABLE *table;
    {
    COUNT tmp;
    GETITEM *gp;
    VOID bell();
    VOID ltordel();
    VOID ltorcleft();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    if(gp->g_length == 1)
        {
        if(gp->gtmpfld[gp->gcndx] != ' ')
            ltordel(table);
        else
            bell();
        }
    else
        {
        if(gp->gcndx > gp->gbegndx)
            {
            if( (gp->gcndx == gp->gendndx)  &&
                (gp->gtmpfld[gp->gcndx] != ' ') && gp->gatend )
                {
                gp->gtmpfld[gp->gcndx] = ' ';
                gp->gredraw = TRUE;
                gp->gatend = FALSE;
                }
            else
                {
                ltorcleft(table);
                ltordel(table);
                }
            }
        else
            bell();
        }
    }

VOID ltordel(table)
GETTABLE *table;
    {
    COUNT tmp;
    TEXT ptmp;
    GETITEM *gp;
    COUNT evalpic();
    VOID bell();
    gp = table->tcurnode;
    gp->gfkey = FALSE;
    tmp = gp->gcndx;
    ptmp = gp->gtmppic[gp->gcndx];
    while((tmp < gp->gendndx) && (ptmp == gp->gtmppic[tmp+1]))
        {
        gp->gtmpfld[tmp] = gp->gtmpfld[tmp+1];
        tmp++;
        }
    if(evalpic(gp->gtmppic[tmp]))
        gp->gtmpfld[tmp] = ' ';
    gp->gredraw = TRUE;
    gp->gatend = FALSE;
    }

VOID ltorins(table)
GETTABLE *table;
    {
    VOID vccurs();
    table->tcurnode->gfkey = FALSE;
    if(table->tinsmode)
        {
        vccurs(NORMCURSOR);
        table->tinsmode = FALSE;
        }
    else
        {
        vccurs(ALTCURSOR);
        table->tinsmode = TRUE;
        }
    if(checkmode != NULLFUNC)
        (*checkmode)(table);
    }

VOID ltormode(table,more,rval)
GETTABLE *table;
COUNT *more,*rval;
    {
    selmode = !selmode;
    if( selmode && !(table->tcurnode->gcontrol & FLDNOSET) && 
        (table->tcurnode->gselset != NULLTEXT) &&
        (table->tcurnode->gplist != NULLFUNC))
        {
        *rval = TRUE;
        *more = 0;
        }
    if(checkmode != NULLFUNC)
        (*checkmode)(table);
    }

VOID ltorblank(gp,flag)
GETITEM *gp;
COUNT flag;                 /* True == del_end_of_line  */
    {
    TEXT *ofset;
    COUNT current;
    VOID blank();
    VOID initlr();
    gp->gfkey = FALSE;
    ofset = gp->gtmpfld;
    if(flag)
        ofset += gp->gcndx;
    blank(ofset);
    current = gp->gcndx;
    initlr(gp);
    gp->gredraw = TRUE;
    gp->gcndx = current;
    gp->gatend = FALSE;
    }

COUNT vcvalchr(key)
COUNT key;
    {
    COUNT retval = TRUE;

    /* В этом месте вставлены русские  буквы */
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

    if( (unsigned char)key < (unsigned char)' ' || (unsigned char)key > (unsigned char)'\377')
        retval = FALSE;
    return(retval);
    }

VOID ltorichr(table)
GETTABLE *table;
    {
    TEXT schar,ochar,opic;
    COUNT current;
    COUNT key;
    GETITEM *gp;
    VOID bell();
    VOID ltorblank();
    VOID ltorcright();
    gp = table->tcurnode;
    key = table->tkeypress;
    opic = gp->gtmppic[gp->gcndx];
    if(((gp->gcndx == gp->gendndx) && gp->gatend) ||
       !vcvalchr(key) || !picok(key,opic) )
        {
        bell();
        return;
        }
    if(gp->gfkey && (gp->gcontrol & FLDBLANK) && 
       hasdata(gp->gtmpfld,gp->gtmppic) )
        ltorblank(gp,FALSE);
    gp->gfkey = FALSE;
    if(isupper(opic) && islower(key))
        key = toupper(key);
    if(gp->gcndx < gp->gendndx)
        gp->gatend = FALSE;
    ochar = gp->gtmpfld[gp->gcndx]; 
    gp->gtmpfld[gp->gcndx] = key;
    if(table->tinsmode)
        {
        current = gp->gcndx;
        while((current <= gp->gendndx) && (opic == gp->gtmppic[current+1]))
            {
            schar = gp->gtmpfld[current+1];
            gp->gtmpfld[current+1] = ochar;
            ochar = schar;
            current++;
            }
        gp->gredraw = TRUE;
        }
    else
        {
        if(gp->gcontrol & FLDPASSWD)
            {
            if(key != ' ')
                vcputc('*',gp->gcurattr);
            }
        else
            vcputc(key,gp->gcurattr);
        }
    if(gp->gcndx == gp->gendndx)
        {
        if(gp->gcontrol & FLDNORET)
            vcpushkey(spkey.fld_ret);
        else 
            gp->gatend = TRUE;
        }
    else
        ltorcright(table);
    }

VOID ltorcls(table)
GETTABLE *table;
    {
    GETITEM *gp;
    gp = table->tcurnode;
    if(hasdata(gp->gtmpfld,gp->gtmppic) )
        ltorblank(gp,FALSE);
    }

VOID ltordeof(table)
GETTABLE *table;
    {
    GETITEM *gp;
    gp = table->tcurnode;
    if(hasdata(gp->gtmpfld,gp->gtmppic) )
        ltorblank(gp,TRUE);
    }


