/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 9/2/90 at 14:44:30
*
*   Name            vcextern.h  --  External Global Variables
*
*   Description
*
*
**/

/*------------------------------------------------------------------*/

extern COUNT vcrow;    /* Current Row                               */
extern COUNT vccol;    /* Current Column                            */
extern TEXT *hlptxt;   /* Pointer to Help Text                      */
extern COUNT msgrow;   /* Message Row                               */
extern COUNT msgcol;   /* Message Column                            */
extern COUNT msgattr;  /* Message Attribute                         */
extern WPTR msgwdo;    /* Message Window                            */
extern COUNT override; /* Override Window logic Yes-1 No-0          */
extern PFI waitfunc;   /* Pointer to Wait function                  */
extern PFI helpfunc;   /* Pointer to Help function                  */
extern PFI keytrap;    /* Pointer to Key trap function              */
extern PFI syskeytrap; /* Pointer to System Key trap function       */
extern PFI dplist;     /* Pointer to default plist function         */
extern COUNT bellstat; /* Bell Off-1 or On-0                        */
extern COUNT vcerror;  /* Global error number defined in vcerror.h  */
extern PFI vcerrfunc;  /* User error function called by terror      */
extern COUNT vccursor; /* Current Cursor Status                     */
extern FILE *prthandle;/* Printer handle                            */
extern COUNT vcdecimal;/* Decimal value for '.'                     */
extern COUNT vcdollar; /* Dollar sign '$'                           */

/*------------------------------------------------------------------*/
/*----------------------Terminal Variables--------------------------*/
/*------------------------------------------------------------------*/
                                                                    
extern struct termctrl vcterm;/* Vitamin C terminal defines         */
extern TEXT *vcinput;   /* Pointer to optional input file           */
extern TEXT *vcoutput;  /* Pointer to optional output file          */
#ifdef TERMINAL
extern COUNT bufon; /* Whether the terminal buffer is currently on  */
extern COUNT curon; /* Was the cursor on before the buffer started  */
extern COUNT trow;  /* The current physical terminal row            */
extern COUNT tcol;  /* The current physical terminal column         */
extern COUNT sp_attr;/* Was the attribute turned off a special attr */
extern TEXT *tbufptr;/* Current location pointer for terminal buffer*/
extern TEXT *termbuf;/* Pointer to terminal buffer                  */
extern TEXT *tbufend;/* Pointer to end of terminal buffer           */
extern TEXT *(*gotofunc)();/* function to translate xy goto         */
extern PFI padfunc;        /* function to add string padding        */
extern COUNT ttranslate;   /* mode VC, termcap, or terminfo         */
#endif
/*------------------------------------------------------------------*/
/*-----------------------Termcap Variables--------------------------*/
/*------------------------------------------------------------------*/

extern TEXT *chbuf; /* Buffer used for termcap requests             */
extern TEXT pathbuf[100];/* Full path area for /etc/termcap.vc open */
extern struct KEYTBLNODE *sorted; /* Sorted termcap entries for sped*/
extern TEXT retbuf[30];  /* Returns the cursor addressing string    */
extern COUNT no_tc; /* If tgetent has not called itself             */

/*-------------------------Debug Variables--------------------------*/

extern TEXT *vcdebug;  /* Pointer to debug string                   */
#ifdef VCDEBUG
extern PFI vcdbfunc;   /* Pointer to debug function                 */
extern COUNT vcdbstep; /* Set single step mode                      */
extern TEXT *vcdbstop; /* Pointer to function to stop on            */
#endif

/*------------------------------------------------------------------*/
/*----------------------Keyboard Variables--------------------------*/
/*------------------------------------------------------------------*/

extern COUNT kbbuffer[127]; /* Keyboard buffer                      */
extern COUNT *kbbufhd;      /* Head of buffer                       */
extern COUNT *kbbuftl;      /* Tail of buffer                       */
extern COUNT *kbbufed;      /* End of buffer                        */
extern struct vckeys vckey; /* Terminal key structure               */
extern struct spkeys spkey; /* Vitamin C key definitions            */
extern COUNT blocked[20];   /* Blocked key array                    */
extern COUNT keysblocked;   /* Current number of blocked keys       */
extern COUNT vckeyrdy;      /* Terminal has key ready function      */
extern COUNT vcshift;       /* Shift Status                         */

/*------------------------------------------------------------------*/
/*-----------------------Default Colors-----------------------------*/
/*------------------------------------------------------------------*/

extern COUNT attrag;   /* ATTRibute for Active Gets                 */
extern COUNT attrnag;  /* ATTRibute for Non-Active Gets             */
extern COUNT attrsay;  /* ATTRibute for Say's                       */
extern COUNT normattr; /* Normal attribute for system               */
extern COUNT termattr; /* Current terminal attribute                */
extern COUNT graphattr;/* Current graphics state                    */

extern struct wcolr vc;

/*------------------------------------------------------------------*/

extern struct WDOCTRL *wdoctrl;
extern COUNT cur_switch;/* Move cursor on or off                    */
#ifdef IBM
extern COUNT vcvram;    /* Screen location 0xb000 = monchrome       */
extern COUNT vcsprt;    /* Video status port                        */
#endif
extern COUNT vctio;     /* Method to output to screen               */
extern TEXT *wscreen; /* Memory Screen                              */
extern TEXT *wbscreen;/* Backup Memory Screen                       */
extern TEXT *tscreen; /* Terminal Memory Screen                     */
   
extern COUNT wmaxtab;
extern COUNT wtab[];
extern struct BODR border[];
extern struct WTBL wtable[];

extern struct WTBL wmono[];

extern struct HLP_STR *hlpndx; /* Help index                        */
extern FILE *hlpfil;  /* Help file                                  */
extern PFI hlphk1;    /* Help hook function 1                       */
extern PFI hlphk2;    /* Help hook function 2                       */
extern COUNT hlptrow; /* Top row of help window                     */
extern COUNT hlptcol; /* Top column of help window                  */
extern COUNT hlpbrow; /* Bottom row of help window                  */
extern COUNT hlpbcol; /* Bottom column of help window               */
extern COUNT hlpdepth;/* Depth of help window                       */
extern COUNT hlpwidth;/* Width of help window                       */
extern COUNT hlpcolor;/* Window color of help window                */
extern COUNT hlpborder;/* Border of help window                     */
extern TEXT *hlptitle;/* Pointer to title for help window           */
extern COUNT hlpctrl; /* Help window control byte                   */
/*------------------------------------------------------------------*/

