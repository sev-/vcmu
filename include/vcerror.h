/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:03
*
*   Name            vcerror.h  --  Error Messages
*
*   Description     
*
*
**/

/*----------------------------------------------------------------------*/
/*-------------------------Error Messages-------------------------------*/
/*----------------------------------------------------------------------*/

#define NOGETMEM     1 /* Out of memory.                                */
#define NOSAYMEM     2
#define NOTMPMEM     3
#define NOSTRMEM     4
#define NONUMMEM     5
#define NOTBLMEM     6
#define NONAMMEM     7
#define BADGTBL      8 /* Pointer to get table is NULL or not valid     */
#define XRDBADGTBL   9
#define SEQBADGTBL  10
#define NOGETBL     11 /* No get table nodes defined                    */
#define NOSYM       12 /* Symbol not found                              */
#define SYMREQ      13 /* Symbol required. (NULL not allowed)           */
#define NOGETAUTH   14 /* User not authorized for operation             */
#define NOSAYAUTH   15
#define BADGET      16 /* Pointer to get node is NULL or is not valid   */
#define LTORBADGET  17
#define RTOLBADGET  18
#define XRDBADGET   18
#define NOGETS      19
#define XRDNOGETS   20 /* No "gets" have been issued on this get table  */
#define NOTABLE     21
#define BADTABLE    22
#define SCRMEM      23 /* Error Allocating screen  (wprep)              */
#define BSCRMEM     24 /* Error Allocating backup screen  (wprep)       */
#define TSCRMEM     25 /* Error Allocating terminal screen (wprep)      */
#define WPTRMEM     26 /* Error Allocating winfo structure (wsetup)     */
#define WLOCMEM     27 /* Error Allocating window data (wsetup)         */
#define PEEMEM      28 /* Error Allocating terminal buffer (vcpee)      */
#define NODEMEM     29 /* Error Allocating key table node (addtable)    */
#define TCAPMEM     30 /* Error Allocating termcap buffer (vctinit)     */
#define VCTRLMEM    31 /* Error Allocating Terminal Memory (vctinit)    */
#define TLBLMEM     32 /* Error Allocating Label Struct Memory (vctinit)*/
#define WCTRLMEM    33 /* Error Allocating Memory for Window Control    */
#define VCAPERR     34 /* Termcap error openning terminal (vctinit)     */
#define CUROPEN     35 /* Trying to Open window Already open  (winit)   */
#define WSTRUCT     36 /* Window Structure in use (wsetup)              */
#define WCORD       37 /* Opening a window with invalid row/col(wxxopen)*/
#define WTBCOORD    38 /* Bad Coord. in tempory border (wrtb)           */
#define SHOWNOTOPEN 39 /* Trying to show a window not open  (wshow)     */
#define SELNOTOPEN  40 /* Trying to select a window not open  (wselect) */
#define SCRNOTOPEN  41 /* Trying to scroll a window not open  (wscroll) */
#define PUTNOTOPEN  42 /* Putting a char. on a window not open(wputchr) */
#define PANOTOPEN   43 /* Putting a Attr on a window not open (wputattr)*/
#define MVNOTOPEN   44 /* Trying to move window not open (wmove)        */
#define MVCOORD     45 /* Invalid row and col on move  (wmove)          */
#define HIDNOTOPEN  46 /* Trying to hide window not open (whide)        */
#define CLNOTOPEN   47 /* Trying to close window not open (wclose)      */
#define ATNOTOPEN   48 /* Trying to address window not open (wat)       */
#define OUTTERMAREA 49 /* Ran out of space in terminal init. (vctinit)  */
#define NOROOM      50 /* Not a Error just no room on the screen        */
#define BADMENU      9 /* Pointer to menu is NULL or not valid          */
#define BADMITEM    10 /* Pointer to menu item is NULL or not valid     */
#define BADMSTYLE   11 /* Pointer to menu style is NULL or not valid    */
#define ONLYMSTYLE  12 /* There is only one style in the style list     */
#define NOMSTYLE    13 /* No matching menu style was found              */
#define CANNOT      14 /* Unable to do desired operation                */
#define BADED       16 /* Pointer to ed node is NULL or not valid       */
#define EDBUF       17 /* editor buffer is full                         */
#define FNTOPN      18 /* error opening disk file                       */
#define SYMEXIST    19 /* symbol already exists                         */
#define BADCORD     20 /* invalid coordinates                           */
#define BADSET      21 /* Pointer to selection set is NULL or invalid   */
#define BADSITM     22 /* Pointer to selection item is NULL or invalid  */
#define SETEMPT     23 /* selection set is empty                        */
#define VCSYMEXTS   24 /* Prokey symbol exists                          */
#define VCNOSYM     25 /* No symbol for key                             */
#define NOMEM       26 /* No memory in addprokey                        */
