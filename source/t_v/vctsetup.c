/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .5 on 9/2/90 at 14:29:41
*
*   Name            vctsetup.c - terminal setup structures
*                                   
*   Description     Hold the terminal setup structures or
*                   loads predefine setup structures from
*                   the vctsetup.h file
*                                   
**/

#define vcglobal
#include <vcstdio.h>
#include <vctsetup.h>

#ifndef VCTERMDEF

/*------------------------------------------------------------------*/
/*----------------------Terminal Variables--------------------------*/
/*------------------------------------------------------------------*/

struct termctrl vcterm;     /* Vitamin C terminal defines           */
struct vckeys vckey;        /* Terminal key structure               */

/*------------------------------------------------------------------*/
/*------------------------Border Structure--------------------------*/
/*------------------------------------------------------------------*/

#ifdef TERMONLY
struct BODR border[3] =
    {
    0x7c,           /* Character to Print Up the Screen (GV)        */
    0x3d,           /* Character to Print Across the Screen (GH)    */
    0x7c,           /* Top Left Character               (G2)        */
    0x7c,           /* Top Right Character              (G1)        */
    0x7c,           /* Bottom Left Character            (G3)        */
    0x7c,           /* Bottom Right Character           (G4)        */
    0x7c,           /* Merge with Left Side Character   (GL)        */
    0x7c,           /* Merge with Right Side Character  (GR)        */
    0x3d,           /* Merge with Bottom Character      (GU)        */
    0x3d,           /* Merge with Top Character         (GD)        */
    0x7c,           /* Middle Intersection              (GC)        */
    0,              /* Side Across Character            (GA)        */
    0,              /* Bottom up Character              (GB)        */
    0,              /* Scroll Side Character            (GF)        */
    0,              /* Scroll Bottom Character          (GI)        */
    0,              /* Scroll Top Character             (GJ)        */
    0,              /* Scroll Bottom Character          (GK)        */
    0,              /* Scroll Left Character            (GM)        */
    0,              /* Scroll Right Character           (GN)        */
    0x3e,           /* Scroll Right Current Location Char  (GO)     */
    0,              /* Scroll Bottom Current Location Char (GP)     */
    0x7c,           /* Character to Print Up the Screen    (gv)     */
    0x3d,           /* Character to Print Across the Screen    (gh) */
    0x7c,           /* Top Left Character                  (g2)     */
    0x7c,           /* Top Right Character                 (g1)     */
    0x7c,           /* Bottom Left Character               (g3)     */
    0x7c,           /* Bottom Right Character              (g4)     */
    0x7c,           /* Merge with Left Side Character      (gl)     */
    0x7c,           /* Merge with Right Side Character     (gr)     */
    0x3d,           /* Merge with Bottom Character         (gu)     */
    0x3d,           /* Merge with Top Character            (gd)     */
    0x7c,           /* Middle Intersection                 (gc)     */
    0,              /* Side Across Character               (ga)     */
    0,              /* Bottom up Character                 (gb)     */
    0,              /* Scroll Side Character               (gf)     */
    0,              /* Scroll Bottom Character             (gi)     */
    0,              /* Scroll Top Character                (gj)     */
    0,              /* Scroll Bottom Character             (gk)     */
    0,              /* Scroll Left Character               (gm)     */
    0,              /* Scroll Right Character              (gn)     */
    0x3e,           /* Scroll Right Current Location Char     (go)  */
    0,              /* Scroll Bottom Current Location Char    (gp)  */
    0x7c,           /* Character to Print Up the Screen             */
    0x3d,           /* Character to Print Across the Screen         */
    0x7c,           /* Top Left Character                           */
    0x7c,           /* Top Right Character                          */
    0x7c,           /* Bottom Left Character                        */
    0x7c,           /* Bottom Right Character                       */
    0x7c,           /* Merge with Left Side Character               */
    0x7c,           /* Merge with Right Side Character              */
    0x3d,           /* Merge with Bottom Character                  */
    0x3d,           /* Merge with Top Character                     */
    0x7c,           /* Middle Intersection                          */
    0,              /* Side Across Character                        */
    0,              /* Bottom up Character                          */
    0,              /* Scroll Side Character                        */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Top Character                         */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Left Character                        */
    0,              /* Scroll Right Character                       */
    0x3e,           /* Scroll Right Current Location Char           */
    0               /* Scroll Bottom Current Location Char          */
    };
