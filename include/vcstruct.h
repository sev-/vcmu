/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 9/2/90 at 14:44:37
*
*   Name            vcstruct.h  --  Structure Definations
*
*   Description
*
*
**/

/*------------------------------------------------------------------*/
/*-------------------------Window Structure-------------------------*/
/*------------------------------------------------------------------*/

struct KEYTBLNODE
    {
    COUNT key;       /* Key stored in this node                     */
    COUNT val;       /* Value if match stops here                   */
    struct KEYTBLNODE *nxtkey; /* If match pointer to next level    */
    struct KEYTBLNODE *othkey; /* If no match pointer to same level */
    };

struct WINF
    {
    TEXT *wname;     /* Window Name                                 */
    struct WINF *wdlist;    /* Next Window in order of open         */
    struct WINF *wnext;     /* Next Window down active list         */
    struct WINF *wprevious; /* Previous Window up active list       */
    UCOUNT wctrl;    /* Window Control Byte                         */
    UCOUNT wopt;     /* Window Options Byte                         */
    COUNT upper_r;   /* Upper Right                                 */
    COUNT upper_c;   /* Upper Left                                  */
    COUNT lower_r;   /* Lower Right                                 */
    COUNT lower_c;   /* Lower Left                                  */
    TEXT  fill_ch;   /* Fill Character for Window                   */
    COUNT border_at; /* Border Attribute                            */
    COUNT bg_at;     /* Background Attribute                        */
    COUNT say_at;    /* Print in Window Attribute                   */
    COUNT get_at;    /* Read from Window Attribute                  */
    COUNT nget_at;   /* Non Active get Attribute                    */
    COUNT tit_at;    /* Title Attribute                             */
    COUNT rtit_at;   /* Right Title Attribute                       */
    COUNT ltit_at;   /* Left Title Attribute                        */
    COUNT btit_at;   /* Bottom Title Attribute                      */
    COUNT stat_at;   /* Status Attribute                            */
    TEXT *title;     /* Pointer to Title for window                 */
    TEXT *rtitle;    /* Pointer to Right Title for window           */
    TEXT *ltitle;    /* Pointer to Left Title for window            */
    TEXT *btitle;    /* Pointer to Bottom Title for window          */
    COUNT width;     /* Width of the Actual Window                  */
    COUNT depth;     /* Depth of the Actual Window                  */
    COUNT c_pos;     /* Current Cursor Column                       */
    COUNT r_pos;     /* Current Cursor Row                          */
    COUNT cur_r;     /* Current Row of top Left-Displayed           */
    COUNT cur_c;     /* Current Column to top left-Displayed        */
    TEXT *location;  /* Pointer to Location of Window               */
    COUNT smerge;    /* Side Merge Location                         */
    COUNT bmerge;    /* Bottom Merge Location                       */
    PFI wtranfunc;   /* Window translate function                   */
    PFI wmsgfunc;    /* Window message function                     */
    UCOUNT wmsgmask; /* Window message mask                         */
    TEXT *wterm;     /* Pointer to structure for terminal emulation */
    TEXT *wxptr2;    /* Might be used for getlist or terminal struct*/
    };

struct WDO_STYLE
    {                           /* -------------------------------- */
    struct WDO_STYLE *wstylnext;/* Pointer to next window style     */
    TEXT *wstylnam;             /* Window Style Name                */
    COUNT wstylctrl;            /* Window Style Control Byte        */
    TEXT  wstylfch;             /* Fill Character for Window        */
    COUNT wstylbd;              /* Border Attribute                 */
    COUNT wstylbg;              /* Background Attribute             */
    COUNT wstylsay;             /* Print in Window Attribute        */
    COUNT wstylget;             /* Read from Window Attribute       */
    COUNT wstylnget;            /* Non Active get Attribute         */
    COUNT wstyltit;             /* Title Attribute                  */
    COUNT wstylrtit;            /* Right Title Attribute            */
    COUNT wstylltit;            /* Left Title Attribute             */
    COUNT wstylbtit;            /* Bottom Title Attribute           */
    COUNT wstylstat;            /* Status Attribute                 */
    };                          /* -------------------------------- */

