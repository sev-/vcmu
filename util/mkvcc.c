/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .2 on 8/31/90 at 23:24:48
*
*   Name            mktcc.c  --  terminal compile program
*
*   Description     This function compiles /etc/termcap.vc text 
*                   file producing /etc/termcap.vcc compiled 
*                   terminal program
*
*   Return Value    Returns -1 if error
*
**/

#define VCERROR_DEFS
#include <vcstdio.h>
#include <vctcap.h>

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
    TEXT *names,*cname,*names_begin,tname[40],*strtok();
    COUNT more;
    VOID dftgraph();
#ifdef VCDEBUG
    vcdebug = "tcompile:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    if(argc > 1)
        outfile = argv[1];
    else
        outfile = (TEXT *)"termcap.vcc";
    vcstart(0);
    /*--------------------------------------------------------------*/
    /*-------------------Setup temporary Locations------------------*/
    /*--------------------------------------------------------------*/
    termptr = (struct termctrl *)vcalloc(1,sizeof(*termptr),vcdebug);
    keyptr = (struct vckeys *)vcalloc(1,sizeof(*keyptr),vcdebug);
    bordptr = (struct BODR *)vcalloc(2,sizeof(*bordptr),vcdebug);
    /*--------------------------------------------------------------*/
    /*-----------------Get Termcap Information----------------------*/
    /*--------------------------------------------------------------*/
    if((termcapbuf = vcalloc(3600,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror("Buffer memory error");
    if((area_begin = vcalloc(1000,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror("Area memory");
    if((names = vcalloc(2000,sizeof(TEXT),vcdebug)) == NULLTEXT)
        terror("Error allocating memory");
    vcgetnent(names,2000);
    names_begin = names;
    cname = strtok(names," \0");
    more = total_entries;
    while(more)
        {
        cname += strlen(cname) + 1;
        if( (cname = strtok(cname," \0")) == NULLTEXT)
            break;
        empty(termcapbuf,3600);
        empty(area_begin,1000);
        if(tblstart != NULLTEXT)
            {
            termptr->table = (struct KEYTBLNODE *) 0;
            vcfree(tblstart,vcdebug);
            tblstart = NULLTEXT;
            }
        area = area_begin;
        area_end = area+975;
        empty(tname,40);
        if((err=vcgetent(termcapbuf,cname)) != 1)
            continue;
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
        dftgraph(&bordptr->up);
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
            if(lblend == lblptr)
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
        stgo((struct PRECOMP *)&termptr->cursor.before,termptr->cm);
        stgo((struct PRECOMP *)&termptr->color.before,termptr->ct);
        addtofile(tname,total_entries-more,termptr,keyptr,bordptr);
        delpcloc((struct PRECOMP *)&termptr->cursor.before);
        delpcloc((struct PRECOMP *)&termptr->color.before);
        dsorttbl();
        termptr->cursor.before = NULLTEXT;
        termptr->cursor.between = NULLTEXT;
        termptr->cursor.after = NULLTEXT;
        termptr->color.before = NULLTEXT;
        termptr->color.between = NULLTEXT;
        termptr->color.after = NULLTEXT;
        vcfree(termptr->firstkeylbl,vcdebug);
        more--;
        }

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
    vcfree(names_begin,vcdebug);
    if(tmpfil != (FILE *)0)
        vcfclose(tmpfil);
    }

delpcloc(pc)
struct PRECOMP *pc;
    {
    if(pc->before != NULLTEXT)
        {
        vcfree(pc->before,NULLTEXT);
        return(0);
        }
    if(pc->between != NULLTEXT)
        {
        vcfree(pc->between,NULLTEXT);
        return(0);
        }
    if(pc->after != NULLTEXT)
        {
        vcfree(pc->after,NULLTEXT);
        return(0);
        }
    }

addtofile(term,slot,termptr,keyptr,bordptr)
TEXT *term;      /* Name of terminal      */
COUNT slot;      /* Location in directory */
struct termctrl *termptr;
struct vckeys *keyptr;
struct BODR *bordptr;
    {
    TEXT template[9];  /* temporary file name */
    LONG lcnt;         /* Possible date       */
    COUNT magic = 975; /* Magic number        */
    TEXT tname[40];    /* Blank terminal name */
    LONG ofset;        /* Offset into code    */
    UCOUNT size;       /* Size of buffer      */
    TEXT **tstr;       /* Pointer to point through structure */
    COUNT cnt;         /* Counting variable   */
    COUNT ssize;       /* Size of structure   */
    FILE *vcfopen();  
    struct KEYLBL *lblptr;
    struct KEYTBLNODE *kptr;
    if(tmpfil == (FILE *)0)
        {
        strcpy(template,"vcXXXXXX");
        mktemp(template);
        if( (tmpfil = vcfopen(outfile /* template */,VCF_WB)) == (FILE *)0)
            terror("Error opening temporary file");
        fwrite(&magic,sizeof(COUNT),1,tmpfil);
        lcnt = 1l;
        fwrite(&lcnt,sizeof(LONG),1,tmpfil);
        cnt = total_entries+1;
        fwrite(&cnt,sizeof(COUNT),1,tmpfil);
        headsize = ftell(tmpfil);
        empty(tname,40);
        dirsize = 40 + sizeof(LONG);
        while(cnt--)
            {
            fwrite(tname,sizeof(TEXT),40,tmpfil);
            fwrite(&ofset,sizeof(LONG),1,tmpfil);
            }
        nextloc = ftell(tmpfil);
        }
    lcnt = headsize + (slot * dirsize);
    fseek(tmpfil,lcnt,0);
    fwrite(term,sizeof(TEXT),40,tmpfil);
    fwrite(&nextloc,sizeof(LONG),1,tmpfil);
    fseek(tmpfil,nextloc,0);
    fwrite(keyptr,sizeof(*keyptr),1,tmpfil);
    fwrite(bordptr,sizeof(*bordptr),2,tmpfil);
    fwrite(&termptr->rows,sizeof(COUNT),NUMNUMBERS,tmpfil);
    size = area - area_begin;
    fwrite(&size,sizeof(COUNT),1,tmpfil);
    fwrite(area_begin,sizeof(TEXT),size,tmpfil);
    if(termptr->tmname != NULLTEXT)
        size = termptr->tmname - area_begin;
    else
        size = 65535;
    fwrite(&size,sizeof(COUNT),1,tmpfil);
    tstr = &termptr->ae;
    cnt = NUMSTRINGS;
    while(cnt--)
        {
        if((*tstr) != NULLTEXT)
            size = (*tstr) - area_begin;
        else
            size = 65535;
        fwrite(&size,sizeof(COUNT),1,tmpfil);
        tstr++;
        }
    cnt = NUMSPECIAL;
    tstr = &termptr->sp0on;
    while(cnt--)
        {
        if((*tstr) != NULLTEXT)
            size = (*tstr) - area_begin;
        else
            size = 65535;
        fwrite(&size,sizeof(COUNT),1,tmpfil);
        tstr++;
        }
    tstr = &termptr->cursor.before;
    cnt = NUMPRECOMP;
    while(cnt--)
        {
        if(*tstr != NULLTEXT)
            {
            size = strlen(*tstr)+1;
            fwrite(&size,sizeof(COUNT),1,tmpfil);
            fwrite(*tstr,sizeof(TEXT),size,tmpfil);
            }
        else
            {
            size = 65535;
            fwrite(&size,sizeof(COUNT),1,tmpfil);
            }
        tstr++;
        }
    fwrite(&termptr->cursor.col_first,sizeof(COUNT),5,tmpfil);
    tstr = &termptr->color.before;
    cnt = NUMPRECOMP;
    while(cnt--)
        {
        if((*tstr) != NULLTEXT)
            {
            size = strlen(*tstr)+1;
            fwrite(&size,sizeof(COUNT),1,tmpfil);
            fwrite(*tstr,sizeof(TEXT),size,tmpfil);
            }
        else
            {
            size = 65535;
            fwrite(&size,sizeof(COUNT),1,tmpfil);
            }
        tstr++;
        }
    fwrite(&termptr->color.col_first,sizeof(COUNT),5,tmpfil); 
    cnt = 0;
    lblptr = termptr->firstkeylbl;
    while(lblptr->klblval != -1)
        {
        cnt++;
        lblptr++;
        }
    fwrite(&cnt,sizeof(COUNT),1,tmpfil);
    lblptr = termptr->firstkeylbl;
    while(cnt--)
        {
        if(lblptr->klblptr != NULLTEXT)
            size = lblptr->klblptr - area_begin;
        else
            size = 65535;
        fwrite(&lblptr->klblval,sizeof(COUNT),1,tmpfil);
        fwrite(&size,sizeof(COUNT),1,tmpfil);
        lblptr++;
        }
    ssize = sizeof(struct KEYTBLNODE);
    cnt = (tblnext - tblstart) / ssize;
    fwrite(&cnt,sizeof(COUNT),1,tmpfil);
    kptr = (struct KEYTBLNODE *)tblstart;
    while(cnt--)
        {
        fwrite(&kptr->key,sizeof(COUNT),2,tmpfil);
        if(kptr->nxtkey != (struct KEYTBLNODE *)0)
            size = (COUNT) ((TEXT *)kptr->nxtkey - tblstart) / ssize;
        else
            size = 65535;
        fwrite(&size,sizeof(COUNT),1,tmpfil);
        if(kptr->othkey != (struct KEYTBLNODE *)0)
            size = (COUNT) ((TEXT *)kptr->othkey - tblstart) / ssize;
        else
            size = 65535;
        fwrite(&size,sizeof(COUNT),1,tmpfil);
        kptr++;
        }        
    nextloc = ftell(tmpfil);
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

COUNT vcgetnent(buf,size)
TEXT *buf;          /* Buffer to terminal names                     */
COUNT size;
    {
    FILE *vcfopen();
    TEXT *result,*bufptr,*tmpptr;
    TEXT *strchr(),*strsset(),*getenv();
    TEXT *bptr,*ptr;
    LONG floc;
    FILE *tcapfil;
    TEXT *endbuf;
    TEXT *vcalloc();
#ifdef VCDEBUG
    vcdebug = "vcgetnent:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    total_entries = 0;
    strcpy(buf,"VC ");
    ptr = buf+3;
    endbuf = buf+size-4;
    strcpy(pathbuf,"/etc/termcap.vc");
    if((tmpptr = getenv("VCTERMCAP")) != NULLTEXT)
        strcpy(pathbuf,tmpptr);
    bufptr = vcalloc(210,sizeof(TEXT),vcdebug);
    if((tcapfil = vcfopen(pathbuf,VCF_R)) == (FILE *)0)
        terror("Cannot open termcap");
    while((result = (TEXT *)fgets(bufptr,210,tcapfil)) != NULLTEXT)
        {
        bptr = bufptr;
        while( (*bptr <= ' ') || (*bptr > 'z') )
            {
            if((*bptr == '\n') || (*bptr == '\0') || (*bptr == '\t'))
                break;
            bptr++;
            }
        if( (*bptr == '#') || (*bptr == ':') || (*bptr == '\n') || 
            (*bptr == '\0') || (*bptr == '\t'))
            continue;
        while( (*bptr != ':') && (*bptr != '|') && (*bptr != '\n') && 
               (*bptr != '\0') && (ptr < endbuf))
            *(ptr++) = *(bptr++);
        total_entries++;
        *(ptr++) = ' ';
        *(ptr+1) = '\0';
        if(ptr >= endbuf)
            break;
        }
    vcfree(bufptr,vcdebug);
    fclose(tcapfil);
    return(1);    
    }

struct BODR dftbord[3] =
    {
    0x7c,           /* Character to Print Up the Screen (GV)        */
    0x3d,           /* Character to Print Across the Screen (GH)    */
    0x7c,           /* Top Left Character               (G2)        */
    0x7c,           /* Top Right Character              (G1)        */
    0x7c,           /* Bottom Left Character            (G3)        */
    0x7c,           /* Bottom Right Character           (G4)        */
    0x7c,           /* Merge with Left Side Character   (GL)        */
    0x7c,           /* Merge with Right Side Character  (GR)        */
    0x3d,           /* Merge with Bottom Character      (GU)        */
    0x3d,           /* Merge with Top Character         (GD)        */
    0x7c,           /* Middle Intersection              (GC)        */
    0,              /* Side Across Character            (GA)        */
    0,              /* Bottom up Character              (GB)        */
    0,              /* Scroll Side Character            (GF)        */
    0,              /* Scroll Bottom Character          (GI)        */
    0,              /* Scroll Top Character             (GJ)        */
    0,              /* Scroll Bottom Character          (GK)        */
    0,              /* Scroll Left Character            (GM)        */
    0,              /* Scroll Right Character           (GN)        */
    0x3e,           /* Scroll Right Current Location Char  (GO)     */
    0,              /* Scroll Bottom Current Location Char (GP)     */
    0x7c,           /* Character to Print Up the Screen    (gv)     */
    0x3d,           /* Character to Print Across the Screen    (gh) */
    0x7c,           /* Top Left Character                  (g2)     */
    0x7c,           /* Top Right Character                 (g1)     */
    0x7c,           /* Bottom Left Character               (g3)     */
    0x7c,           /* Bottom Right Character              (g4)     */
    0x7c,           /* Merge with Left Side Character      (gl)     */
    0x7c,           /* Merge with Right Side Character     (gr)     */
    0x3d,           /* Merge with Bottom Character         (gu)     */
    0x3d,           /* Merge with Top Character            (gd)     */
    0x7c,           /* Middle Intersection                 (gc)     */
    0,              /* Side Across Character               (ga)     */
    0,              /* Bottom up Character                 (gb)     */
    0,              /* Scroll Side Character               (gf)     */
    0,              /* Scroll Bottom Character             (gi)     */
    0,              /* Scroll Top Character                (gj)     */
    0,              /* Scroll Bottom Character             (gk)     */
    0,              /* Scroll Left Character               (gm)     */
    0,              /* Scroll Right Character              (gn)     */
    0x3e,           /* Scroll Right Current Location Char     (go)  */
    0,              /* Scroll Bottom Current Location Char    (gp)  */
    0x7c,           /* Character to Print Up the Screen             */
    0x3d,           /* Character to Print Across the Screen         */
    0x7c,           /* Top Left Character                           */
    0x7c,           /* Top Right Character                          */
    0x7c,           /* Bottom Left Character                        */
    0x7c,           /* Bottom Right Character                       */
    0x7c,           /* Merge with Left Side Character               */
    0x7c,           /* Merge with Right Side Character              */
    0x3d,           /* Merge with Bottom Character                  */
    0x3d,           /* Merge with Top Character                     */
    0x7c,           /* Middle Intersection                          */
    0,              /* Side Across Character                        */
    0,              /* Bottom up Character                          */
    0,              /* Scroll Side Character                        */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Top Character                         */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Left Character                        */
    0,              /* Scroll Right Character                       */
    0x3e,           /* Scroll Right Current Location Char           */
    0               /* Scroll Bottom Current Location Char          */
    };

VOID dftgraph(bp)
struct BODR *bp;
    {
    COUNT length;
    length = sizeof(struct BODR) * 2;
    vcmem(bp,&dftbord[0].up,length);
    }
