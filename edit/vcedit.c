/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 21:50:59
*
*   Name            vcedit.c - edit
*                                   
*   Description     Head of the party.  This is the command center
*                   for the editor
*
*   Return Value    Returns O.K.
*                                   
**/

#include <vcstdio.h>
#include <vcdbms.h>
#include <vced.h>

COUNT vcedit(vced)
VCED *vced;                 /* Pointer to edit structure            */
    {                       /* ------------------------------------ */
    VOID vcedwopen();       /* Declare functions used               */
    COUNT vcedptrbuf();     /*    "        "      "                 */
    COUNT vcedexec();       /*    "        "      "                 */
    if(vced->edwptr == (WPTR)0)         /* If window not open       */
        {                               /*                          */
        vcedwopen(vced);                /* Open window              */ 
        vcedprtbuf(vced);               /* Display buffer           */
        }                               /*                          */
    else                                /* Window open so select    */
        wselect(vced->edwptr);          /* to be sure on top        */
    while(vced->edmail < 9990)          /* While not ready to exit  */
        {                               /*                          */
        vcedupdate(vced);               /* Do any updates           */
#ifdef VCEDFULL
        vcedunvced(vced);               /* Add vced to undo buffer  */
#endif
        vced->edkey[2] = vced->edkey[1];/* Move key down one        */
        vced->edkey[1] = vced->edkey[0];/* Move key down one        */
        vced->edkey[0] = getone();      /* Get key                  */
#ifdef VCEDFULL
        if(vcedrecstat)                 /* If recording             */
            vcedreckey(vced);           /* Record key               */
#endif
        vcedexec(vced);                 /* Execute key pressed      */
        }                               /*                          */
    }                                   /* ------------------------ */