struct WDO_DESC
    {                           /* -------------------------------- */
    struct WDO_DESC *wdefnext;  /* Pointer to Next Definition       */
    TEXT *wdefname;             /* Pointer to Window Name           */
    TEXT *wdefstyle;            /* Pointer to Name of Window Style  */
    TEXT *wdeftitle;            /* Pointer to Title for window      */
    TEXT *wdefrtitle;           /* Pointer to Right Title for window*/
    TEXT *wdefltitle;           /* Pointer to Left Title for window */
    TEXT *wdefbtitle;           /* Pointer to Bottom Title for wdo  */
    COUNT wdefur;               /* Upper Right                      */
    COUNT wdefuc;               /* Upper Left                       */
    COUNT wdeflr;               /* Lower Right                      */
    COUNT wdeflc;               /* Lower Left                       */
    COUNT wdefwid;              /* Width of the Actual Window       */
    COUNT wdefdep;              /* Depth of the Actual Window       */
    COUNT wdefsmer;             /* Side Merge Location              */
    COUNT wdefbmer;             /* Bottom Merge Location            */
    };                          /* -------------------------------- */

struct STR_WSTYLE
    {
    TEXT *wssnam;    /* Window Style Name                           */
    COUNT wssctrl;   /* Window Style Control Byte                   */
    TEXT  wssfch;    /* Fill Character for Window                   */
    COUNT wssbd;     /* Border Attribute                            */
    COUNT wssbg;     /* Background Attribute                        */
    COUNT wsssay;    /* Print in Window Attribute                   */
    COUNT wssget;    /* Read from Window Attribute                  */
    COUNT wssnget;   /* Non Active get Attribute                    */
    COUNT wsstit;    /* Title Attribute                             */
    COUNT wssrtit;   /* Right Title Attribute                       */
    COUNT wssltit;   /* Left Title Attribute                        */
    COUNT wssbtit;   /* Bottom Title Attribute                      */
    COUNT wssstat;   /* Status Attribute                            */
    };

struct STR_WDEF
    {
    TEXT *wdsname;   /* Pointer to Window Name                      */
    TEXT *wdsstyle;  /* Pointer to Name of Window Style             */
    TEXT *wdstitle;  /* Pointer to Title for window                 */
    TEXT *wdsrtitle; /* Pointer to Right Title for window           */
    TEXT *wdsltitle; /* Pointer to Left Title for window            */
    TEXT *wdsbtitle; /* Pointer to Bottom Title for window          */
    COUNT wdsur;     /* Upper Right to Override window style        */
    COUNT wdsuc;     /* Upper Left to Override window style         */
    COUNT wdslr;     /* Lower Right to Override window style        */
    COUNT wdslc;     /* Lower Left to Override window style         */
    COUNT wdswid;    /* Width of the Actual Window                  */
    COUNT wdsdep;    /* Depth of the Actual Window                  */ 
    COUNT wdssmer;   /* Side Merge Location                         */
    COUNT wdsbmer;   /* Bottom Merge Location                       */
    };

typedef struct WDO_DESC WDEF;
typedef struct WDO_STYLE WSTYLE;

struct WDOCTRL
    {
    struct WINF *wcurrent;  /* Current Window Selected              */
    struct WINF *whead;     /* Head of opened order window list     */
    struct WINF *wtail;     /* Tail of opened order window list     */
    struct WINF *wdhead;    /* Head of display order                */
    struct WINF *wdtail;    /* Tail of display order                */
    COUNT wno_opn;   /* Number of Open Windows                      */
    COUNT wno_active;/* Number of Active Windows                    */
    COUNT wstdctrl;  /* standard control byte for window in wopen() */
    COUNT wfreeze;   /* Freeze output to Current Active Window      */
    COUNT wbgdisplay;/* Check to see if it is ok to print on screen */
    COUNT wsrninit;  /* Window screen initialized                   */
    COUNT wretlf;    /* 0 No tran. : 1 lf = lf+ret : 2 ret = ret+lf */
    COUNT wstrip;    /* Strip high bit in cooked mode               */
    PFI wcookfunc;   /* Default window cooked function              */
    COUNT wtabsize;  /* Size of Tab in COOKED Mode                  */
    COUNT wdelay;    /* Delay on window opens                       */
    COUNT rowcut;    /* Number of Rows in Cut and Paste             */
    COUNT colcut;    /* Number of Columns in Cut and Paste          */
    struct WINF *wcutwdo;    /* Cut and Paste Window                */
    struct WINF *wdebug;     /* Debug Window                        */
    PFI wopnfunc;    /* Pointer to function to use as window open   */
    PFI wclfunc;     /* Pointer to function to use as window close  */
    struct WDO_STYLE *wstyle; /* Pointer to head of window style    */
    struct WDO_DESC *wdefine; /* Pointer to head of window defines  */
    };

