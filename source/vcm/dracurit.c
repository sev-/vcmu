/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:24:03
*
*   Name            dracuritm -- draws current menu item                 
*                                   
*   Description     Draws current menu item.  Handles blank
*                   items, separators, and unavailable items too.
*
*   Return Value    Returns -1 if error
*                                   
**/                                 
      
#define VCM_DEFS
#define VCERROR_DEFS
#include <vcstdio.h>

COUNT dracuritm(m)
VCMENU *m;          /* Pointer to menu                              */
   {
   COUNT attr,ofst,bdcolofst=1,bdlinofst=0;
   TEXT chkmrk[2];
   COUNT gattr;
   VOID box();
   VOID at();
   VOID vcputc();
   VOID xatsay();
   COUNT strlen();
   if( m == (VCMENU *)0 || m->mmagic != MENUMAGIC )
      {
      vcerror = BADMENU;
      return(-1);
      }
   if( m->mcuritmptr == (MENUITEM *)0 || m->mcuritmptr->emagic != MITEMMAGIC )
      {
      vcerror = BADMITEM;
      return(-1);
      }
   chkmrk[0] = border[0].scr_rcur;
   chkmrk[1]='\0';
   if( m->mchecks )
      ofst=1;
   else
      ofst=0;

   if( m->mstyle & BORDERLESS )
      {
      bdcolofst = 0;
      bdlinofst = -1;
      }

   if( m->mcuritmptr->ectrl & UNAVAILABLE )
      {
      attr=m->munavattr;
      }
   else
      {
      if( m->mcuritmptr->ectrl & SEPARATOR )
         {
         if( m->mstyle & VERTICAL )
            {
            box(m->mcuritmptr->eitemnbr+bdlinofst,bdcolofst,
                m->mcuritmptr->eitemnbr+bdlinofst,m->mmnuwid-bdcolofst,
                1, (m->mnormattr & 0xf0) + (m->mbordattr & 0xf) );
            }
         else
            {
            gattr = (m->mnormattr & 0xf0) + (m->mbordattr & 0xf);
            at(m->mcuritmptr->ehcoords >> 8,m->mcuritmptr->ehcoords & 0xff);
            vcputc(border[1].up,gattr);
            }
                
         if( !(m->mstyle & BORDERLESS) )
            {
            if( m->mstyle & VERTICAL )
               {
               gattr = m->mbordattr;
               at(m->mcuritmptr->eitemnbr,0);
               vcputc(border[1].lside,gattr);
               at(m->mcuritmptr->eitemnbr,m->mmnuwid);
               vcputc(border[1].rside,gattr);
               }
            else
               {
               if( m->mwptr->depth == 3 )
                  {
                  gattr = m->mbordattr;
                  at(0,m->mcuritmptr->ehcoords & 0xff);
                  vcputc(border[1].mt,gattr);
                  at(2,m->mcuritmptr->ehcoords & 0xff);
                  vcputc(border[1].mb,gattr);
                  }
               }
            }
         return(0);
         }
      else
         attr=m->mnormattr;
      }
   if( m->mcuritmptr->ectrl & BLANKITEM )
      return(0);

   if( m->mstyle & VERTICAL )
      {
      if( m->mchecks && (m->mcuritmptr->ectrl & CHECKED) )
         {
         if( *m->mcuritmptr->eparm.pnumptr )
            xatsay(m->mcuritmptr->eitemnbr+bdlinofst,bdcolofst,chkmrk,attr);
         else
            xatsay(m->mcuritmptr->eitemnbr+bdlinofst,bdcolofst,(TEXT *)" ",attr);
         }
      xatsay(m->mcuritmptr->eitemnbr+bdlinofst,bdcolofst+ofst,
              m->mcuritmptr->eitemname,attr);
      if(m->mcuritmptr->ekeyname)
         xatsay(m->mcuritmptr->eitemnbr+bdlinofst,
             m->mitemwid+ofst+bdcolofst+1+(m->mknamwid-
             strlen(m->mcuritmptr->ekeyname)),
             m->mcuritmptr->ekeyname,attr);
      }
   if( m->mstyle & HORIZONTAL )
      {
      xatsay(m->mcuritmptr->ehcoords >> 8,
         m->mcuritmptr->ehcoords & 0xff,
         m->mcuritmptr->eitemname,attr);
      }
   return(0);
   }




