/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:39
*
*   Name            vcsystem - make system call
*                                   
*   Description     This function sets up Vitamin C
*                   to make a system call.
*
*   Return Value    Returns what system returns
*                                   
**/

#include <vcstdio.h>

COUNT vcsystem(cmd,flag,msg)
TEXT *cmd;                  /* Command to execute                   */
COUNT flag;                 /* True to clear screen before call     */
TEXT *msg;                  /* Pause and print this message (askmsg)*/
    {                       /* ------------------------------------ */
    COUNT curstat;          /* Save the cursor status               */
    COUNT retval;           /* Value returned by the system call    */    
    VOID erase();           /* Declare functions used               */
    VOID vccurs();          /*    "        "      "                 */
    VOID wrefresh();        /*    "        "      "                 */
#ifdef TERMONLY
    VOID set_normal();      /*    "        "      "                 */
    VOID set_raw();         /*    "        "      "                 */
#endif
    if(flag)                            /* If we are to clear screen*/
        {                               /*                          */
        override = TRUE;                /* Go direct to screen      */
        erase();                        /* Erase the screen         */
        override = FALSE;               /* Restore override value   */
        }                               /*                          */
    curstat = vccursor;                 /* Save the cursor status   */
    if((vcterm.ge != NULLTEXT) && graphattr)    /* If graphics on   */
        {                               /*                          */
        dist_str(vcterm.ge,0);          /* Turn graphics off        */
        graphattr = FALSE;              /* Set graphics flag        */
        }                               /*                          */
    if(curstat > 2)                     /* Is the cursor off        */
        vccurs(ON);                     /* Turn the cursor on       */
#ifdef TERMONLY
    flipattr(normattr);                 /* Make attribute normal    */
    if(vcterm.es != NULLTEXT)           /* If there is exit string  */
        sendpstr(vcterm.es);            /* Send exit string         */
    set_normal();                       /* Set terminal normal      */
#endif
    retval = system(cmd);               /* Call system command      */
#ifdef UNIX
    set_raw();                          /* Set terminal in raw mode */
    if(vcterm.is != NULLTEXT)           /* Is there a setup string  */
        dist_str(vcterm.is,0);          /* Send setup string        */
#endif
    if(msg != NULLTEXT)                 /* If they want to pause    */
        askmsg(NULLTEXT,msg,0);         /* Display message          */
    wrefresh(flag);                     /* Redraw the screen        */
    if(curstat > 2)                     /* If cursor was off        */
        vccurs(OFF);                    /* Turn cursor off          */
    return(retval);                     /* Return the value         */
    }                                   /* ------------------------ */

