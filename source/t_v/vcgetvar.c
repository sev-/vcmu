/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:16:59
*
*   Name            vcgetvar.c  --                  
*
*
**/

/*------------------------------------------------------------------*/
/*--------------------------Used in gets----------------------------*/
/*------------------------------------------------------------------*/

#define VCGETVAR
#define VCGET_DEFS
#include <vcstdio.h>

#ifdef VMS
COUNT vcldgt()
    {
    return(TRUE);
    }
#endif

COUNT userlevel = 0;/* Current user security level                  */
COUNT insmode = 0;  /* If in Insert Mode                            */
COUNT selmode = TRUE;/* Selection Sets on or off                    */
PFI checkmode = NULLFUNC;/* Function to check editor modes          */
PFI vcstatus = NULLFUNC; /* Function to display status message      */
GETTABLE *dftgettbl = (GETTABLE *)0;/* Head of Default get table    */
VCPIC *vcpicture = (VCPIC *)0;      /* Structure of valid pictures  */
COUNT dtblctrl=MKCIRCLE;/* Default get table control                */
PFI dplist = NULLFUNC;/* Pointer to default picklist function       */
COUNT datactrl[16]= /* Default datactrl bytes                       */
    {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };
PFI datafunc[16] =  /* Data picture function                        */
    {
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC
    };
PFI datapre[16] =   /* Data pre-functions                           */
    {
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC
    };
PFI datapost[16] =  /* Data post-functions                          */
    {
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC
    };
PFI datalight[16] =   /* Data display-functions                     */
    {
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC
    };
PFI datainit[16] =   /* Data display-functions                     */
    {
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC,
    NULLFUNC,NULLFUNC,NULLFUNC,NULLFUNC
    };
PFI gethk1 = NULLFUNC;/* Get hook function number 1                 */
PFI gethk2 = NULLFUNC;/* Get hook function number 2                 */
PFI gethk3 = NULLFUNC;/* Get hook function number 3                 */
PFI gethk4 = NULLFUNC;/* Get hook function number 4                 */
