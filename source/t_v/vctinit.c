/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:19:05
*                
*   Name            vctinit.c  --  terminal init program
*
*   Description     This function sets up the terminal
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>
#include <vctcap.h>

COUNT vctinit(useterm)
TEXT *useterm;              /* Name of terminal to use or NULL      */
    {                       /* ------------------------------------ */
    struct termctrl *termptr;   /* Termctrl structure to init       */
    struct vckeys *keyptr;      /* Tckey structure to init          */ 
    struct BODR *bordptr;       /* Border structure to init         */
    TEXT tmpbuf[50],**ptr,**tstr,*vcgetenv(),*tmptr,*vcgetstr(),*gtname();
    TEXT *vcalloc(),term[20],*termcapbuf,*area,*area_end;
    COUNT err,*tnum,cnt,start;
    TEXT *strcpy();
    COUNT vcgetent();
    VOID terror();
    VOID vcfree();
    TEXT *strncpy();
    COUNT vcgetnum();
    COUNT vcgetflag();
    COUNT addtable();
    COUNT strcmp();
    TEXT *strtok();
    VOID ckspterm();
    COUNT atoi();
    struct KEYLBL *lblptr,*lblend;
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vctinit:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    termptr = (struct termctrl *)&vcterm.tmname;
    keyptr =  (struct vckeys *)&vckey.esc;
    bordptr = (struct BODR *)&border[0].up;
    /*--------------------------------------------------------------*/
    /*-----------------Get Termcap Information----------------------*/
    /*--------------------------------------------------------------*/
    if((termcapbuf = vcalloc(3600,sizeof(TEXT),vcdebug)) == NULLTEXT)
        {
        vcerror = TCAPMEM;
        return(-1);
        }
    if(useterm == NULLTEXT)
        {
#ifdef IBM
        strcpy(tmpbuf,"ibmpc");
#endif
#ifdef OS2
        strcpy(tmpbuf,"os2pc");
#endif
#ifdef TERMONLY
        strcpy(tmpbuf,"vt100");
#endif
        if((tmptr = vcgetenv("TERM")) != NULLTEXT)
            strcpy(tmpbuf,tmptr);
        }
    else
        strcpy(tmpbuf,useterm);
    if((err=vcgetent(termcapbuf,tmpbuf)) != 1)
        {
        if(err == -1)
            terror((TEXT *)"Termcap not found");
        else
            {
            strcat(tmpbuf,(TEXT *)" : Terminal not found in Termcap");
            terror(tmpbuf);
            }
        }
    if((area = vcalloc(1000,sizeof(TEXT),vcdebug)) == NULLTEXT)
        {
        vcfree(termcapbuf,vcdebug);
        vcerror = VCTRLMEM;
        return(-1);
        }
    area_end = area+975;
    tmptr = gtname(termcapbuf,&start);
    strncpy(area,tmptr,start);
    termptr->tmname = area;
    area += start;
    *area = '\0';
    area++;
    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal Number Values-----------------*/
    /*--------------------------------------------------------------*/
    tnum = &termptr->rows;
    ptr = &tnumctrl[0];
    while(*ptr != NULLTEXT)
        *(tnum++) = vcgetnum(*(ptr++));
    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal Logical Values----------------*/
    /*--------------------------------------------------------------*/
    tnum = &termptr->am;
    ptr = &tboolctrl[0];
    while(*ptr != NULLTEXT)
        *(tnum++) = vcgetflag(*(ptr++));
    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal String Values-----------------*/
    /*--------------------------------------------------------------*/
    ptr = &tstrctrl[0];
    tstr = &termptr->ae;
    while(*ptr != NULLTEXT)
        {
        *(tstr++) = vcgetstr(*(ptr++),&area);
        if(area > area_end)
            {
            vcerror = OUTTERMAREA;
            return(-1);
            }
        }
    /*--------------------------------------------------------------*/
    /*-------------------Get Border Characters----------------------*/
    /*--------------------------------------------------------------*/
    tnum = &bordptr->up;
    ptr = &tborderctrl[0];
    while(*ptr != NULLTEXT)
        {
        tmptr = &tmpbuf[0];
        vcgetstr(*(ptr++),&tmptr);
        if( tmptr != &tmpbuf[0])
            {
            *tnum = (COUNT) tmpbuf[0];
            if(termptr->gs != NULLTEXT)
#ifdef PRIMOS
                *tnum &= 0x7f;
#else
                *tnum += 128;
#endif
            }
        tnum++;
        }
    /*--------------------------------------------------------------*/
    /*-------------------Get Terminal Function Keys-----------------*/
    /*--------------------------------------------------------------*/
    start = 5000;
    strcpy(term,"k0");
    while(1)
        {
        tmptr = tmpbuf;
        if((vcgetstr(term,&tmptr)) != NULLTEXT)
            {
            tmptr = strtok(tmpbuf,"|");
            while(tmptr != NULLTEXT)
                {
                addtable(&termptr->table,tmptr,start);
                tmptr = strtok(NULLTEXT,"|");
                }
            start++;
            }
        term[1] += 1;
        if(term[1] > '9')
            {
            term[0] +=1;
            term[1] = '0';
            if(term[0] == 'l')
                term[0] += 1;
            }
        if(term[0] > 'z')
            break;
        }
    keyptr->no_fkeys = start-5000;
    /*--------------------------------------------------------------*/
    /*-------------------Setup Special Keys-------------------------*/
    /*--------------------------------------------------------------*/
    cnt = 0;
    tnum = &keyptr->esc;
    while(kload[cnt].tcap != NULLTEXT)
        {
        tmptr = tmpbuf;
        if((vcgetstr(kload[cnt].tcap,&tmptr)) != NULLTEXT)
            {
            tmptr = strtok(tmpbuf,"|");
            while(tmptr != NULLTEXT)
                {
                *tnum = addtable(&termptr->table,tmptr,kload[cnt].value);
                tmptr = strtok(NULLTEXT,"|");
                }
            tnum++;
            }
        else
            {
            if(kload[cnt].def)
                {
                tmpbuf[0] = (TEXT) kload[cnt].def;
                tmpbuf[1] = '\0';
                *(tnum++) = addtable(&termptr->table,tmpbuf,kload[cnt].value);
                }
            }
        cnt++;
        }
    /*--------------------------------------------------------------*/
    /*-------------------Setup Key Label Structure------------------*/
    /*--------------------------------------------------------------*/
    cnt = keyptr->no_fkeys + 25 +2;
    if((lblptr = (struct KEYLBL *) vcalloc(cnt,sizeof(*lblptr),
                                            vcdebug)) == (struct KEYLBL *)0)
        {
        vcfree(termcapbuf,vcdebug);
        vcerror = TLBLMEM;
        return(-1);
        }
    termptr->firstkeylbl = lblptr;
    lblend = lblptr;
    lblend += cnt - 2;
    start = 4000;
    strcpy(term,"00");
    cnt++;
    while(cnt)
        {
        if( (lblptr->klblptr = vcgetstr(term,&area)) != NULLTEXT)
            {
            lblptr->klblval = start;
            lblptr++;
            cnt--;
            }
        if(lblptr == lblend)
            break;
        if(area > area_end)
            {
            vcerror = OUTTERMAREA;
            return(-1);
            }
        term[1] += 1;
        start++;
        if( start > 4900 )
            {
            if(term[1] > '9')
                {
                term[0] +=1;
                term[1] = '0';
                if(term[0] == 'm')
                    term[0] = 'M';
                }
            }
        else
            {
            if(term[1] > '9')
                {
                term[0] +=1;
                term[1] = '0';
                }
            if(!strcmp(term,"25"))
                {
                start = 5000;
                strcpy(term,"l0");
                }
            }
        if((start > 5010) && (term[0] > 'Z'))
            break;
        }
    lblptr->klblval = -1;
    if(termptr->bs == 1)
        {
        termptr->bc = area;
        *area++ = (TEXT) 8;
        *area = '\0';
        }
    /*--------------------------------------------------------------*/
    /*---------Setup Terminal that attribute requires a space-------*/
    /*--------------------------------------------------------------*/
    if((termptr->sg == 1) || (termptr->ug == 1) ||
        (termptr->gg == 1) || (termptr->bb == 1) ||
        (termptr->ig == 1) )
        termptr->mc = TRUE;
    else
        termptr->mc = FALSE;
    ptr = &tspattr[0];
    tstr = &termptr->sp0on;
    while(*ptr != NULLTEXT)
        {
        *(tstr++) = vcgetstr(*(ptr++),&area);
        if(area > area_end)
            {
            vcerror = OUTTERMAREA;
            return(-1);
            }
        }
    ckspterm(termptr);
    if(termptr->sp1on == NULLTEXT)
        {
        termptr->sp1on = termptr->us;
        termptr->sp1off = termptr->ue;
        }
    if(termptr->sp4on == NULLTEXT)
        {
        termptr->sp4on = termptr->it;
        termptr->sp4off = termptr->ie;
        }
    if(termptr->sp5on == NULLTEXT)
        {
        termptr->sp5on = termptr->so;
        termptr->sp5off = termptr->se;
        }
    if(termptr->sp9on == NULLTEXT)
        {
        termptr->sp9on = termptr->bo;
        termptr->sp9off = termptr->be;
        }

    /*--------------------------------------------------------------*/
    /*---------------------------Finished---------------------------*/
    /*--------------------------------------------------------------*/
    vcfree(termcapbuf,vcdebug);
    if(termptr->zk == 1)
        vckeyrdy = FALSE;
    if(termptr->zc == -1)
        termptr->zc = 1;
    if(termptr->zt == -1)
        termptr->zt = 1;
    if((tmptr = vcgetenv("COLUMNS")) != NULLTEXT)
        termptr->cols = atoi(tmptr);
    if((tmptr = vcgetenv("LINES")) != NULLTEXT)
        termptr->rows = atoi(tmptr);
    if((tmptr = vcgetenv("VCIN")) != NULLTEXT)
        {
        vcinput = vcalloc(1,strlen(tmptr),vcdebug);
        strcpy(vcinput,tmptr);
        }
    if((tmptr = vcgetenv("VCOUT")) != NULLTEXT)
        {
        vcoutput = vcalloc(1,strlen(tmptr),vcdebug);
        strcpy(vcoutput,tmptr);
        }
    return(1);
    }

