/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:25
*
*   Name            vcglobal.c  --  All global variables
*
*   Description     This file contains all the global variables
*
**/

#define vcglobal

#include <vcstdio.h>

#ifdef VMS
COUNT vcldgl()
    {
    return(TRUE);
    }
#endif

/*------------------------------------------------------------------*/
/*-----------------------System Variables---------------------------*/
/*------------------------------------------------------------------*/
                                                                    
COUNT vcrow = 0;    /* Current Row                                  */
COUNT vccol = 0;    /* Current Column                               */
COUNT bellstat=1;   /* Bell Off-1 or On-0                           */
COUNT vcerror = 0;  /* Global errors defines in vcerror.h           */
PFI vcerrfunc = NULLFUNC; /* Error function called by terror        */
COUNT vccursor =1;  /* Current Cursor Status                        */
COUNT vctio  = -1;  /* Method for output to screen                  */
COUNT cur_switch =1;/* Address the Cursor 0 = off 1 = on            */
FILE *prthandle = (FILE *)0;/* Printer handle                       */
COUNT vcdecimal = '.';      /* Value of decimal point               */
COUNT vcdollar = '$';       /* Value of dollar sign                 */

#ifdef IBM
COUNT vcvram = 0xb800;/* Screen location 0xb000 = monchrome         */
COUNT vcsprt = 0x3da;/* color monitor Video status port,mono=0x3ba  */
#endif

/*------------------------------------------------------------------*/
/*----------------------Terminal Variables--------------------------*/
/*------------------------------------------------------------------*/

TEXT *vcinput = NULLTEXT;   /* Pointer to optional input file       */
TEXT *vcoutput = NULLTEXT;  /* Pointer to optional output file      */
#ifdef TERMINAL
TEXT *tscreen = NULLTEXT;/* Terminal Memory Screen                  */
COUNT bufon=0;      /* Whether the terminal buffer is currently on  */
COUNT curon=0;      /* Was the cursor on before the buffer started  */
COUNT trow = -1;    /* The current physical terminal row            */
COUNT tcol = -1;    /* The current physical terminal column         */
COUNT sp_attr=0;    /* Was the attribute turned off a special attr  */
TEXT *tbufptr;      /* Current location pointer for terminal buffer */
TEXT *termbuf;      /* Pointer to terminal buffer                   */
TEXT *tbufend;      /* Pointer to end of terminal buffer            */
PFT gotofunc = (PFT)0;         /* Function to translate xy goto     */
PFI padfunc = NULLFUNC;        /* Function to add string padding    */
COUNT ttranslate = 0;          /* Mode VC, termcap, or terminfo     */
#endif

/*------------------------------------------------------------------*/
/*-----------------------Termcap Variables--------------------------*/
/*------------------------------------------------------------------*/

TEXT *chbuf;        /* Buffer used for termcap requests             */
TEXT pathbuf[100];  /* Full path area for /etc/termcap.vc open      */
struct KEYTBLNODE *sorted;  /* Sorted termcap entries for speed     */
TEXT retbuf[30];    /* Returns the cursor addressing string         */
COUNT no_tc=TRUE;   /* If tgetent has not called itself             */

/*------------------------------------------------------------------*/
/*-------------------------Debug Variables--------------------------*/
/*------------------------------------------------------------------*/

TEXT *vcdebug;      /* Pointer to debug string                      */
#ifdef VCDEBUG
PFI vcdbfunc;       /* Pointer to debug function                    */
COUNT vcdbstep;     /* Set single step mode                         */
TEXT *vcdbstop;     /* Pointer to function to stop on               */
#endif

/*------------------------------------------------------------------*/
/*----------------------Keyboard Variables--------------------------*/
/*------------------------------------------------------------------*/

COUNT kbbuffer[127];/* Keyboard buffer                              */
COUNT *kbbufhd = &kbbuffer[0]; /* Head of buffer                    */
COUNT *kbbuftl = &kbbuffer[0]; /* Tail of buffer                    */
COUNT *kbbufed = &kbbuffer[126]; /* End of buffer                   */
struct spkeys spkey;/* Vitamin C key defination                     */
COUNT blocked[20];  /* Blocked key array                            */
COUNT keysblocked=0;/* Current number of blocked keys               */
PFI keytrap = NULLFUNC;/* Pointer to Key Trap function              */
PFI syskeytrap = NULLFUNC;/* Pointer to System Key Trap function    */
PFI waitfunc = NULLFUNC;/* Pointer to Wait function                 */
COUNT vckeyrdy = KEYRDY;/* Keyready function works                  */
COUNT vcshift = 0;  /* Keyboard Shift status byte                   */