#endif

#ifdef IBM
struct BODR border[3] =
    {
    0xba,           /* Character to Print Up the Screen (GV)        */
    0xcd,           /* Character to Print Across the Screen (GH)    */
    0xc9,           /* Top Left Character               (G2)        */
    0xbb,           /* Top Right Character              (G1)        */
    0xc8,           /* Bottom Left Character            (G3)        */
    0xbc,           /* Bottom Right Character           (G4)        */
    0xcc,           /* Merge with Left Side Character   (GL)        */
    0xb9,           /* Merge with Right Side Character  (GR)        */
    0xca,           /* Merge with Bottom Character      (GU)        */
    0xcb,           /* Merge with Top Character         (GD)        */
    0xce,           /* Middle Intersection              (GC)        */
    0,              /* Side Across Character            (GA)        */
    0,              /* Bottom up Character              (GB)        */
    0,              /* Scroll Side Character            (GF)        */
    0,              /* Scroll Bottom Character          (GI)        */
    0,              /* Scroll Top Character             (GJ)        */
    0,              /* Scroll Bottom Character          (GK)        */
    0,              /* Scroll Left Character            (GM)        */
    0,              /* Scroll Right Character           (GN)        */
    0xaf,           /* Scroll Right Current Location Char  (GO)     */
    0,              /* Scroll Bottom Current Location Char (GP)     */
    0xb3,           /* Character to Print Up the Screen    (gv)     */
    0xc4,           /* Character to Print Across the Screen    (gh) */
    0xda,           /* Top Left Character                  (g2)     */
    0xbf,           /* Top Right Character                 (g1)     */
    0xc0,           /* Bottom Left Character               (g3)     */
    0xd9,           /* Bottom Right Character              (g4)     */
    0xc3,           /* Merge with Left Side Character      (gl)     */
    0xb4,           /* Merge with Right Side Character     (gr)     */
    0xc1,           /* Merge with Bottom Character         (gu)     */
    0xc2,           /* Merge with Top Character            (gd)     */
    0xc5,           /* Middle Intersection                 (gc)     */
    0,              /* Side Across Character               (ga)     */
    0,              /* Bottom up Character                 (gb)     */
    0,              /* Scroll Side Character               (gf)     */
    0,              /* Scroll Bottom Character             (gi)     */
    0,              /* Scroll Top Character                (gj)     */
    0,              /* Scroll Bottom Character             (gk)     */
    0,              /* Scroll Left Character               (gm)     */
    0,              /* Scroll Right Character              (gn)     */
    0xaf,           /* Scroll Right Current Location Char     (go)  */
    0,              /* Scroll Bottom Current Location Char    (gp)  */
    0xb3,           /* Character to Print Up the Screen             */
    0xcd,           /* Character to Print Across the Screen         */
    0xd5,           /* Top Left Character                           */
    0xb8,           /* Top Right Character                          */
    0xd4,           /* Bottom Left Character                        */
    0xbe,           /* Bottom Right Character                       */
    0xc6,           /* Merge with Left Side Character               */
    0xb5,           /* Merge with Right Side Character              */
    0xcf,           /* Merge with Bottom Character                  */
    0xd1,           /* Merge with Top Character                     */
    0xd8,           /* Middle Intersection                          */
    0,              /* Side Across Character                        */
    0,              /* Bottom up Character                          */
    0,              /* Scroll Side Character                        */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Top Character                         */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Left Character                        */
    0,              /* Scroll Right Character                       */
    0xaf,           /* Scroll Right Current Location Char           */
    0               /* Scroll Bottom Current Location Char          */
    };
