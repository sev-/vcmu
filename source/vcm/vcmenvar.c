/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:27
*
*   Name            vcmenvar - menu variable              
*                                   
*                                   
**/                                 

/*------------------------------------------------------------------*/
/*---------------------------Menu Variables-------------------------*/
/*------------------------------------------------------------------*/

#define VCMENVAR
#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

#ifdef VMS
COUNT vcldmn()
    {
    return(TRUE);
    }
#endif

struct VC_MENU *vcmchain; /* Pointer to chain of menus              */
struct VCM_STYLE vcmstyle =
    {
    (MENUSTYLE *)0, /* Pointer to next sytle                        */
    MSTYLEMAGIC,    /* Magic Number                                 */
    (TEXT *)"DEFAULT",/* Name for default style                     */
    VERTICAL,       /* Vertical menu                                */                                                
    AUTO,           /* Auto adjust size                             */
    0x1b,           /* vc.cyan+vc.bold+vc.bg*vc.blue                */
    0x71,           /* vc.blue+vc.bg*vc.white                       */
    0x13,           /* vc.cyan+vc.bg*vc.blue                        */
    0x9,            /* vc.blue+vc.bold                              */
    0,              /* Item Control                                 */
    0               /* Permission level                             */
    };

PFI vcmhk1=NULLFUNC;/* Menu hook function number 1                  */
PFI vcmhk2=NULLFUNC;/* Menu hook function number 2                  */
PFI vcmhk3=NULLFUNC;/* Menu hook function number 3                  */
PFI vcmhk4=NULLFUNC;/* Menu hook function number 4                  */
PFI vcmhk5=NULLFUNC;/* Menu hook function number 5                  */

PFI scrnfunc = NULLFUNC; /* Pointer to screen function              */