/*------------------------------------------------------------------*/
/*---------------------------Color Table----------------------------*/
/*------------------------------------------------------------------*/

struct wcolr
    {
    COUNT black;
    COUNT blue;
    COUNT green;
    COUNT cyan;
    COUNT red;
    COUNT magenta;
    COUNT brown;
    COUNT white;
    COUNT bold;      /* Added to Color for Bright except Bg         */
    COUNT blink;     /* Added to Color to Blink                     */
    COUNT bg;        /* Must be Multiplied by color                 */
    COUNT dflt;
    };

/*------------------------------------------------------------------*/
/*-------------------------Border Structure-------------------------*/
/*------------------------------------------------------------------*/

struct BODR
    {
    COUNT up;        /* Character to Print Up the Screen (GV/gv)    */
    COUNT across;    /* Character to Print Across the Screen (GH/gh)*/
    COUNT tl;        /* Top Left Character               (G2/g2)    */
    COUNT tr;        /* Top Right Character              (G1/g1)    */
    COUNT bl;        /* Bottom Left Character            (G3/g3)    */
    COUNT br;        /* Bottom Right Character           (G4/g4)    */
    COUNT lside;     /* Merge with Left Side Character   (GL/gl)    */
    COUNT rside;     /* Merge with Right Side Character  (GR/gr)    */
    COUNT mb;        /* Merge with Bottom Character      (GU/gu)    */
    COUNT mt;        /* Merge with Top Character         (GD/gd)    */
    COUNT middle;    /* Middle Intersection              (GC/gc)    */
    COUNT sacross;   /* Side Across Character            (GA/ga)    */
    COUNT bup;       /* Bottom up Character              (GB/gb)    */
    COUNT scr_side;  /* Scroll Side Character            (GF/gf)    */
    COUNT scr_bot;   /* Scroll Bottom Character          (GI/gi)    */
    COUNT scr_tch;   /* Scroll Top Character             (GJ/gj)    */
    COUNT scr_bch;   /* Scroll Bottom Character          (GK/gk)    */
    COUNT scr_lch;   /* Scroll Left Character            (GM/gm)    */
    COUNT scr_rch;   /* Scroll Right Character           (GN/gn)    */
    COUNT scr_rcur;  /* Scroll Right Current Location Char  (GO/go) */
    COUNT scr_bcur;  /* Scroll Bottom Current Location Char (GP/gp) */
    };

/*------------------------------------------------------------------*/
/*----------------------Default Window Colors-----------------------*/
/*------------------------------------------------------------------*/

struct WTBL
    {
    COUNT bd_t;      /* Default Border Attribute                    */
    COUNT bg_t;      /* Default Background Attribute                */
    COUNT say_t;     /* Default Say Attribute                       */
    COUNT nget_t;    /* Default Non Active Get Attribute            */
    COUNT get_t;     /* Default Get Attribute                       */
    COUNT tit_t;     /* Default Title Attribute                     */
    COUNT rtit_t;    /* Right Title Attribute                       */
    COUNT ltit_t;    /* Left Title Attribute                        */
    COUNT btit_t;    /* Bottom Title Attribute                      */
    COUNT stat_t;    /* Status Attribute                            */
    };

/*------------------------------------------------------------------*/
/*---------------------------Key Structure--------------------------*/
/*------------------------------------------------------------------*/

