/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:17:11
*
*   Name            vckeyset.c -- Key setup
*
*   Description     Sets up the spkey structure used by Terminal
*                   Control to control actions of it's own 
*                   functions.   
*                   
*   Return Value    VOID
*
**/

#include <vcstdio.h>

COUNT splist[34]=
    {
    4000,   /*  Exit Key            -   Esc                         */
    5000,   /*  Help Key            -   F0                          */
    5000,   /*  Exit Help           -   F0                          */
    5001,   /*  Window Adjust Key   -   F1                          */
    4019,   /*  Done                -   Enter Key                   */
    4002,   /*  Field Return        -   Ret                         */
    4011,   /*  Field End           -   End Key                     */
    4010,   /*  Field Home          -   Home Key                    */
    4006,   /*  Field Cursor Left   -   Cursor Left                 */
    4007,   /*  Field Cursor Right  -   Cursor Right                */
    4001,   /*  Field Backspace     -   Backsp                      */
    4015,   /*  Field Delete        -   Delete Key                  */
    4017,   /*  Field Blank         -   Delete Line                 */
    4024,   /*  Field Del End of ln -   Delete Left Key             */
    4014,   /*  Field Insert        -   Insert Key                  */
    4005,   /*  Field Left          -   Back Tab                    */
    4004,   /*  Field Right         -   Tab                         */
    4009,   /*  Field Down          -   Cursor Down                 */
    4008,   /*  Field Up            -   Cursor Up                   */
    4013,   /*  Field Page Down     -   Page Down                   */
    4012,   /*  Field Page Up       -   Page Up                     */
    5010,   /*  Field mode          -   Eleventh function key       */
    4009,   /*  List Down           -   Cursor Down                 */
    4008,   /*  List Up             -   Cursor Up                   */
    4006,   /*  List Left           -   Cursor Left                 */
    4007,   /*  List Right          -   Cursor Right                */
    4012,   /*  List Page Up        -   Page Up                     */
    4013,   /*  List Page Down      -   Page Down                   */
    4010,   /*  List Home           -   Home Key                    */
    4011,   /*  List End            -   End Key                     */
    4021,   /*  Print Screen        -   Print Key                   */
    4003,   /*  Screen Refresh      -   Break Key                   */
    4019,   /*  Mouse On            -   Enter Key                   */
    9999    /*  End of List                                         */
    };

VOID vckeyset()
    {
    COUNT *nextkey,*present,*ofset;
    VOID vcpicset();
#ifdef VCDEBUG
    vcdebug = (TEXT *) "vckeyset:";
    if(vcdbfunc != NULLFUNC)
        (*vcdbfunc)(CONTINUE);
#endif
    vcpicset();
    nextkey = &spkey.abort;
    present = &splist[0];
    ofset = &vckey.esc;
    while( *present != 9999)
        {
        if((*present < 5000) && (*present > 3999))
            *(nextkey++) = *(ofset+(*(present++)-4000));
        else
            *(nextkey++) = *(present++);
        }
    }

COUNT vcalpha(),vcany(),vcdigit(),vcsdigit(),vcyesno();

VOID vcpicset()
    {
    addpic('X',vcany);
    addpic('x',vcany);
    addpic('#',vcdigit);
    addpic('9',vcsdigit);
    addpic('A',vcalpha);
    addpic('a',vcalpha);
    addpic('Y',vcyesno);
    addpic('y',vcyesno);
    }