/*------------------------------------------------------------------*/
/*--------------------------Color variables-------------------------*/
/*------------------------------------------------------------------*/

#ifdef IBM
COUNT attrag=112;   /* ATTRibute for Active Gets                    */
COUNT attrnag=7;    /* ATTRibute for Non-Active Gets                */
COUNT attrsay=7;    /* ATTRibute for Say's                          */
COUNT normattr=7;   /* Normal attribute for system                  */
COUNT termattr=0;   /* Current terminal attribute                   */
COUNT msgattr=7;    /* Current message attribute                    */
COUNT graphattr=0;  /* Current graphics state                       */
#endif

#ifdef TERMONLY
COUNT attrag=112;    /* ATTRibute for Active Gets                   */
COUNT attrnag=7;     /* ATTRibute for Non-Active Gets               */
COUNT attrsay=7;     /* ATTRibute for Say's                         */
COUNT normattr=7;    /* Normal attribute for system                 */
COUNT termattr=0;    /* Current terminal attribute                  */
COUNT msgattr=7;     /* Current message attribute                   */
COUNT graphattr=0;   /* Current graphics state                      */
#endif

#ifdef OS2
COUNT attrag=112;   /* ATTRibute for Active Gets                    */
COUNT attrnag=7;    /* ATTRibute for Non-Active Gets                */
COUNT attrsay=7;    /* ATTRibute for Say's                          */
COUNT normattr=7;   /* Normal attribute for system                  */
COUNT termattr=0;   /* Current terminal attribute                   */
COUNT msgattr=7;    /* Current message attribute                    */
COUNT graphattr=0;  /* Current graphics state                       */
#endif

/*------------------------------------------------------------------*/
/*---------------------Status Message Variables---------------------*/
/*------------------------------------------------------------------*/

COUNT msgrow= 0;    /* Message Row                                  */
COUNT msgcol= 0;    /* Message Column                               */
WPTR msgwdo = (WPTR)0; /* Message Window                            */

/*------------------------------------------------------------------*/
/*------------------------Color Tables------------------------------*/
/*------------------------------------------------------------------*/


struct wcolr vc =
    {
    00,             /* Black                                        */
    01,             /* Blue                                         */
    02,             /* Green                                        */
    03,             /* Cyan                                         */
    04,             /* Red                                          */
    05,             /* Magenta                                      */
    06,             /* Brown                                        */
    07,             /* White                                        */
    8,              /* Bold                                         */
    128,            /* Blink                                        */
    16,             /* Background (must be multiplied by color)     */
    -1              /* Default color                                */
    };

/*------------------------------------------------------------------*/
/*-----------------------Window Variables---------------------------*/
/*------------------------------------------------------------------*/

#ifdef WINDOW

TEXT *wscreen = NULLTEXT; /* Memory Screen                          */
TEXT *wbscreen = NULLTEXT;/* Backup Memory Screen                   */
struct WDOCTRL *wdoctrl;/* Window control structure                 */
COUNT override = 0; /* Override Window logic Yes-1 No-0             */

#endif

/*------------------------------------------------------------------*/
/*-----------------Table for Default Window Colors------------------*/
/*------------------------------------------------------------------*/

#ifdef WINDOW

#define Black 0
#define Blue 1
#define Green 2
#define Cyan 3
#define Red 4
#define Magenta 5
#define Brown 6
#define White 7
#define Bold 8
#define Blink 128
#define Bkgd 16  