#endif

#ifdef OS2
struct BODR border[3] =
    {
    0xba,           /* Character to Print Up the Screen (GV)        */
    0xcd,           /* Character to Print Across the Screen (GH)    */
    0xc9,           /* Top Left Character               (G2)        */
    0xbb,           /* Top Right Character              (G1)        */
    0xc8,           /* Bottom Left Character            (G3)        */
    0xbc,           /* Bottom Right Character           (G4)        */
    0xcc,           /* Merge with Left Side Character   (GL)        */
    0xb9,           /* Merge with Right Side Character  (GR)        */
    0xca,           /* Merge with Bottom Character      (GU)        */
    0xcb,           /* Merge with Top Character         (GD)        */
    0xce,           /* Middle Intersection              (GC)        */
    0,              /* Side Across Character            (GA)        */
    0,              /* Bottom up Character              (GB)        */
    0,              /* Scroll Side Character            (GF)        */
    0,              /* Scroll Bottom Character          (GI)        */
    0,              /* Scroll Top Character             (GJ)        */
    0,              /* Scroll Bottom Character          (GK)        */
    0,              /* Scroll Left Character            (GM)        */
    0,              /* Scroll Right Character           (GN)        */
    0xaf,           /* Scroll Right Current Location Char  (GO)     */
    0,              /* Scroll Bottom Current Location Char (GP)     */
    0xb3,           /* Character to Print Up the Screen    (gv)     */
    0xc4,           /* Character to Print Across the Screen    (gh) */
    0xda,           /* Top Left Character                  (g2)     */
    0xbf,           /* Top Right Character                 (g1)     */
    0xc0,           /* Bottom Left Character               (g3)     */
    0xd9,           /* Bottom Right Character              (g4)     */
    0xc3,           /* Merge with Left Side Character      (gl)     */
    0xb4,           /* Merge with Right Side Character     (gr)     */
    0xc1,           /* Merge with Bottom Character         (gu)     */
    0xc2,           /* Merge with Top Character            (gd)     */
    0xc5,           /* Middle Intersection                 (gc)     */
    0,              /* Side Across Character               (ga)     */
    0,              /* Bottom up Character                 (gb)     */
    0,              /* Scroll Side Character               (gf)     */
    0,              /* Scroll Bottom Character             (gi)     */
    0,              /* Scroll Top Character                (gj)     */
    0,              /* Scroll Bottom Character             (gk)     */
    0,              /* Scroll Left Character               (gm)     */
    0,              /* Scroll Right Character              (gn)     */
    0xaf,           /* Scroll Right Current Location Char     (go)  */
    0,              /* Scroll Bottom Current Location Char    (gp)  */
    0xb3,           /* Character to Print Up the Screen             */
    0xcd,           /* Character to Print Across the Screen         */
    0xd5,           /* Top Left Character                           */
    0xb8,           /* Top Right Character                          */
    0xd4,           /* Bottom Left Character                        */
    0xbe,           /* Bottom Right Character                       */
    0xc6,           /* Merge with Left Side Character               */
    0xb5,           /* Merge with Right Side Character              */
    0xcf,           /* Merge with Bottom Character                  */
    0xd1,           /* Merge with Top Character                     */
    0xd8,           /* Middle Intersection                          */
    0,              /* Side Across Character                        */
    0,              /* Bottom up Character                          */
    0,              /* Scroll Side Character                        */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Top Character                         */
    0,              /* Scroll Bottom Character                      */
    0,              /* Scroll Left Character                        */
    0,              /* Scroll Right Character                       */
    0xaf,           /* Scroll Right Current Location Char           */
    0               /* Scroll Bottom Current Location Char          */
    };
#endif

#endif
