/**
*
*   Vitamin C Multi-User version 1.1
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .3 on 9/1/90 at 00:28:22
*
*   Name            vcprokey.h - Prokey header file
*                    
*
**/

struct VC_PROKEY
   {
   COUNT pro_magic;
   struct VC_PROKEY *pro_next;
   COUNT pro_keycode;
   PFI pro_func;
   TEXT *pro_aux;
   };

typedef struct VC_PROKEY VCPROKEY;

