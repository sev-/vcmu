/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:17
*
*   Name            vclint.h  --  
*
*   Description     Functions lint file
*
*
**/

#ifndef VCSTRIP
extern  COUNT accept(TEXT *str,TEXT *pic);
extern  COUNT addpic(COUNT pic,PFI pfunc);
extern  COUNT addtable(struct KEYTBLNODE **node,TEXT *str,COUNT value);
extern  COUNT addwdef(TEXT *name,TEXT *style,TEXT *title,TEXT *rtitle,TEXT *ltitle,TEXT *btitle,COUNT ur,COUNT uc,COUNT lr,COUNT lc,COUNT wid,COUNT dep,COUNT smer,COUNT bmer);
extern  COUNT addwstyle(TEXT *nam,COUNT ctrl,COUNT fch,COUNT bd,COUNT bg,COUNT say,COUNT get,COUNT nget,COUNT tit,COUNT rtit,COUNT ltit,COUNT btit,COUNT stat);
extern  COUNT adtoi(TEXT *str);
extern  COUNT ahtoi(TEXT *str);
extern  COUNT allcaps(TEXT *str);
extern  COUNT aotoi(TEXT *str);
extern  COUNT askmsg(TEXT *tit,TEXT *msg,COUNT flag);
extern  COUNT setaskmsg(COUNT topr,COUNT topc,COUNT botr,COUNT botc,COUNT color,COUNT ctrl,TEXT *style);
extern  COUNT at(COUNT row,COUNT col);
extern  COUNT atsay(COUNT row,COUNT col,TEXT *fld);
extern  COUNT atsayget(COUNT row,COUNT col,TEXT *sfld,TEXT *gfld,TEXT *pic);
extern  COUNT atsaynum(COUNT row,COUNT col,TEXT *numptr,TEXT *pic,COUNT type);
extern  COUNT atsaytyp(COUNT row,COUNT col,TEXT *numptr,TEXT *pic,COUNT type,COUNT attr);
extern  COUNT bell(VOID );
extern  COUNT blank(TEXT *str);
extern  COUNT blockkey(COUNT key);
extern  COUNT box(COUNT up,COUNT lf,COUNT lo,COUNT rt,COUNT type,COUNT attr);
extern  COUNT bufkdy(VOID );
extern  COUNT buildhlp(TEXT *filnam,struct HLP_STR *hndx);
extern  COUNT ckspattr(COUNT attr);
extern  UCOUNT attr2bit(COUNT attr);
extern  COUNT ckspterm(struct termctrl *termptr);
extern  COUNT colormon(VOID );
extern  COUNT equip(VOID );
extern  COUNT dayofwk(TEXT *str);
extern  TEXT *day_name(COUNT n);
extern  COUNT delbox(COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,COUNT attr);
extern  COUNT delpic(COUNT pic);
extern  TEXT *dflthlp(TEXT *str);
extern  COUNT dkeyval(COUNT val);
extern  COUNT pushknode(struct KEYTBLNODE *node);
extern  struct KEYTBLNODE *popknode(VOID );
extern  COUNT xdkeyval(struct KEYTBLNODE *node,COUNT val);
extern  COUNT dsorttbl(VOID );
extern  COUNT xdeltable(struct KEYTBLNODE *node);
extern  COUNT elapstim(TEXT *start,TEXT *end);
extern  COUNT empty(TEXT *str,COUNT len);
extern  COUNT erabox(COUNT up,COUNT lf,COUNT lo,COUNT rt);
extern  COUNT eraeol(VOID );
extern  COUNT eraeos(VOID );
extern  COUNT erase(VOID );
extern  COUNT evalpic(COUNT c);
extern  COUNT exitkey(COUNT ascii);
extern  COUNT fdternam(TEXT *buffer,TEXT *tname);
extern  WPTR filtowdo(TEXT *fnam);
extern  TEXT *findset(TEXT *str2);
extern  COUNT fromjul(long jul,TEXT *outstr);
extern  COUNT gbufkey(VOID );
extern  COUNT getdate(TEXT *dat);
extern  TEXT *getlabel(struct KEYLBL *lblptr,COUNT key);
extern  COUNT getone(VOID );
extern  COUNT vcpushkey(COUNT ans);
extern  COUNT gettime(TEXT *tim);
extern  COUNT gettype(TEXT *pic);
extern  WDEF *getwdef(TEXT *name);
extern  WSTYLE *getwstyle(TEXT *name);
extern  TEXT *gtname(TEXT *tbuf,COUNT *len);
extern  COUNT hasdata(TEXT *fld,TEXT *pic);
extern  COUNT haveauth(COUNT authlevel,COUNT task);
extern  COUNT hclose(VOID );
extern  COUNT helpkey(COUNT ascii);
extern  COUNT hfind(TEXT *keyword);
extern  COUNT hload(FILE *fp);
extern  COUNT hlpsort(struct HLP_STR *hstru,COUNT siz);
extern  COUNT hopen(TEXT *msgfil,TEXT *ndxfil);
extern  COUNT hprint(WPTR wptr);
extern  COUNT vcin(VOID );
extern  COUNT vcout(TEXT *buf,COUNT nbytes);
extern  COUNT xkeyrdy(VOID );
extern  struct KEYTBLNODE *intable(struct KEYTBLNODE *node,COUNT str,COUNT *value);
extern  COUNT intdate(TEXT *str,COUNT *mo,COUNT *da,COUNT *yr);
extern  COUNT isblank(TEXT *str);
extern  COUNT isexitkey(COUNT key);
extern  COUNT itoap(COUNT number,TEXT *str,COUNT precision);
extern  COUNT keyisblk(COUNT key);
extern  COUNT keyrdy(VOID );
extern  COUNT leapyear(TEXT *str);
extern  TEXT *month_name(COUNT n);
extern  COUNT nocolor(VOID );
extern  COUNT numstrcpy(TEXT *dest,TEXT *srce);
extern  COUNT prnnum(COUNT row,COUNT col,TEXT *fld,TEXT *pic,COUNT attr);
extern  COUNT say(TEXT *str);
extern  COUNT sayseg(WPTR wptr,COUNT r,COUNT c,TEXT *fld,COUNT beg,COUNT width,COUNT attr);
extern  COUNT scrolldn(COUNT up,COUNT lf,COUNT lo,COUNT rt,COUNT n,COUNT atr);
extern  COUNT scrollup(COUNT up,COUNT lf,COUNT lo,COUNT rt,COUNT n,COUNT atr);
extern  COUNT selbar(WPTR wptr,COUNT row,COUNT col,COUNT attr,COUNT width);
extern  COUNT setattr(COUNT mode,COUNT attr);
extern  COUNT setbell(COUNT mode);
extern  PFI sethelp(PFI func);
extern  COUNT sethwdo(COUNT topr,COUNT topc,COUNT botr,COUNT botc,TEXT *title,COUNT ctrl,COUNT depth,COUNT width,COUNT color);
extern  PFI setkeytrap(PFI keyfunc);
extern  PFI setloop(PFI func);
extern  WPTR setswdo(WPTR wptr);
extern  COUNT spfix(VOID );
extern  COUNT sprtnum(TEXT *buf,TEXT *fld,TEXT *pic);
extern  COUNT startstyle(struct STR_WSTYLE *sp,struct STR_WDEF *dp);
extern  COUNT statlin(WPTR wptr,COUNT row,COUNT col,COUNT attr);
extern  COUNT statsay(TEXT *msg,COUNT nattr);
extern  WPTR statwdo(VOID );
extern  COUNT std2attr(UCOUNT attr);
extern  COUNT std2cord(COUNT cord);
extern  COUNT stgo(TEXT *txtpc,TEXT *cm);
extern  TEXT *strsset(TEXT *str1,TEXT *str2);
extern  COUNT systrap(COUNT ich);
extern  TEXT *tallcaps(TEXT *str);
extern  COUNT vcaddrc(COUNT row,COUNT col);
extern  TEXT *vcalloc(UCOUNT amount,UCOUNT size,TEXT *calledby);
extern  COUNT vcalnum(COUNT c);
extern  COUNT vcalpha(COUNT c);
extern  COUNT vcany(COUNT c);
extern  COUNT vca_get(COUNT row,COUNT col,TEXT *buffer,COUNT len);
extern  COUNT vca_put(COUNT row,COUNT col,TEXT *buffer,COUNT len);
extern  COUNT vccsmall(COUNT no);
extern  COUNT vccstart(COUNT no);
extern  COUNT vcctinit(TEXT *useterm);
extern  LONG findtofst(TEXT *term);
extern  COUNT vccurs(COUNT code);
extern  COUNT vcsetcur(COUNT lines);
extern  COUNT vcgetcur(VOID );
extern  COUNT vcdelay(COUNT no);
extern  COUNT vcdelfil(TEXT *nam);
extern  COUNT vcdigit(COUNT c);
extern  TEXT *vcdtos(TEXT *str,double num,COUNT prec);
extern  COUNT vcend(COUNT restore);
extern  COUNT vcfclose(FILE *fp);
extern  COUNT vcfflush(FILE *fptr);
extern  FILE *vcfopen(TEXT *nam,TEXT *mode);
extern  COUNT vcfree(TEXT *location,TEXT *calledby);
extern  COUNT vcgetent(TEXT *buf,TEXT *terminal);
extern  TEXT *vcgetenv(TEXT *buf);
extern  COUNT vcgetflag(TEXT *id);
extern  COUNT vcgetnum(TEXT *id);
extern  TEXT *vcgetstr(TEXT *id,TEXT * *area);
extern  TEXT *vcgoto(struct PRECOMP *pc,COUNT col,COUNT row);
extern  COUNT vchelp(VOID );
extern  TEXT *vcitos(TEXT *str,COUNT num);
extern  COUNT vckeyset(VOID );
extern  COUNT vcpicset(VOID );
extern  TEXT *vcltos(TEXT *str,LONG num,COUNT prec);
extern  COUNT vcmem(TEXT *end,TEXT *start,UCOUNT len);
extern  COUNT vcnap(COUNT time);
extern  COUNT vcnoterm(TEXT *useterm);
extern  TEXT *vcnumfix(TEXT *des,TEXT *org,COUNT siz,COUNT dec);
extern  COUNT vcpeek(COUNT seg,COUNT ofst,TEXT *buf,COUNT bytes);
extern  COUNT vcpoke(COUNT seg,COUNT ofst,TEXT *buf,COUNT bytes);
extern  COUNT vcprokey(COUNT key);
extern  COUNT vcprtchr(TEXT ch);
extern  COUNT vcprtcls(VOID );
extern  COUNT vcprtfls(VOID );
extern  FILE *vcprtopn(TEXT *printer);
extern  COUNT vcprtscr(VOID );
extern  COUNT vcprtstr(TEXT *str);
extern  COUNT vcprtwdo(WPTR wptr,PFI mapfunc);
extern  COUNT vcputc(TEXT ch,COUNT attr);
extern  COUNT vcputpad(TEXT *str,COUNT lines,PFI func);
extern  COUNT vcputs(TEXT *str,COUNT attr);
extern  COUNT vcsdigit(COUNT c);
extern  COUNT vcsmall(COUNT no);
extern  COUNT vcstart(COUNT no);
extern  COUNT vcsystem(TEXT *cmd,COUNT flag,TEXT *msg);
extern  COUNT vctinit(TEXT *useterm);
extern  COUNT vctrap(COUNT input);
extern  COUNT vctsmall(COUNT no);
extern  COUNT vctstart(COUNT no);
extern  COUNT vcustom(COUNT no);
extern  COUNT termsort(VOID );
extern  COUNT terror(TEXT *msg);
extern  COUNT timeadd(TEXT *t1,TEXT *t2);
extern  COUNT timeloc(WPTR wptr,COUNT row,COUNT col,COUNT attr);
extern  COUNT timeloop(VOID );
extern  TEXT *tmppic(TEXT *fld,TEXT picchr);
extern  COUNT tohours(COUNT days,TEXT *hhmmssxx);
extern  LONG tojul(TEXT *sdat);
extern  TEXT *trim(TEXT *str);
extern  COUNT ttinit(VOID );
extern  TEXT *ttrim(TEXT *str);
extern  COUNT unblkkey(COUNT key);
extern  COUNT ungetone(COUNT ans);
extern  COUNT wadjust(WPTR wptr);
extern  COUNT wat(WPTR wptr,COUNT row,COUNT col);
extern  COUNT watsay(WPTR wptr,COUNT row,COUNT col,TEXT *fld);
extern  COUNT wborder(WPTR wptr,COUNT type);
extern  COUNT wbound(WPTR wptr);
extern  COUNT wbox(WPTR wptr,COUNT up,COUNT lf,COUNT lo,COUNT rt,COUNT type,COUNT attr);
extern  COUNT wclose(WPTR wptr);
extern  COUNT wlistdel(WPTR wptr);
extern  COUNT wclr(WPTR wptr,COUNT attr);
extern  COUNT wclrfld(WPTR wptr,COUNT len,COUNT attrb);
extern  COUNT wcols(WPTR wptr);
extern  COUNT wcut(WPTR wptr,COUNT clear,COUNT key);
extern  COUNT wcutout(WPTR wptr);
extern  WPTR wdefinit(TEXT *name,TEXT *style,TEXT *title,TEXT *rtitle,TEXT *ltitle,TEXT *btitle,COUNT ur,COUNT uc,COUNT lr,COUNT lc,COUNT wid,COUNT dep,COUNT smer,COUNT bmer);
extern  WPTR wdefopen(TEXT *wdef);
extern  COUNT wdelbox(WPTR wptr,COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,COUNT attr);
extern  COUNT wdokey(COUNT ascii);
extern  COUNT wdotofil(WPTR wptr,TEXT *fnam);
extern  COUNT werabox(WPTR wptr,COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,COUNT attr);
extern  COUNT weraeol(WPTR wptr,COUNT attr);
extern  COUNT weraeos(WPTR wptr,COUNT attr);
extern  COUNT werase(WPTR wptr,COUNT attr);
extern  COUNT wexpand(WPTR wptr,COUNT *text,COUNT *attr);
extern  COUNT wfandn(WPTR wptr);
extern  COUNT wfanup(WPTR wptr);
extern  COUNT wflip(COUNT toprow,COUNT topcol,COUNT botrow,COUNT botcol);
extern  COUNT wflop(WPTR wptr,COUNT toprow,COUNT topcol,COUNT dth,COUNT wth,COUNT attr);
extern  COUNT whbar(WPTR wp);
extern  COUNT whidden(WPTR wptr);
extern  COUNT whide(WPTR wptr);
extern  COUNT whit(WPTR wptr,COUNT row,COUNT col);
extern  COUNT winit(WPTR wptr);
extern  COUNT winter(WPTR wptr,WPTR wptr2);
extern  COUNT winwdo(WPTR wptr,COUNT row,COUNT col);
extern  TEXT *wloadimg(TEXT *fname);
extern  COUNT wcoord(WPTR wptr,COUNT *ur,COUNT *uc,COUNT *lr,COUNT *lc);
extern  COUNT wctrl(WPTR wptr,COUNT *ctrl,COUNT mode);
extern  COUNT wcurspos(WPTR wptr,COUNT *row,COUNT *col);
extern  TEXT *wmemloc(WPTR wptr);
extern  WPTR winfoptr(WPTR wptr);
extern  COUNT wvirtpos(WPTR wptr,COUNT *ur,COUNT *uc);
extern  COUNT wvirtsiz(WPTR wptr,COUNT *depth,COUNT *width);
extern  COUNT wattr(WPTR wptr,COUNT *bd,COUNT *bg,COUNT *say,COUNT *atg,COUNT *natg,COUNT *tit,COUNT mode);
extern  COUNT wmove(WPTR wptr,COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c);
extern  COUNT wmov_cur(WPTR wptr,COUNT draw);
extern  COUNT woff(VOID );
extern  COUNT won(VOID );
extern  WPTR wopen(COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,TEXT *title);
extern  COUNT wpaste(WPTR wptr,COUNT attr,COUNT key);
extern  COUNT wpickcl(WPTR wptr);
extern  COUNT wpickopn(WPTR wptr);
extern  COUNT wpkarea(COUNT *upr,COUNT *upc,COUNT *lor,COUNT *loc,COUNT mupr,COUNT mupc,COUNT mlor,COUNT mloc,COUNT attr,COUNT bd,COUNT depth,COUNT width,COUNT key);
extern  COUNT wplace_cur(WPTR wptr);
extern  WPTR wprep(VOID );
extern  COUNT wpulldn(WPTR wptr);
extern  COUNT wpullup(WPTR wptr);
extern  COUNT wputattr(WPTR wptr,COUNT attr,COUNT times);
extern  COUNT wputchr(WPTR wptr,COUNT text,COUNT attr);
extern  COUNT wputs(WPTR wptr,TEXT *str,COUNT attrb);
extern  COUNT wrd_scrn(VOID );
extern  COUNT wrefresh(COUNT flag);
extern  COUNT wrestore(WPTR wptr);
extern  COUNT wrows(WPTR wptr);
extern  COUNT wrtb(COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c);
extern  COUNT wrt_scrn(VOID );
extern  TEXT *wsaveimg(TEXT *fname);
extern  COUNT wscrn_blank(VOID );
extern  COUNT wscroll(WPTR wptr,COUNT direction,COUNT amount);
extern  WPTR wselect(WPTR wptr);
extern  WPTR wsetup(TEXT *name,COUNT ctrl,COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,COUNT ch,COUNT bg_atr,COUNT bd_atr,COUNT sy_at,COUNT gt_at,COUNT ngt_at,COUNT ti_at,TEXT *tit,COUNT dth,COUNT wth);
extern  COUNT wshow(WPTR wptr);
extern  COUNT wshuffle(WPTR wptr);
extern  COUNT wsscroll(WPTR wptr,COUNT direction,COUNT no);
extern  COUNT wstack(WPTR wptr);
extern  WPTR wstyleopen(TEXT *style,COUNT ur,COUNT uc,COUNT lr,COUNT lc,TEXT *title);
extern  COUNT wupdate(WPTR wptr);
extern  COUNT wvbar(WPTR wp);
extern  COUNT wwrtdw(WPTR wptr);
extern  COUNT wwrtup(WPTR wptr);
extern  COUNT wwtb(COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,COUNT attr);
extern  COUNT wxatsay(WPTR wptr,COUNT row,COUNT col,TEXT *str,COUNT attr);
extern  WPTR wxopen(COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,TEXT *title,COUNT ctrl,COUNT dth,COUNT wth);
extern  WPTR wxxopen(COUNT up_r,COUNT up_c,COUNT lo_r,COUNT lo_c,TEXT *title,COUNT ctrl,COUNT dth,COUNT wth,COUNT wc,COUNT fch);
extern  COUNT wzoom(WPTR wptr);
extern  COUNT wzoomin(WPTR wptr);
extern  COUNT xatsay(COUNT row,COUNT col,TEXT *str,COUNT attr);
extern  COUNT xerabox(COUNT up,COUNT lf,COUNT lo,COUNT rt,COUNT attr);
extern  COUNT xeraeol(COUNT attr);
extern  COUNT xeraeos(COUNT attr);
extern  COUNT xerase(COUNT attr);
extern  COUNT xgetone(VOID );
#endif