struct vckeys
    {                /* ------------------------------------------- */
                     /*  Generic Terminal Keys and Potential Value  */
                     /*  Name      Termcap/lbl    Default    Value  */
                     /* ------------------------------------------- */
    COUNT esc;       /*  ESC         (n)kz          ESC       4000  */
    COUNT backsp;    /*  Backspace      kb          ^H        4001  */
    COUNT ret;       /*  Return         cr          ^M        4002  */
    COUNT brk;       /*  Break       (n)bk          ^B        4003  */
    COUNT tab;       /*  Tab            ta          ^I        4004  */
    COUNT btab;      /*  Back Tab       bt          ^Q        4005  */
    COUNT cur_left;  /*  Cursor Left    kl          ^S        4006  */
    COUNT cur_right; /*  Cursor Right   kr          ^D        4007  */
    COUNT cur_up;    /*  Cursor Up      ku          ^E        4008  */
    COUNT cur_down;  /*  Cursor Down    kd          ^X        4009  */
    COUNT home_key;  /*  Home Key       kh          ^W        4010  */
    COUNT end_key;   /*  End Key        EN          ^Z        4011  */
    COUNT pgup;      /*  Page Up        PU          ^R        4012  */
    COUNT pgdn;      /*  Page Down      PD          ^C        4013  */
    COUNT ins_key;   /*  Insert Key  (n)ki          ^V        4014  */
    COUNT del_key;   /*  Delete Key  (n)kk          ^G        4015  */
    COUNT ins_ln;    /*  Insert Line (n)LI          ^N        4016  */
    COUNT del_ln;    /*  Delete Line    LD          ^Y        4017  */
    COUNT hlp_key;   /*  Help Key    (n)kp          F0        4018  */
    COUNT enter_key; /*  Enter Key   (n)ek          ^M        4019  */
    COUNT clear_key; /*  Clear Key   (n)ck          ^O        4020  */
    COUNT print_key; /*  Print Key   (n)pk          ^P        4021  */
    COUNT num_mis;   /*  Number Minus(n)mk           -        4026  */
    COUNT num_com;   /*  Number Comma(n)nk           ,        4027  */
    COUNT num_plus;  /*  Number Plus (n)ok           +        4028  */
                     /* ------------------------------------------  */
                     /*                Function Keys                */
                     /* Name      Termcap/lbl    Default    Value   */
                     /* ------------------------------------------- */
    COUNT no_fkeys;  /* No Func. Keys  kn           0       None    */
                     /* F0 -F9      k0-k9/l0-l9     0     5000-5009 */
                     /* F10-F19  (n)m0-m9/M0-M9     0     5010-5019 */
                     /* F20-F29  (n)n0-n9/N0-N9     0     5020-5029 */
                     /* F30-F39  (n)o0-o9/O0-O9     0     5030-5039 */
                     /* F40-F49  (n)p0-p9/P0-P9     0     5040-5049 */
                     /* F50-F59  (n)q0-q9/Q0-Q9     0     5050-5059 */
                     /* F60-F69  (n)r0-r9/R0-R9     0     5060-5069 */
                     /* F70-F79  (n)s0-s9/S0-S9     0     5070-5079 */
                     /* F80-F89  (n)t0-t9/T0-T9     0     5080-5089 */
                     /* F90-F99  (n)u0-u9/U0-U9     0     5090-5099 */
                     /* F100-F109(n)v0-v9/V0-V9     0     5100-5109 */
                     /* F110-F119(n)w0-w9/W0-W9     0     5110-5119 */
                     /* F120-F129(n)x0-x9/X0-X9     0     5120-5129 */
                     /* F130-F139(n)y0-y9/Y0-W9     0     5130-5139 */
                     /* F140-F149(n)z0-z9/Z0-Z9     0     5140-5149 */
    };               /* ------------------------------------------- */

