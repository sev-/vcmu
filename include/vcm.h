/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:20
*
*   Name            vcm.h  --  Structure Definations
*
*   Description
*
*
**/

/*------------------------------------------------------------------*/
/*-------------------------Menu Structures--------------------------*/
/*------------------------------------------------------------------*/

struct VCM_STYLE
   {
   struct VCM_STYLE *snext;
   COUNT smagic;
   TEXT *stylename;
   COUNT mnustyle;
   COUNT swidth;
   COUNT snormattr;
   COUNT sbarattr;
   COUNT sunavattr;
   COUNT sbordattr;
   COUNT sitmctrl;
   COUNT spermlvl;
   };

struct VC_MENU
   {
   struct VC_MENU *mnext;
   struct VC_MENU *mprev;
   struct VC_MENU *mcalledby; /* Pointer to menu that called this one */
   COUNT mmagic;
   TEXT *menuname;
   COUNT mstyle;
   COUNT mrow;
   COUNT mcol;
   COUNT mwidth;
   struct VCM_ITEM *mitemhead;
   struct VCM_ITEM *mitemtail;
   struct VCM_ITEM *mcuritmptr;
   COUNT mcuritmnbr;
   COUNT mnormattr;
   COUNT mbarattr;
   COUNT munavattr;
   COUNT mbordattr;
   TEXT *mhelpkey;
   COUNT mitemcnt;
   COUNT mitemwid;
   COUNT mknamwid;
   COUNT mchecks;
   COUNT mmnuwid;
   COUNT mpermlvl;
   struct WINF *mwptr;
   COUNT mwno;
   COUNT mresult;
   COUNT mfuncret;
   COUNT mkeyhit;
   TEXT *mstatus;
   };

union VCM_PARM
   {
   COUNT *pnumptr;
   TEXT *pchrptr;
   struct VC_MENU *pmnuptr;
   };
 
struct VCM_ITEM
   {
   struct VCM_ITEM *enext;
   struct VCM_ITEM *eprev;
   COUNT emagic;
   TEXT *eitemname;
   TEXT *ekeyname;
   COUNT ekeynum;
   PFI efunc;
   union VCM_PARM eparm;
   COUNT *echkvar;
   TEXT *ehelpkey;
   COUNT eitemnbr;
   COUNT ehcoords;
   COUNT ectrl;
   TEXT *estat;
   COUNT emctrl;
   TEXT *embuf;
   };

typedef struct
    {
    TEXT *istylename;
    COUNT imnustyle;
    COUNT iswidth;
    COUNT isnormattr;
    COUNT isbarattr;
    COUNT isunavattr;
    COUNT isbordattr;
    COUNT isitmctrl;
    COUNT ispermlvl;
    } SSTYLES;

typedef struct 
    {
    TEXT *smnunam;
    COUNT srow;
    COUNT scol;
    TEXT *shlpkey;
    TEXT *sstyle;
    } SMENUS;
   
typedef struct 
    {
    TEXT *imenu;
    TEXT *iitem;
    TEXT *ikeynam;
    COUNT ikeynum;
    PFI ifunc;
    TEXT *iparm;
    TEXT *istat;
    TEXT *ihlpkey;
    COUNT ictrl;
    COUNT imctrl;
    TEXT *imbuf;
    } SMENUITEMS;

typedef struct VCM_STYLE MENUSTYLE;
typedef struct VC_MENU VCMENU;
typedef struct VCM_ITEM MENUITEM;

#ifndef VCMENVAR
extern struct VCM_STYLE vcmstyle;
extern struct VC_MENU *vcmchain;
extern PFI vcmhk1;
extern PFI vcmhk2;
extern PFI vcmhk3;
extern PFI vcmhk4;
extern PFI vcmhk5;
extern PFI scrnfunc;
#endif

/*------------------------------------------------------------------*/
/*---------------------------End of File----------------------------*/
/*------------------------------------------------------------------*/