#ifdef VCGET_DEFS
extern  COUNT afld2tmp(GETTABLE *tbl,COUNT flag);
extern  COUNT atget(COUNT row,COUNT col,TEXT *fld,TEXT *pic);
extern  COUNT atgetbox(COUNT ur,COUNT uc,COUNT lr,COUNT lc,COUNT num,COUNT attr);
extern  COUNT atgetc(COUNT row,COUNT col,TEXT *fld,TEXT *pic,COUNT wid,COUNT ctrl,TEXT *lst);
extern  COUNT atgetsay(COUNT row,COUNT col,TEXT *fld,COUNT attr);
extern  COUNT checkset(TEXT *fld,GETTABLE *table);
extern  COUNT clrfld(COUNT len,COUNT attrb);
extern  COUNT clrgets(GETTABLE *tbl);
extern  COUNT clrsays(SAYITEM *snptr);
extern  COUNT clrtbl(GETTABLE *tbl);
extern  COUNT datepost(GETITEM *gi);
extern  COUNT datepre(GETITEM *gi);
extern  COUNT dfvclist(GETTABLE *table);
extern  COUNT fld2tmp(GETITEM *gi,COUNT flag);
extern  COUNT get(TEXT *fld,TEXT *pic);
extern  GETITEM *getalloc(VOID );
extern  COUNT getfld(GETTABLE *table);
extern  COUNT callval(GETTABLE *gt);
extern  GETTABLE *gettblptr(TEXT *nam);
extern  COUNT getsay(GETITEM *gi);
extern  COUNT initblk(GETITEM *gi);
extern  COUNT initbut(GETITEM *gi);
extern  COUNT initchk(GETITEM *gi);
extern  COUNT initcho(GETITEM *gi);
extern  COUNT initlr(GETITEM *gi);
extern  COUNT initrl(GETITEM *gi);
extern  COUNT inpblock(GETTABLE *table);
extern  COUNT inpbuton(GETTABLE *table);
extern  COUNT inpcheck(GETTABLE *table);
extern  COUNT inpchkpic(GETITEM *gi);
extern  COUNT inpchktog(GETITEM *gp,COUNT flag);
extern  COUNT inpchoice(GETTABLE *table);
extern  COUNT intpost(GETITEM *gi);
extern  COUNT intpre(GETITEM *gi);
extern  COUNT lightblk(GETITEM *gi);
extern  COUNT lightbut(GETITEM *gi);
extern  COUNT lightchk(GETITEM *gi);
extern  COUNT lightcho(GETITEM *gi);
extern  COUNT lightlr(GETITEM *gi);
extern  COUNT lightrl(GETITEM *gi);
extern  COUNT longpost(GETITEM *gi);
extern  COUNT longpre(GETITEM *gi);
extern  COUNT ltorinp(GETTABLE *table);
extern  COUNT ltordraw(GETTABLE *table);
extern  COUNT ltorhpass(GETTABLE *table);
extern  COUNT ltorcleft(GETTABLE *table);
extern  COUNT ltorcright(GETTABLE *table);
extern  COUNT ltorbksp(GETTABLE *table);
extern  COUNT ltordel(GETTABLE *table);
extern  COUNT ltorins(GETTABLE *table);
extern  COUNT ltormode(GETTABLE *table,COUNT *more,COUNT *rval);
extern  COUNT ltorblank(GETITEM *gp,COUNT flag);
extern  COUNT vcvalchr(COUNT key);
extern  COUNT ltorichr(GETTABLE *table);
extern  COUNT ltorcls(GETTABLE *table);
extern  COUNT ltordeof(GETTABLE *table);
extern  COUNT mapnum(TEXT *in,TEXT *pic,COUNT *decireal,COUNT *deciscrn,COUNT *hassign);
extern  COUNT mapstr(GETITEM *gi);
extern  COUNT numpost(GETITEM *gi);
extern  COUNT numpre(GETITEM *gi);
extern  COUNT oldpre(GETITEM *gi);
extern  COUNT picok(TEXT ch,TEXT pic);
extern  COUNT readgets(VOID );
extern  COUNT rtolinp(GETTABLE *table);
extern  COUNT rtoldraw(GETTABLE *table);
extern  COUNT rtolhpass(GETTABLE *table);
extern  COUNT rtolflip(GETTABLE *table);
extern  COUNT rtolcleft(GETTABLE *table);
extern  COUNT rtolcright(GETTABLE *table);
extern  COUNT rtolbksp(GETTABLE *table);
extern  COUNT rtoldel(GETTABLE *table);
extern  COUNT rtolblank(GETITEM *gp);
extern  COUNT rtolichr(GETTABLE *table);
extern  COUNT rtolcls(GETTABLE *table);
extern  COUNT rtolsign(GETTABLE *table);
extern  COUNT rtolrins(GETTABLE *table);
extern  COUNT rtolldel(GETTABLE *table);
extern  COUNT rtolprec(TEXT *fld);
extern  COUNT sayget(SAYITEM *si);
extern  COUNT seqgetstd(GETTABLE *gtp);
extern  COUNT sintpost(GETITEM *gi);
extern  COUNT sintpre(GETITEM *gi);
extern  COUNT snumpost(GETITEM *gi);
extern  COUNT snumpre(GETITEM *gi);
extern  COUNT strpost(GETITEM *gi);
extern  COUNT strpre(GETITEM *gi);
extern  GETTABLE *tblalloc(TEXT *symnam,COUNT ctrl,PFI seq);
extern  GETITEM *vcfld(COUNT row,COUNT col,TEXT *fld,TEXT *pic,COUNT opt,COUNT ctrl,TEXT *nam);
extern  COUNT vcfldblk(GETITEM *gi);
extern  GETITEM *vcfldfnd(GETTABLE *tbl,TEXT *lbl,COUNT nbr,COUNT flag);
extern  TEXT *vcfldget(GETTABLE *tbl,TEXT *name,COUNT flag);
extern  GETITEM *vcfldgo(GETTABLE *tbl,TEXT *name,COUNT ofst);
extern  TEXT *vcfldiget(GETTABLE *tbl,COUNT id,COUNT flag);
extern  GETITEM *vcfldigo(GETTABLE *tbl,COUNT id,COUNT ofst);
extern  COUNT vcfldiinput(GETTABLE *table,COUNT id,COUNT ofset);
extern  COUNT vcfldinput(GETTABLE *table,TEXT *fld,COUNT ofset);
extern  TEXT *vcfldiput(GETTABLE *tbl,COUNT id,TEXT *val,COUNT flag);
extern  TEXT *vcfldput(GETTABLE *tbl,TEXT *name,TEXT *val,COUNT flag);
extern  COUNT vcsaveds(GETTABLE *gt);
extern  GETTABLE *vctblsel(GETTABLE *tbl);
extern  COUNT vctoreal(GETITEM *gi);
extern  GETITEM *vcxfld(COUNT row,COUNT col,TEXT *fld,TEXT *pic,COUNT opt,COUNT ctrl,TEXT *nam,PFI val,TEXT *msg);
extern  GETITEM *vcxxfld(COUNT row,COUNT col,TEXT *fld,TEXT *pic,COUNT opt,COUNT ctrl,TEXT *nam,PFI val,TEXT *msg,TEXT *help,COUNT width,TEXT *
extern  COUNT valdate(TEXT *str);
extern  GETITEM *valtable(GETTABLE *table);
extern  COUNT xaccept(TEXT *str,TEXT *pic,COUNT tblval);
extern  COUNT xatget(COUNT row,COUNT col,TEXT *fld,TEXT *pic,PFI val,TEXT *msg,TEXT *help,COUNT act,COUNT nact);
extern  COUNT xatgetc(COUNT row,COUNT col,TEXT *fld,TEXT *pic,PFI val,TEXT *msg,TEXT *help,COUNT act,COUNT nact,COUNT width,COUNT ctrl,TEXT *lst);
extern  COUNT xatgetsay(GETTABLE *tblptr,WPTR wptr,COUNT row,COUNT col,TEXT *fld,COUNT attr,COUNT lr,COUNT lc,COUNT control);
extern  SAYITEM *getsayalloc(VOID );
extern  COUNT xreadgets(GETTABLE *gptr);
extern  COUNT xxatget(GETTABLE *tp,WPTR wp,COUNT row,COUNT col,TEXT *fld,TEXT *pic,PFI val,TEXT *msg,TEXT *help,COUNT act,COUNT nact);
#endif

#ifdef SEL_DEFS
extern  SELSET *addselitm(SELSET *list,TEXT *display,TEXT *value);
extern  SELSET *aloselitm(VOID );
extern  SELSET *bldset(TEXT **array);
extern  SELSET *bldxset(TEXT **array);
extern  SELSET *delselitm(SELSET *list,SELSET *selitem);
extern  COUNT delselset(SELSET *list);
extern  SELSET *getselitm(SELSET *list,TEXT *display,TEXT *value);
extern  COUNT lstsellst(SELSET *list);
#endif

#ifdef VCPRO_DEFS
extern  COUNT addprokey(COUNT key,PFI func,TEXT *aux);
extern  COUNT delprokey(COUNT key);
extern  VCPROKEY *scnprokey(COUNT key);
#endif

#ifdef VCM_DEFS
extern  COUNT addmstyle(TEXT *name,COUNT mnustyle,COUNT width,COUNT norm,COUNT bar,COUNT unav,COUNT bord,COUNT permlvl);
extern  COUNT chgmstyle(MENUSTYLE *styleptr,TEXT *name,COUNT mnustyle,COUNT width,COUNT norm,COUNT bar,COUNT unav,COUNT bord,COUNT permlvl);
extern  COUNT delmenu(VCMENU *mptr);
extern  COUNT delmitem(VCMENU *mnuptr,TEXT *itmnam);
extern  COUNT delmstyle(TEXT *stylename);
extern  COUNT dracuritm(VCMENU *m);
extern  COUNT findavl(VCMENU *m);
extern  MENUITEM *getmnuitm(VCMENU *mnuptr,TEXT *itmnam);
extern  VCMENU *getmnuptr(TEXT *menunam);
extern  MENUSTYLE *getmstyle(TEXT *name);
extern  COUNT initmenu(SSTYLES *style,SMENUS *menu,SMENUITEMS *item);
extern  COUNT lstmstyle(VOID );
extern  COUNT menu(TEXT *name);
extern  MENUITEM *menuitem(VCMENU *menuptr,TEXT *item,PFI func,TEXT *parm,TEXT *stat,COUNT ctrl);
extern  VCMENU *menunew(COUNT row,COUNT col,TEXT *mnunam,TEXT *hlpkey,TEXT *style);
extern  MENUITEM *menuxitem(VCMENU *menuptr,TEXT *item,TEXT *keynam,COUNT keynum,PFI func,TEXT *parm,TEXT *stat,TEXT *hlpkey,COUNT ctrl);
extern  VCMENU *menuxnew(COUNT row,COUNT col,COUNT width,TEXT *mnunam,COUNT style,COUNT norm,COUNT bar,COUNT unav,COUNT bord,COUNT permis,TEXT 
extern  MENUITEM *menuxxitem(VCMENU *menuptr,TEXT *item,TEXT *keynam,COUNT keynum,PFI func,TEXT *parm,TEXT *stat,TEXT *hlpkey,COUNT ctrl,COUNT 
extern  COUNT mnukey(VCMENU *m);
extern  COUNT nextmitm(VCMENU *m);
extern  COUNT prevmitm(VCMENU *m);
extern  COUNT vcmenu(VCMENU *m);
extern  COUNT vcmselbar(VCMENU *m,COUNT mode);
extern  COUNT toglchkvar(VCMENU *m);
#endif