struct spkeys
    {                /* ------------------------------------------- */
                     /*            Keys Used by Vitamin C           */
                     /*  Name      Termcap/lbl    Default    Value  */
                     /* ------------------------------------------- */
    COUNT abort;     /*  Exit Key                                   */
    COUNT hkey;      /*  Help Key                                   */
    COUNT xhkey;     /*  Exit Help                                  */
    COUNT wakey;     /*  Window Adj                                 */
    COUNT done;      /*  Done                                       */
    COUNT fld_ret;   /*  Field Return                               */
    COUNT fld_end;   /*  End of list                                */
    COUNT fld_home;  /*  Field Home                                 */
    COUNT fld_cleft; /*  Cursor Left                                */
    COUNT fld_cright;/*  Cursor Right                               */
    COUNT fld_bksp;  /*  Backspace                                  */
    COUNT fld_del;   /*  Del Right                                  */
    COUNT fld_blank; /*  Blank Field                                */
    COUNT fld_deof;  /*  Del End of Field                           */
    COUNT fld_ins;   /*  Field Insert                               */
    COUNT fld_left;  /*  Field Left                                 */
    COUNT fld_right; /*  Field Right                                */
    COUNT fld_down;  /*  Field Down                                 */
    COUNT fld_up;    /*  Field Up                                   */
    COUNT fld_pgdn;  /*  PgDn Fields                                */
    COUNT fld_pgup;  /*  PgUP Fields                                */
    COUNT fld_mode;  /*  Field mode key                             */
    COUNT list_dn;   /*  Down List                                  */
    COUNT list_up;   /*  Up List                                    */
    COUNT list_left; /*  Left list                                  */
    COUNT list_right;/*  Right list                                 */
    COUNT list_pgup; /*  PgUp List                                  */
    COUNT list_pgdn; /*  PgDn list                                  */
    COUNT list_home; /*  List home                                  */
    COUNT list_end;  /*  List Home                                  */
    COUNT prt_scrn;  /*  Print Screen                               */
    COUNT scrn_fresh;/*  Screen refresh                             */
    COUNT mouse_on;  /*  Mouse On                                   */
    };               /* ------------------------------------------- */

/*------------------------------------------------------------------*/
/*--------------------Terminal Control Structure--------------------*/
/*------------------------------------------------------------------*/

struct PRECOMP
    {
    TEXT *before;    /*  String sent before row                     */
    TEXT *between;   /*  String sent between row and column         */
    TEXT *after;     /*  String sent after row and column           */
    COUNT col_first; /*  1 = send column first                      */
    COUNT rformat;   /*  Format of row 1=d 2=2d 3=3d 4=.            */
    COUNT cformat;   /*  Format of column 1=d 2=2d 3=3d 4=.         */
    COUNT rofset;    /*  Value to add to row                        */
    COUNT cofset;    /*  Value to add to column                     */
    };

struct KEYLBL
    {
    COUNT klblval;   /*  Value for this key                         */
    TEXT *klblptr;   /*  Pointer to label for this key              */
    };