struct WTBL wtable[10] =
    {
    Cyan,           /* Default Border Attribute              (0)    */
    White,          /* Default Background Attribute          (0)    */
    Brown,          /* Default Say Attribute                 (0)    */
    Cyan,           /* Default Non Active Get Attribute      (0)    */
    Cyan*Bkgd,      /* Default Get Attribute                 (0)    */
    Cyan,           /* Default Title Attribute               (0)    */
    Cyan,           /* Right Title Attribute                 (0)    */
    Cyan,           /* Left Title Attribute                  (0)    */
    Cyan,           /* Bottom Title Attribute                (0)    */
    Cyan,           /* Status Attribute                      (0)    */
    Brown,          /* Default Border Attribute              (1)    */
    White,          /* Default Background Attribute          (1)    */
    Cyan,           /* Default Say Attribute                 (1)    */
    Brown,          /* Default Non Active Get Attribute      (1)    */
    Brown*Bkgd,     /* Default Get Attribute                 (1)    */
    Brown,          /* Default Title Attribute               (1)    */
    Brown,          /* Right Title Attribute                 (1)    */
    Brown,          /* Left Title Attribute                  (1)    */
    Brown,          /* Bottom Title Attribute                (1)    */
    Brown,          /* Status Attribute                      (1)    */
    Green,          /* Default Border Attribute              (2)    */
    White,          /* Default Background Attribute          (2)    */
    Brown,          /* Default Say Attribute                 (2)    */
    Green,          /* Default Non Active Get Attribute      (2)    */
    Green*Bkgd,     /* Default Get Attribute                 (2)    */
    Green,          /* Default Title Attribute               (2)    */
    Green,          /* Right Title Attribute                 (2)    */
    Green,          /* Left Title Attribute                  (2)    */
    Green,          /* Bottom Title Attribute                (2)    */
    Green,          /* Status Attribute                      (2)    */
    White,          /* Default Border Attribute              (3)    */
    White,          /* Default Background Attribute          (3)    */
    Cyan,           /* Default Say Attribute                 (3)    */
    White,          /* Default Non Active Get Attribute      (3)    */
    White*Bkgd,     /* Default Get Attribute                 (3)    */
    White,          /* Default Title Attribute               (3)    */
    White,          /* Right Title Attribute                 (3)    */
    White,          /* Left Title Attribute                  (3)    */
    White,          /* Bottom Title Attribute                (3)    */
    White,          /* Status Attribute                      (3)    */
    Brown,          /* Default Border Attribute              (4)    */
    White,          /* Default Background Attribute          (4)    */
    Green,          /* Default Say Attribute                 (4)    */
    White,          /* Default Non Active Get Attribute      (4)    */
    White*Bkgd,     /* Default Get Attribute                 (4)    */
    White,          /* Default Title Attribute               (4)    */
    White,          /* Right Title Attribute                 (4)    */
    White,          /* Left Title Attribute                  (4)    */
    White,          /* Bottom Title Attribute                (4)    */
    White,          /* Status Attribute                      (4)    */
    Cyan,           /* Default Border Attribute              (5)    */
    White,          /* Default Background Attribute          (5)    */
    Brown,          /* Default Say Attribute                 (5)    */
    White,          /* Default Non Active Get Attribute      (5)    */
    White*Bkgd,     /* Default Get Attribute                 (5)    */
    White,          /* Default Title Attribute               (5)    */
    White,          /* Right Title Attribute                 (5)    */
    White,          /* Left Title Attribute                  (5)    */
    White,          /* Bottom Title Attribute                (5)    */
    White,          /* Status Attribute                      (5)    */
    Red,            /* Default Border Attribute              (6)    */
    White,          /* Default Background Attribute          (6)    */
    Cyan,           /* Default Say Attribute                 (6)    */
    White,          /* Default Non Active Get Attribute      (6)    */
    Red+White*Bkgd, /* Default Get Attribute                 (6)    */
    White,          /* Default Title Attribute               (6)    */
    White,          /* Right Title Attribute                 (6)    */
    White,          /* Left Title Attribute                  (6)    */
    White,          /* Bottom Title Attribute                (6)    */
    White,          /* Status Attribute                      (6)    */
    Green,          /* Default Border Attribute              (7)    */
    White,          /* Default Background Attribute          (7)    */
    Cyan,           /* Default Say Attribute                 (7)    */
    White,          /* Default Non Active Get Attribute      (7)    */
    White*Bkgd,     /* Default Get Attribute                 (7)    */
    White,          /* Default Title Attribute               (7)    */
    White,          /* Right Title Attribute                 (7)    */
    White,          /* Left Title Attribute                  (7)    */
    White,          /* Bottom Title Attribute                (7)    */
    White,          /* Status Attribute                      (7)    */
    Cyan,           /* Default Border Attribute              (8)    */
    White,          /* Default Background Attribute          (8)    */
    Cyan,           /* Default Say Attribute                 (8)    */
    Brown,          /* Default Non Active Get Attribute      (8)    */
    Brown+Blue*Bkgd,/* Default Get Attribute                 (8)    */
    Brown,          /* Default Title Attribute               (8)    */
    Brown,          /* Right Title Attribute                 (8)    */
    Brown,          /* Left Title Attribute                  (8)    */
    Brown,          /* Bottom Title Attribute                (8)    */
    Brown,          /* Status Attribute                      (8)    */
    White,          /* Default Border Attribute              (9)    */
    White,          /* Default Background Attribute          (9)    */
    White,          /* Default Say Attribute                 (9)    */
    Cyan,           /* Default Non Active Get Attribute      (9)    */
    White+Bkgd*Blue,/* Default Get Attribute                 (9)    */
    Cyan,           /* Default Title Attribute               (9)    */
    Cyan,           /* Right Title Attribute                 (9)    */
    Cyan,           /* Left Title Attribute                  (9)    */
    Cyan,           /* Bottom Title Attribute                (9)    */
    Cyan,           /* Status Attribute                      (9)    */
    };                                                             

