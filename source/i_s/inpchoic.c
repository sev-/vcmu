/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:08:47
*
*   Name            inpchoic.c  - Input choice
*                                   
*   Description     Get choice input
*
*   Return Value    
*                                   
**/

#define VCGET_DEFS
#include <vcstdio.h>

COUNT inpchoice(table)
GETTABLE *table;            /* Pointer to get table                 */
    {                       /* ------------------------------------ */
    TEXT **curptr;          /* Pointer to current item              */
    TEXT **headptr;         /* Points to head of list               */
    COUNT fldnbr;           /* Starting value of field              */
    COUNT cnt;              /* Temporary variable for counting      */
    GETITEM *gi;            /* Pointer to current get node          */
#ifdef VCDEBUG
    vcdebug = (TEXT *) "inpchoice:";    /* Set current function     */
    if(vcdbfunc != NULLFUNC)            /* If debug function        */
        (*vcdbfunc)(CONTINUE);          /* Call debug function      */
#endif
    gi = table->tcurnode;               /* Assign current node      */
    headptr = (TEXT **)gi->gselset;     /* Point to head of list    */
    curptr = headptr;                   /* Assign current to head   */
    fldnbr = (COUNT)(*gi->gtmpfld - '0');/* Find current field value*/
    cnt = fldnbr;                       /* Assign temporary variable*/
    while((*curptr != NULLTEXT ) && cnt--)  /* While not correct one*/
        curptr++;                       /* Point to next            */
    if(*curptr == NULLTEXT)             /* If field value to high   */
        {                               /*                          */
        fldnbr = 0;                     /* Reset to first item      */
        curptr = headptr;               /* Move current pointer     */
        }                               /*                          */
    while(TRUE)                         /* While not finished       */
        {                               /*                          */
#ifdef WINDOW
        if((gi->gwptr != (WPTR) 0) && !override)
            wat(gi->gwptr,gi->g_row,gi->g_col);  /* Address cursor  */
        else                            /*                          */
#endif
            at(gi->g_row,gi->g_col);    /* Address cursor           */
        table->tkeypress = getone();    /* Get next character       */
        if( gethk1 )                    /* If hook function         */
            if((*gethk1)(table))        /* If returns TRUE          */
                continue;               /* Get next character       */
        if(table->tkeypress == spkey.list_up)   /* If uplist pressed*/  
            {                           /*                          */
            if(curptr == headptr)       /* If at top of list        */
                bell();                 /* Beep at user             */
            else                        /*                          */
                {                       /*                          */
                curptr--;               /* Point to previous member */
                fldnbr--;               /* Decrement fld number     */
#ifdef WINDOW
                if((gi->gwptr != (WPTR) 0) && !override)
                    wxatsay(gi->gwptr,gi->g_row,gi->g_col,
                                            *curptr,gi->gcurattr);
                else                    /*                          */
#endif
                    xatsay(gi->g_row,gi->g_col,*curptr,gi->gcurattr);
                }                       /*                          */
            continue;                   /* Go to top of loop        */
            }                           /*                          */
        if(table->tkeypress == spkey.list_dn)   /* If down list     */ 
            {                           /*                          */
            curptr++;                   /* Point to next item       */
            if(*curptr == NULLTEXT)     /* If at end of list        */
                {                       /*                          */
                curptr--;               /* Go back to current       */
                bell();                 /* Beep at user             */
                }                       /*                          */
            else                        /*                          */
                {                       /*                          */
                fldnbr++;               /* Increment field number   */
#ifdef WINDOW
                if((gi->gwptr != (WPTR) 0) && !override)
                    wxatsay(gi->gwptr,gi->g_row,gi->g_col,
                                            *curptr,gi->gcurattr);
                else                    /*                          */
#endif
                    xatsay(gi->g_row,gi->g_col,*curptr,gi->gcurattr);
                }                       /*                          */
            continue;                   /* Go to top of loop        */
            }                           /*                          */
        if(table->tkeypress == spkey.fld_cleft) /* If cursor left   */
            table->tkeypress = spkey.fld_left;  /* Assign to exit   */
        if(table->tkeypress == spkey.fld_cright)/* If cursor right  */
            table->tkeypress = spkey.fld_right; /* Assign to exit   */
        if(isexitkey(table->tkeypress)) /* If exit key pressed      */
            break;                      /* Exit loop                */
        bell();                         /* Invalid key entered- beep*/
        }                               /*                          */
    *gi->gtmpfld = fldnbr + '0';        /* Assign current           */
    return(GOOD);                       /* Return good to leave     */
    }                                   /*                          */
