/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 9/1/90 at 00:44:46
*
*   Name            mktsetup.c  --  make vctsetup.h file
*
*   Description     This function compiles /etc/termcap.vc text 
*                   file producing source code header file for
*                   DOS or OS2 to compile Vitamin C without 
*                   a termcap.vc or termcap.vcc file.
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>
#include <vctcap.h>

#define NUMNUMBERS 18
#define NUMSTRINGS 28
#define NUMSPECIAL 32
#define NUMPRECOMP 3

static COUNT total_entries;
static TEXT *area = NULLTEXT;
static TEXT *area_begin = NULLTEXT;
static TEXT *area_end = NULLTEXT;
static FILE *tmpfil = (FILE *)0;
static COUNT tblsize = 4000;
static TEXT *tblnext = NULLTEXT;
static TEXT *tblstart = NULLTEXT;
static LONG nextloc = 0l;
static LONG headsize = 0l;
static COUNT dirsize;
static TEXT *outfile;

main(argc,argv)
COUNT argc;
TEXT *argv[];
    {
    struct termctrl *termptr;   /* Pointer to termctrl structure to init*/
    struct vckeys *keyptr;  /* Pointer to vckey structure to init       */ 
    struct BODR *bordptr;   /* Pointer to border structure to init      */
    TEXT tmpbuf[50],**ptr,**tstr,*getenv(),*tmptr,*vcgetstr(),*gtname();
    TEXT *vcalloc(),term[40],*termcapbuf,*errptr;
    COUNT err,*tnum,cnt,start;
    struct KEYLBL *lblptr,*lblend;
    TEXT *names,*cname,tname[40],*strtok();
    COUNT more;
    VOID dftgraph();
#ifdef VCDEBUG
    vcdebug = "tcompile:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(argc > 1)
        cname = argv[1];
    else
        cname = (TEXT *)"ibmcpc";
    if(argc > 2)
        outfile = argv[2];
    else
        outfile = (TEXT *)"vctsetup.h";
    /*--------------------------------------------------------------*/
    /*-------------------Setup temporary Locations------------------*/
    /*--------------------------------------------------------------*/
    termptr = (struct termctrl *)vcalloc(1,sizeof(*termptr),vcdebug);
    keyptr = (struct vckeys *)vcalloc(1,sizeof(*keyptr),vcdebug);
    bordptr = (struct BODR *)vcalloc(3,sizeof(*bordptr),vcdebug);
    vcmem(bordptr,&border[0].up,sizeof(*bordptr)*3);
    /*--------------------------------------------------------------*/
    /*-----------------Get Termcap Information----------------------*/
    /*--------------------------------------------------------------*/
    if((termcapbuf = vcalloc(3600,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror("Buffer memory error");
    if((area_begin = vcalloc(1000,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror("Area memory");
    if((names = vcalloc(2000,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror("Error allocating memory");
    empty(termcapbuf,3600);
    empty(area_begin,1000);
    area = area_begin;
    area_end = area+975;
    empty(tname,40);
    if((err=vcgetent(termcapbuf,cname)) != 1)
        terror("Terminal not found");
    cnt = 0;
    tmptr = termcapbuf;
    while(cnt < 39)
        {
        if((*tmptr == ':') || (*tmptr == '\0') || (*tmptr == '\n'))
            break;
        tname[cnt++] = *(tmptr++);
        }
    tname[cnt] = '\0';
    printf("Processing %s\n\r",tname);
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
        if((errptr = vcgetstr(term,&tmptr)) != NULLTEXT)
            {
            tmptr = strtok(tmpbuf,"|");
            while(tmptr != NULLTEXT)
                {
                *tnum = spaddtable(&termptr->table,tmptr,start);
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
        if((errptr = vcgetstr(kload[cnt].tcap,&tmptr)) != NULLTEXT)
            {
            tmptr = strtok(tmpbuf,"|");
            while(tmptr != NULLTEXT)
                {
                *tnum = spaddtable(&termptr->table,tmptr,
                                                 kload[cnt].value);
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
                *(tnum++) = spaddtable(&termptr->table,tmpbuf,kload[cnt].value);
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
        terror("memory error");
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
        if(term[0] > 'Z')
            break;
        }
    lblptr->klblval = -1;
    if(termptr->bs == 1)
        {
        termptr->bc = area;
        *area++ = (TEXT) 8;
        *area++ = '\0';
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
    stgo((struct PRECOMP *)&termptr->cursor.before,termptr->cm);
    stgo((struct PRECOMP *)&termptr->color.before,termptr->ct);
    mvpcloc((struct PRECOMP *)&termptr->cursor.before);
    mvpcloc((struct PRECOMP *)&termptr->color.before);
    addtofile(tname,0,termptr,keyptr,bordptr);
    vcfree(termptr->firstkeylbl,vcdebug);
    /*--------------------------------------------------------------*/
    /*---------------------------Finished---------------------------*/
    /*--------------------------------------------------------------*/
    if(termcapbuf != NULLTEXT)
        vcfree(termcapbuf,vcdebug);
    if(area_begin != NULLTEXT)
        vcfree(area_begin,vcdebug);
    vcfree(termptr,vcdebug);
    vcfree(keyptr,vcdebug);
    vcfree(bordptr,vcdebug);
    if(tmpfil != (FILE *)0)
        vcfclose(tmpfil);
    }

mvpcloc(pc)
struct PRECOMP *pc;
    {
    COUNT size;
    if(pc->before != NULLTEXT)
        {
        size = strlen(pc->before)+1;
        strcpy(area,pc->before);
/*        vcfree(pc->before,NULLTEXT); */
        pc->before = area;
        area += size;
        if(area > area_end)
            terror((TEXT *)"Out of Area");
        }
    if(pc->between != NULLTEXT)
        {
        size = strlen(pc->between)+1;
        strcpy(area,pc->between);
/*        vcfree(pc->between,NULLTEXT); */
        pc->between = area;
        area += size;
        if(area > area_end)
            terror((TEXT *)"Out of Area");
        }
    if(pc->after != NULLTEXT)
        {
        size = strlen(pc->after)+1;
        strcpy(area,pc->after);
/*        vcfree(pc->after,NULLTEXT); */
        pc->after = area;
        area += size;
        if(area > area_end)
            terror((TEXT *)"Out of Area");
        }
    }

addtofile(term,slot,termptr,keyptr,bordptr)
TEXT *term;      /* Name of terminal      */
COUNT slot;      /* Location in directory */
struct termctrl *termptr;
struct vckeys *keyptr;
struct BODR *bordptr;
    {
    TEXT tname[40];    /* Blank terminal name */
    UCOUNT size;       /* Size of buffer      */
    TEXT **tstr;       /* Pointer to point through structure */
    COUNT cnt;         /* Counting variable   */
    COUNT ssize;       /* Size of structure   */
    COUNT *cptr;        /* Count pointer        */
    TEXT *ptr;          /* TEXT pointer         */
    COUNT nbr;          /* Counting variable    */
    FILE *vcfopen();  
    struct KEYLBL *lblptr;
    struct KEYTBLNODE *kptr;
    if(tmpfil == (FILE *)0)
        {
        if( (tmpfil = vcfopen(outfile,VCF_W)) == (FILE *)0)
            terror("Error opening temporary file");
        fprintf(tmpfil,"/* Vitamin C Multi-User Terminal Structures */\n");
        fprintf(tmpfil,"/* For Terminal %s */\n\n",term);
        fprintf(tmpfil,"#define VCTERMDEF\n\n");
        fprintf(tmpfil,"#ifndef vcglobal\n\n");
        fprintf(tmpfil,"extern TEXT vctermarea[];\n"); 
        fprintf(tmpfil,"extern struct KEYLBL vclblarea[];\n");
        fprintf(tmpfil,"extern struct KEYTBLNODE vckeytbl[];\n\n");
        fprintf(tmpfil,"#else\n\n");
        }
    ssize = sizeof(*keyptr) / sizeof(COUNT);
    cptr = &keyptr->esc;
    fprintf(tmpfil,"struct vckeys vckey = \n    {\n    ");
    for(cnt = 0; cnt < ssize-1;cnt++)
        {
        if( cnt && !(cnt % 10))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"%d,",*cptr);
        cptr++;
        }
    fprintf(tmpfil,"%d\n    };\n\n",*cptr);
    ssize = sizeof(*bordptr) / sizeof(COUNT) * 3;
    cptr = &bordptr->up;
    fprintf(tmpfil,"struct BODR border[3] =\n    {\n    ");
    for(cnt = 0; cnt < ssize-1;cnt++)
        {
        if( cnt && !(cnt % 10))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"%d,",*cptr);
        cptr++;
        }
    fprintf(tmpfil,"%d\n    };\n\n",*cptr);
    ssize = area - area_begin;
    ptr = area_begin;
    fprintf(tmpfil,"TEXT vctermarea[%d] = \n    {\n    ",ssize);
    for(cnt = 0; cnt < ssize-1;cnt++)
        {
        if( cnt && !(cnt % 20))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"%d,",(COUNT)(*ptr));
        ptr++;
        }
    fprintf(tmpfil,"%d\n    };\n\n",(COUNT)(*ptr));
    fprintf(tmpfil,"struct termctrl vcterm = \n    {\n    ",ssize);
    if(termptr->tmname != NULLTEXT)
        size = termptr->tmname - area_begin;
    else
        size = 65535;
    fprintf(tmpfil,"(TEXT *)%u,\n    ",size);
    ssize = NUMNUMBERS;
    cptr = &termptr->rows;
    for(cnt = 0; cnt < ssize;cnt++)
        {
        if( cnt && !(cnt % 10))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"%d,",*cptr);
        cptr++;
        }
    fprintf(tmpfil,"\n    ");
    tstr = &termptr->ae;
    ssize = NUMSTRINGS;
    for(cnt = 0;cnt < ssize;cnt++)
        {
        if((*tstr) != NULLTEXT)
            size = (*tstr) - area_begin;
        else
            size = 65535;
        if( cnt && !(cnt % 5))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"(TEXT *)%u,",size);
        tstr++;
        }
    fprintf(tmpfil,"\n    (struct KEYTBLNODE *)0,\n    ");
    tstr = &termptr->cursor.before;
    ssize = NUMPRECOMP;
    for(cnt = 0;cnt < ssize;cnt++)
        {
        if((*tstr) != NULLTEXT)
            size = (*tstr) - area_begin;
        else
            size = 65535;
        fprintf(tmpfil,"(TEXT *)%u,",size);
        tstr++;
        }
    cptr = &termptr->cursor.col_first;
    for(cnt = 0; cnt < 5;cnt++)
        {
        if( cnt && !(cnt % 10))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"%d,",*cptr);
        cptr++;
        }
    fprintf(tmpfil,"\n    ");
    tstr = &termptr->color.before;
    ssize = NUMPRECOMP;
    for(cnt = 0;cnt < ssize;cnt++)
        {
        if((*tstr) != NULLTEXT)
            size = (*tstr) - area_begin;
        else
            size = 65535;
        fprintf(tmpfil,"(TEXT *)%u,",size);
        tstr++;
        }
    cptr = &termptr->color.col_first;
    for(cnt = 0; cnt < 5;cnt++)
        {
        if( cnt && !(cnt % 10))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"%u,",*cptr);
        cptr++;
        }
    fprintf(tmpfil,"\n    (struct KEYLBL *)0,\n    ");
    ssize = NUMSPECIAL;
    tstr = &termptr->sp0on;
    for(cnt = 0;cnt < ssize-1;cnt++)
        {
        if((*tstr) != NULLTEXT)
            size = (*tstr) - area_begin;
        else
            size = 65535;
        if( cnt && !(cnt % 5))
            fprintf(tmpfil,"\n    ");
        fprintf(tmpfil,"(TEXT *)%u,",size);
        tstr++;
        }
    if((*tstr) != NULLTEXT)
        size = (*tstr) - area_begin;
    else
        size = 65535;
    fprintf(tmpfil,"(TEXT *)%u\n    };\n\n",size);
    cnt = 0;
    lblptr = termptr->firstkeylbl;
    while(lblptr->klblval != -1)
        {
        cnt++;
        lblptr++;
        }
    ssize = cnt;
    lblptr = termptr->firstkeylbl;
    fprintf(tmpfil,"struct KEYLBL vclblarea[%d] = \n    {\n    ",ssize+1);
    for(cnt = 0; cnt < ssize;cnt++)
        {
        if( cnt && !(cnt % 4))
            fprintf(tmpfil,"\n    ");
        if(lblptr->klblptr != NULLTEXT)
            size = lblptr->klblptr - area_begin;
        else
            size = 65535;
        fprintf(tmpfil,"%u,",lblptr->klblval);
        fprintf(tmpfil,"(TEXT *)%d,",size);
        lblptr++;
        }
    if( cnt && !(cnt % 4))
        fprintf(tmpfil,"\n    ");
    fprintf(tmpfil,"%u,",65535);
    fprintf(tmpfil,"(TEXT *)%u\n    };\n\n",65535);
    ssize = sizeof(struct KEYTBLNODE);
    nbr = (tblnext - tblstart) / ssize;
    kptr = (struct KEYTBLNODE *)tblstart;
    fprintf(tmpfil,"struct KEYTBLNODE vckeytbl[%d] = \n    {\n    ",nbr+1);
    for(cnt = 0; cnt < nbr;cnt++)
        {
        fprintf(tmpfil,"%d,",kptr->key);
        fprintf(tmpfil,"%d,",kptr->val);
        if(kptr->nxtkey != (struct KEYTBLNODE *)0)
            size = (COUNT) ((TEXT *)kptr->nxtkey - tblstart) / ssize;
        else
            size = 65535;
        fprintf(tmpfil,"(struct KEYTBLNODE *)%u,",size);
        if(kptr->othkey != (struct KEYTBLNODE *)0)
            size = (COUNT) ((TEXT *)kptr->othkey - tblstart) / ssize;
        else
            size = 65535;
        fprintf(tmpfil,"(struct KEYTBLNODE *)%u,\n    ",size);
        kptr++;
        }        
    size = 65535;
    fprintf(tmpfil,"%u,",size);
    fprintf(tmpfil,"%u,",size);
    fprintf(tmpfil,"(struct KEYTBLNODE *)%u,",size);
    fprintf(tmpfil,"(struct KEYTBLNODE *)%u\n    };\n\n",size);
    fprintf(tmpfil,"#endif\n");
    }

COUNT spaddtable(node,str,value)
struct KEYTBLNODE **node;
TEXT *str;
COUNT value;
    {
    TEXT *spalloc();
    struct KEYTBLNODE *newnode,*next;
    COUNT key;
#ifdef VCDEBUG
    vcdebug = "spaddtable:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    key = *str;
    if(key == 0xff)
        key = 0x100;
    if(*node == (struct KEYTBLNODE *) 0)
        {
        if( (newnode = (struct KEYTBLNODE *) spalloc(1,sizeof(**node),
                                     vcdebug)) == (struct KEYTBLNODE *)0)
            {
            vcerror=NODEMEM;
            return(-1);
            }
        *node = (struct KEYTBLNODE *) newnode;
        newnode->key = key;
        str++;
        if(*str == '\0')
            {
            newnode->val = value;
            return(value);
            }
        else
            return(spaddtable(&newnode->nxtkey,str,value));
        }
    else
        {
        next = *node;
        while( (next->key != key) && (next->othkey != 
                                            (struct KEYTBLNODE *)0) )
            next = next->othkey;
        if(next->key == key)
            {
            str++;
            if(*str == '\0')
                {
                if(next->val)
                    return(next->val);
                else
                    return(next->val = value);
                }
            else
                return(spaddtable(&next->nxtkey,str,value));
            }
        else
            return(spaddtable(&next->othkey,str,value));
        }
    }

TEXT *spalloc(size,amount,msg)
UCOUNT size;
UCOUNT amount;
TEXT *msg;
    {
    TEXT *tblcur;
    TEXT *vcalloc();
    if(tblstart == NULLTEXT)
        {
        tblstart = vcalloc(1,tblsize,vcdebug);
        tblnext = tblstart;
        }
    tblcur = tblnext;
    tblnext = tblnext + (size * amount);
    if(tblnext > (tblstart + tblsize))
        {
        printf("Out of Table Space\n");
        exit(0);
        }
    return(tblcur);
    }