struct WTBL wmono[10] =
    {
    7,              /* Default Border Attribute              (0)    */
    7,              /* Default Background Attribute          (0)    */
    7,              /* Default Say Attribute                 (0)    */
    1,              /* Default Non Active Get Attribute      (0)    */
    112,            /* Default Get Attribute                 (0)    */
    15,             /* Default Title Attribute               (0)    */
    10,             /* Right Title Attribute                 (0)    */
    10,             /* Left Title Attribute                  (0)    */
    10,             /* Bottom Title Attribute                (0)    */
    10,             /* Status Attribute                      (0)    */
    7,              /* Default Border Attribute              (1)    */
    7,              /* Default Background Attribute          (1)    */
    7,              /* Default Say Attribute                 (1)    */
    1,              /* Default Non Active Get Attribute      (1)    */
    112,            /* Default Get Attribute                 (1)    */
    15,             /* Default Title Attribute               (1)    */
    10,             /* Right Title Attribute                 (1)    */
    10,             /* Left Title Attribute                  (1)    */
    10,             /* Bottom Title Attribute                (1)    */
    10,             /* Status Attribute                      (1)    */
    7,              /* Default Border Attribute              (2)    */
    7,              /* Default Background Attribute          (2)    */
    7,              /* Default Say Attribute                 (2)    */
    1,              /* Default Non Active Get Attribute      (2)    */
    112,            /* Default Get Attribute                 (2)    */
    15,             /* Default Title Attribute               (2)    */
    10,             /* Right Title Attribute                 (2)    */
    10,             /* Left Title Attribute                  (2)    */
    10,             /* Bottom Title Attribute                (2)    */
    10,             /* Status Attribute                      (2)    */
    7,              /* Default Border Attribute              (3)    */
    7,              /* Default Background Attribute          (3)    */
    7,              /* Default Say Attribute                 (3)    */
    1,              /* Default Non Active Get Attribute      (3)    */
    112,            /* Default Get Attribute                 (3)    */
    15,             /* Default Title Attribute               (3)    */
    10,             /* Right Title Attribute                 (3)    */
    10,             /* Left Title Attribute                  (3)    */
    10,             /* Bottom Title Attribute                (3)    */
    10,             /* Status Attribute                      (3)    */
    7,              /* Default Border Attribute              (4)    */
    7,              /* Default Background Attribute          (4)    */
    7,              /* Default Say Attribute                 (4)    */
    1,              /* Default Non Active Get Attribute      (4)    */
    112,            /* Default Get Attribute                 (4)    */
    15,             /* Default Title Attribute               (4)    */
    10,             /* Right Title Attribute                 (4)    */
    10,             /* Left Title Attribute                  (4)    */
    10,             /* Bottom Title Attribute                (4)    */
    10,             /* Status Attribute                      (4)    */
    7,              /* Default Border Attribute              (5)    */
    7,              /* Default Background Attribute          (5)    */
    7,              /* Default Say Attribute                 (5)    */
    1,              /* Default Non Active Get Attribute      (5)    */
    112,            /* Default Get Attribute                 (5)    */
    15,             /* Default Title Attribute               (5)    */
    10,             /* Right Title Attribute                 (5)    */
    10,             /* Left Title Attribute                  (5)    */
    10,             /* Bottom Title Attribute                (5)    */
    10,             /* Status Attribute                      (5)    */
    7,              /* Default Border Attribute              (6)    */
    7,              /* Default Background Attribute          (6)    */
    7,              /* Default Say Attribute                 (6)    */
    1,              /* Default Non Active Get Attribute      (6)    */
    112,            /* Default Get Attribute                 (6)    */
    15,             /* Default Title Attribute               (6)    */
    10,             /* Right Title Attribute                 (6)    */
    10,             /* Left Title Attribute                  (6)    */
    10,             /* Bottom Title Attribute                (6)    */
    10,             /* Status Attribute                      (6)    */
    7,              /* Default Border Attribute              (7)    */
    7,              /* Default Background Attribute          (7)    */
    7,              /* Default Say Attribute                 (7)    */
    1,              /* Default Non Active Get Attribute      (7)    */
    112,            /* Default Get Attribute                 (7)    */
    15,             /* Default Title Attribute               (7)    */
    10,             /* Right Title Attribute                 (7)    */
    10,             /* Left Title Attribute                  (7)    */
    10,             /* Bottom Title Attribute                (7)    */
    10,             /* Status Attribute                      (7)    */
    7,              /* Default Border Attribute              (8)    */
    7,              /* Default Background Attribute          (8)    */
    7,              /* Default Say Attribute                 (8)    */
    1,              /* Default Non Active Get Attribute      (8)    */
    112,            /* Default Get Attribute                 (8)    */
    15,             /* Default Title Attribute               (8)    */
    10,             /* Right Title Attribute                 (8)    */
    10,             /* Left Title Attribute                  (8)    */
    10,             /* Bottom Title Attribute                (8)    */
    10,             /* Status Attribute                      (8)    */
    7,              /* Default Border Attribute              (9)    */
    7,              /* Default Background Attribute          (9)    */
    7,              /* Default Say Attribute                 (9)    */
    1,              /* Default Non Active Get Attribute      (9)    */
    112,            /* Default Get Attribute                 (9)    */
    15,             /* Default Title Attribute               (9)    */
    10,             /* Right Title Attribute                 (9)    */
    10,             /* Left Title Attribute                  (9)    */
    10,             /* Bottom Title Attribute                (9)    */
    10              /* Status Attribute                      (9)    */
    };

