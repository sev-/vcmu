/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:05:02
*
*   Name            filtowdo.c  --  load file to window
*
*   Description     Opens a window file and loads contents from
*                   disk. 
*
*   Return Value    Returns window pointer or NULL if error
*                    
*
**/

#include <vcstdio.h>

#ifdef USESHORT
#define SCANVALUE "%hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd %hd"
#else
#define SCANVALUE "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
#endif

WPTR filtowdo(fnam)
TEXT *fnam;         /* Name of window file                          */
    {
    FILE *vcfopen(),*fp;
    WPTR wptr;
    WPTR wxxopen();
    TEXT *vcalloc(),*trim();
    COUNT wlen;
    COUNT upper_r, upper_c, lower_r, lower_c, control, depth, width, fill_ch;
    COUNT border_at, bg_at, say_at, get_at, nget_at, tit_at, c_pos, r_pos;
    COUNT cur_r, cur_c;
    COUNT isactive;
    TEXT buf[200];
    COUNT strlen();
    TEXT *strcpy();
    VOID vcfree();
    COUNT vcfclose();
    COUNT wshow();
    if( (fp=vcfopen(fnam,VCF_RB)) == (FILE *) 0 )     /* read binary */
        return((WPTR) 0);              /* ERROR: Unable to open file  */
    if( fgets(buf,200,fp) == (char *) 0 )
        {
        vcfclose(fp);
        return((WPTR) 0);              /* ERROR: Reading file         */
        }
    if( sscanf(buf,SCANVALUE,
            &upper_r,
            &upper_c,
            &lower_r,
            &lower_c,
            &control,
            &depth,
            &width,
            &fill_ch,
            &border_at,
            &bg_at,
            &say_at,
            &get_at,
            &nget_at,
            &tit_at,
            &c_pos,
            &r_pos,
            &cur_r,
            &cur_c) < 18 )
        return((WPTR) 0);             /* ERROR: Reading file */
    isactive = control & ACTIVE;
    if(isactive)
        control ^= ACTIVE;
    control &= ~WOPEN;
    if( fgets(buf,200,fp) == (char *)0 )
        {
        vcfclose(fp);
        return((WPTR) 0);              /* ERROR: Reading file         */
        }
    wlen = strlen(buf);
    if( wlen && ( buf[wlen-1] < ' ' ) )
        buf[wlen-1] = '\0';
    wlen = width * depth * 2;
    wptr = wxxopen(upper_r,upper_c,lower_r,lower_c,buf,control,
                  depth,width,0,fill_ch);
    if( wptr == (WPTR) 0 )
        {
        vcfclose(fp);
        return((WPTR) 0);               /* ERROR: Opening window */
        }
    wptr->border_at = border_at;
    wptr->bg_at = bg_at;
    wptr->say_at = say_at; 
    wptr->get_at = get_at;
    wptr->nget_at = nget_at; 
    wptr->tit_at = tit_at;
    wptr->c_pos = c_pos;
    wptr->r_pos = r_pos;
    wptr->cur_r = cur_r;
    wptr->cur_c = cur_c;
    if( fread(wptr->location,sizeof(TEXT),wlen,fp) != wlen )
        {
        vcfclose(fp);
        return((WPTR) 0);              /* ERROR: Writing file */
        }
    if( vcfclose(fp) )
        return((WPTR) 0);              /* ERROR: closing file */
    if( isactive )
        wshow(wptr);
    return(wptr);                /* SUCCESS!            */
    }
 
