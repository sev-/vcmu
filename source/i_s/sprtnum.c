/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:10:22
*
*   Name            sprtnum.c  --  String print number
*
*   Description     This function takes the string field and formats
*                   it according with the picture and places the 
*                   newly formatted string into buf
*
*   Return Value    Returns 0 if not full, 1 if full
*
**/

#include <vcstdio.h>

COUNT sprtnum(buf,fld,pic)
TEXT *buf;                  /* Buffer to put formatted string       */
TEXT *fld;                  /* Field to format                      */
TEXT *pic;                  /* Picture of format                    */
    {                       /* ------------------------------------ */
    COUNT retval = FALSE;   /* Return if picture is full            */
    TEXT *bcur,*fcur,*pcur; /* Current location for fields          */
    TEXT *bend;             /* Last location in buf for characters  */
    TEXT *fend = NULLTEXT;  /* Last character in field              */
    TEXT floatchr = ' ';    /* Float character                      */
    COUNT fillchrs = FALSE; /* True to fill with floatchr           */
    COUNT nodata = FALSE;   /* True when out of data from field     */
    COUNT overflow = FALSE; /* Did we overflow field                */
    COUNT evalpic();        /* Evalute picture function             */
    TEXT *strchr();         /* Declare functions used               */
#ifdef VCDEBUG
    vcdebug = (TEXT *) "sprtnum:";      /* Define current function  */
    if(vcdbfunc != NULLFUNC)            /* If debug function        */
        (*vcdbfunc)(CONTINUE);          /* Call debug function      */
#endif
    bend = buf;                         /* Buffers ends at beginning*/
    if((strchr(pic,'-') != NULLTEXT) && /* If picture contains '-'  */
       (strchr(fld,'-') == NULLTEXT)  ) /* And field does not       */
        bend++;                         /* Increment leading spaces */
    if(!evalpic(*pic) && (*pic != '-')) /* Is first character spec. */
        {                               /*                          */
        bend++;                         /* Increment leading spaces */
        floatchr = *pic;                /* Assign floating character*/        
        if(*pic == *(pic+1))            /* If two in row            */
            fillchrs = TRUE;            /* Flag fill characters     */
        }                               /*                          */
    bcur = buf;                         /* Start at first of buffer */
    pcur = pic;                         /* Start at first of picture*/
    while(*pcur != '\0')                /* While not at end         */
        {                               /*                          */
        bcur++;                         /* Increment buffer pointer */
        pcur++;                         /* Move to next location    */
        }                               /*                          */
    *(bcur--) = '\0';                   /* Null terminate buffer    */
    pcur--;                             /* Point to last char.      */
    fcur = fld;                         /* Start at first of field  */
    while(*(fcur+1) != '\0')            /* While not at end         */
        {                               /*                          */
        if(*fcur != ' ')                /* Skip leading spaces      */
            if(fend == NULLTEXT)        /* If end not defined       */
                fend = fcur;            /* Assign end of string loc.*/
        fcur++;                         /* Move to next location    */
        }                               /*                          */
    if(fend == NULLTEXT)                /* If end still not defined */
        if(*fcur == ' ')                /* If last character empty  */
            fend = fcur+1;              /* Point to null no char.   */
        else                            /*                          */
            fend = fcur;                /* Point to last character  */
    while(bcur >= buf)                  /* Start moving strings     */
        {                               /*                          */
        if(nodata)                      /* If no more data          */
            {                           /*                          */
            if(fillchrs)                /* If fill field            */
                *(bcur--) = floatchr;   /* Insert fill character    */
            else                        /*                          */
                *(bcur--) = ' ';        /* Put in space             */
            continue;                   /* Next character           */
            }                           /*                          */
        if(!evalpic(*pcur) && (fcur >= fend) &&/* If current a mask */
               (*pcur != floatchr) &&   /* And not float character  */
               (*pcur != '-')      &&   /* And not minus picture    */
               (*fcur != '-')      &&   /* And not minus sign       */
               (*fcur != '+')        )  /* And not plus sign        */
            {                           /*                          */
            if(*fcur == *pcur)          /* If same (prob. decimal)  */
                fcur--;                 /* Move to next character   */
            *(bcur--) = *(pcur--);      /* Move to buffer           */
            continue;                   /* Next character           */
            }                           /*                          */
        if(fcur >= fend)                /* If field not at end      */
            {                           /*                          */
            *(bcur--) = *(fcur--);      /* Move field to buffer     */
            pcur--;                     /* Move picture pointer     */
            if(bcur < bend)             /* If at end                */
                {                       /*                          */
                if((fcur >= fld) && (fcur >= fend)) /* If more chars*/
                    {                   /*                          */
                    overflow = TRUE;    /* Overflowed space         */
                    break;              /* Exit loop                */
                    }                   /*                          */
                else                    /*                          */
                    retval = TRUE;      /* Return full              */
                }
            continue;                   /* Next character           */
            }                           /*                          */
        nodata = TRUE;                  /* No more data             */
        if(bcur < bend)                 /* If field is full         */
            retval = TRUE;              /* Return field is full     */
        if(floatchr != ' ')             /* If float character       */
            *(bcur--) = floatchr;       /* Assign float character   */
        }                               /*                          */
    if(overflow)                        /* If the field was overflow*/
        {                               /*                          */
        retval = -1;                    /* Return overflowed        */
        while(*buf != '\0')             /* While not at end         */
            *(buf++) = '*';             /* Fill with '*'            */
        }                               /*                          */
    return(retval);                     /* Return if field full     */
    }                                   /* ------------------------ */
        