COUNT wmaxtab=20;
COUNT wtab[20] =
    {
    0,
    1*TABSIZE,
    2*TABSIZE,
    3*TABSIZE,
    4*TABSIZE,
    5*TABSIZE,
    6*TABSIZE,
    7*TABSIZE,
    8*TABSIZE,
    9*TABSIZE,
    10*TABSIZE,
    11*TABSIZE,
    12*TABSIZE,
    13*TABSIZE,
    14*TABSIZE,
    15*TABSIZE,
    16*TABSIZE,
    17*TABSIZE,
    18*TABSIZE,
    19*TABSIZE
    };

#endif

/*------------------------------------------------------------------*/
/*---------------------Help System Gobal Variables------------------*/
/*------------------------------------------------------------------*/

TEXT *hlptxt = NULLTEXT;/* Pointer to Help Text                     */
PFI helpfunc = NULLFUNC;/* Pointer to Help function                 */
struct HLP_STR *hlpndx; /* Pointer to help index                    */
FILE *hlpfil;       /* Name of help file                            */
PFI hlphk1 = NULLFUNC;/* Help hook function 1                       */
PFI hlphk2 = NULLFUNC;/* Help hook function 2                       */
COUNT hlptrow =  3; /* Top row of help window                       */
COUNT hlptcol =  3; /* Top column of help window                    */
COUNT hlpbrow = 14; /* Bottom row of help window                    */
COUNT hlpbcol = 45; /* Bottom column of help window                 */
COUNT hlpdepth = 0; /* Depth of help window                         */
COUNT hlpwidth = 0; /* Width of help window                         */
COUNT hlpcolor = 0; /* Window color of help window                  */
COUNT hlpborder = 0;/* Border of help window                        */
COUNT hlpctrl = BORDER+SHADOW; /* Help window control byte          */
TEXT *hlptitle = (TEXT *)"Help Window"; /* Title for help window    */
