/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 9/2/90 at 14:44:32
*
*   Name            vcget.h  --  Vitamin C Defines
*
*   Description     
*
*
**/

/*------------------------------------------------------------------*/
/*-------------------------Gets Structures--------------------------*/
/*------------------------------------------------------------------*/

struct GET_NODE   
    {
    struct GET_NODE *gnext;     /* Pointer to next node in link     */
    struct GET_NODE *gprev;     /* Pointer to previous node in link */
    struct GET_NODE *gup;       /* Node for fld_up                  */
    struct GET_NODE *gdown;     /* Node for fld_down                */
    struct GET_NODE *gleft;     /* Node for fld_left                */
    struct GET_NODE *gright;    /* Node for fld_right               */
    COUNT gmagic;               /* Magic number                     */
    COUNT g_row;                /* Row for display                  */
    COUNT g_col;                /* Column for display               */
    COUNT g_length;             /* Length of field                  */
    TEXT *g_field;              /* Pointer to field                 */
    TEXT *g_picture;            /* Picture of field                 */
    TEXT *g_msg;                /* Message area                     */
    TEXT *g_help;               /* Help text                        */
    PFI g_funptr;               /* Validation function              */
    COUNT gattrag;              /* Active get attribute             */
    COUNT gattrnag;             /* Non-active get attribute         */
    COUNT gmaxwid;              /* Max width                        */
    COUNT gcontrol;             /* Bit-coded options                */
    TEXT *gselset;              /* Selection set controls           */
    PFI gplist;                 /* Selection set function           */
    PFI gprefunc;               /* Pre-function                     */
    PFI gpostfunc;              /* Post-function                    */
    TEXT *gtmppic;              /* Picture used during input        */
    TEXT *gtmpfld;              /* Field used during input          */
    COUNT gcurattr;             /* Current attribute                */
    COUNT gfldtyp;              /* Input type / Variable type       */
    COUNT gdispsiz;             /* Display size                     */
    COUNT gbegndx;              /* Beginning index of field         */
    COUNT gcndx;                /* Current location in field        */
    COUNT gendndx;              /* End index of field               */
    COUNT gstart;               /* Column to start displaying       */
    COUNT gatend;               /* Passed the end of the field      */
    COUNT gredraw;              /* Redraw field                     */
    COUNT gfkey;                /* Flag for first key entered       */
    COUNT gid;                  /* Field id value                   */
    TEXT *gptr;                 /* Field name                       */
    TEXT *gxptr;                /* Extra pointer for programmer     */
    COUNT *gnbr;                /* Count pointer for programmer     */
    struct WINF *gwptr;         /* Window to get input              */
    };

struct SAY_NODE
    {
    struct SAY_NODE *snnext;    /* Next say node                    */ 
    struct WINF *snwptr;        /* Window for say                   */
    COUNT snctrl;               /* Control value for say            */
    COUNT snrow;                /* Row location                     */
    COUNT sncol;                /* Column location                  */
    TEXT *snfld;                /* Field to display                 */
    COUNT snattr;               /* Attribute to display             */
    COUNT snbrow;               /* Bottom row for box               */
    COUNT snbcol;               /* Bottom column for box            */
    };

struct GETTBL_NODE
    {   
    struct GETTBL_NODE *tnext;      /* Next get table               */
    struct GETTBL_NODE *tprevious;  /* Previous get table           */
    struct GET_NODE *thead;         /* Head of get nodes            */
    struct GET_NODE *ttail;         /* Tail of get nodes            */
    struct GET_NODE *tcurnode;      /* Current get node             */
    struct GET_NODE *tstartnode;    /* Start get node               */
    struct SAY_NODE *tsayhead;      /* Head of say nodes            */
    struct SAY_NODE *tsaytail;      /* Tail of say nodes            */
    TEXT *table_name;               /* Table name                   */
    COUNT tmagic;                   /* Table magic number           */
    COUNT tctrl;                    /* Table control value          */
    COUNT tstatus;                  /* Table status value           */
    COUNT tkeypress;                /* Last key pressed             */
    COUNT tinsmode;                 /* Insert mode setting for table*/
    struct WINF *twptr;             /* Window for table (not used)  */
    PFI tgetseq;                    /* Sequence function            */
    };

struct _VCPIC
    {
    struct _VCPIC *picnext;
    COUNT picchar;
    PFI picfunc;
    };

typedef struct _VCPIC VCPIC;
typedef struct GETTBL_NODE GETTABLE;
typedef struct GET_NODE GETITEM;
typedef struct SAY_NODE SAYITEM;

#ifndef VCGETVAR
extern COUNT userlevel;     /* Current user level (for security)    */
extern COUNT insmode;       /* Insert mode on or off                */
extern COUNT selmode;       /* Selection sets on or off             */
extern PFI checkmode;       /* Function to toggle insert mode       */
extern PFI vcstatus;        /* Program to print status message      */
extern GETTABLE *dftgettbl; /* Head of default get table list       */
extern COUNT dtblctrl;      /* Default get table control            */
extern COUNT datactrl[16];  /* Default get control                  */
extern VCPIC *vcpicture;    /* Structure of valid pictures          */
extern PFI datapre[16];     /* Data pre-functions                   */
extern PFI datapost[16];    /* Data post functions                  */
extern PFI datafunc[16];    /* Data execute functions               */
extern PFI datalight[16];   /* Data display active functions        */
extern PFI datainit[16];    /* Data type init function              */
extern PFI gethk1;          /* Get hook function number 1           */
extern PFI gethk2;          /* Get hook function number 2           */
extern PFI gethk3;          /* Get hook function number 3           */
extern PFI gethk4;          /* Get hook function number 4           */
#endif
