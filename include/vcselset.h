/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:23
*
*   Name            vcselset.h  --  
*
*   Description     
*
**/

/*------------------------------------------------------------------*/
/*---------------------Selection Set Structures---------------------*/
/*------------------------------------------------------------------*/

struct PLIST
    {
    COUNT pl_ctrl;
    COUNT pl_wctrl;
    struct WINF *pl_wptr;
    TEXT *pl_wtitle;
    COUNT pl_urow;
    COUNT pl_ucol;
    COUNT pl_lrow;
    COUNT pl_lcol;
    COUNT pl_color;
    TEXT **pl_clist;
    };

struct SEL_ITEM
   {
   COUNT imagic;
   struct SEL_ITEM *inext;
   struct SEL_ITEM *iprev;
   TEXT *idisplay;
   TEXT *ivalue;
   };

typedef struct PLIST PICKLIST;
typedef struct SEL_ITEM SELSET;