struct termctrl 
    {
    TEXT *tmname;    /*  Terminal Name                              */
    COUNT rows;      /*  Number of rows on terminal                 */
    COUNT cols;      /*  Number of columns on terminal              */
    COUNT sg;        /*  Number of blank character left by so or se */
    COUNT ug;        /*  Number of blank character left by ue or us */
    COUNT cg;        /*  Number of character left blank by ct (n)cg */
    COUNT gg;        /*  Number of character taken by GS and GE (GG)*/
    COUNT bb;        /*  Number of character taken by bl & be (n)bb */
    COUNT ig;        /*  Number of character taken by it & ie (n)ig */
    COUNT zd;        /*  Delay used on keyrdy reads  (zd)           */
    COUNT zk;        /*  Disable keyrdy function (zk)               */
    COUNT zc;        /*  Number of character to wait on read (zc)   */
    COUNT zt;        /*  Amount of time to wait on key read (zt)    */
    COUNT am;        /*  Terminal has automatic margins             */
    COUNT bs;        /*  Terminal can backspace with ^H             */
    COUNT ms;        /*  Can move in Standout (or any mode)         */
    COUNT xs;        /*  Standout not erased by overwritting (hp)   */
    COUNT mc;        /*  Magic Cookie problem                       */ 
    UCOUNT sp;       /*  Terminal has attr that requires a space    */
    TEXT *ae;        /*  End alternate character set                */
    TEXT *as;        /*  Start alternate character set              */
    TEXT *bc;        /*  Backspace Character if not ^H              */
    TEXT *bo;        /*  Start blink mode                           */
    TEXT *be;        /*  End blink mode                             */
    TEXT *ic;        /*  Alternate cursor on (n)ca                  */
    TEXT *cd;        /*  Clear to end of display                    */
    TEXT *ce;        /*  Clear to end of line                       */
    TEXT *cf;        /*  Cursor off  (CF)                           */
    TEXT *cl;        /*  Clear Screen                               */
    TEXT *co;        /*  Cursor on  (CO)                            */
    TEXT *cm;        /*  Address Cursor                             */
    TEXT *ct;        /*  Color Terminal (n) ct                      */
    TEXT *es;        /*  Exit String (n) es                         */
    TEXT *ie;        /*  End low intensity mode                     */
    TEXT *is;        /*  Terminal initialization string             */
    TEXT *it;        /*  Start low intensity mode                   */
    TEXT *ke;        /*  Out of Keypad Transmit Mode                */
    TEXT *ks;        /*  Start Keypad Transmit Mode                 */
    TEXT *ge;        /*  End graphics mode (GE)                     */
    TEXT *gs;        /*  Begin graphics mode (GS)                   */
    TEXT *pc;        /*  Pad character other than NULL              */
    TEXT *se;        /*  End stand out mode  (inverse)              */
    TEXT *so;        /*  Begin stand out mode (inverse)             */
    TEXT *ue;        /*  End underscore mode                        */
    TEXT *us;        /*  Start underscore mode                      */
    TEXT *ve;        /*  End alternate cursor                       */
    TEXT *vs;        /*  Start alternate cursor                     */
    struct KEYTBLNODE *table; /* Special Key Translate Table        */
    struct PRECOMP cursor;    /* Cursor Addressing Pre Compile(cm)  */
    struct PRECOMP color;     /* Color Monitor Pre Compile (ct)     */
    struct KEYLBL *firstkeylbl;/* Pointer to first key label        */
    TEXT *sp0on;     /*  Invisible space attribute            n(a0) */
    TEXT *sp1on;     /*  Underline space attribute            n(a1) */
    TEXT *sp2on;     /*  Normal space attribute               n(a2) */
    TEXT *sp3on;     /*  Lolite/Underline space attribute     n(a3) */
    TEXT *sp4on;     /*  Lolite/Normal space attribute        n(a4) */
    TEXT *sp5on;     /*  Inverse space attribute              n(a5) */
    TEXT *sp6on;     /*  Inverse/Underline space attribute    n(a6) */
    TEXT *sp7on;     /*  Lolite/Inverse space attribute       n(a7) */
    TEXT *sp8on;     /*  Blink/Underline space attribute      n(a8) */
    TEXT *sp9on;     /*  Blink/Normal space attribute         n(a9) */
    TEXT *spaon;     /*  Graphics/Underline space attribute   n(b0) */
    TEXT *spbon;     /*  Graphics/Normal space attribute      n(b1) */
    TEXT *spcon;     /*  Blink/Inverse space attribute        n(b2) */
    TEXT *spdon;     /*  Inverse/Underline/Blink space attr.  n(b3) */
    TEXT *speon;     /*  Graphics/Inverse space attribute     n(b4) */
    TEXT *spfon;     /*  Graphics/Inverse/Underline space att n(b5) */
    TEXT *sp0off;    /*  Invisible space attribute            n(A0) */
    TEXT *sp1off;    /*  Underline space attribute            n(A1) */
    TEXT *sp2off;    /*  Normal space attribute               n(A2) */
    TEXT *sp3off;    /*  Lolite/Underline space attribute     n(A3) */
    TEXT *sp4off;    /*  Lolite/Normal space attribute        n(A4) */
    TEXT *sp5off;    /*  Inverse space attribute              n(A5) */
    TEXT *sp6off;    /*  Inverse/Underline space attribute    n(A6) */
    TEXT *sp7off;    /*  Lolite/Inverse space attribute       n(A7) */
    TEXT *sp8off;    /*  Blink/Underline space attribute      n(A8) */
    TEXT *sp9off;    /*  Blink/Normal space attribute         n(A9) */
    TEXT *spaoff;    /*  Graphics/Underline space attribute   n(B0) */
    TEXT *spboff;    /*  Graphics/Normal space attribute      n(B1) */
    TEXT *spcoff;    /*  Blink/Inverse space attribute        n(B2) */
    TEXT *spdoff;    /*  Inverse/Underline/Blink space attr.  n(B3) */
    TEXT *speoff;    /*  Graphics/Inverse space attribute     n(B4) */
    TEXT *spfoff;    /*  Graphics/Inverse/Underline space att n(B5) */
    };

struct VCREGS { UCOUNT ax,bx,cx,dx,si,di,ds,es; }; 

struct HLP_STR
    {
    TEXT keyword[12];
    LONG filloc;
    };

/*------------------------------------------------------------------*/
/*---------------------------End of File----------------------------*/
/*------------------------------------------------------------------*/
