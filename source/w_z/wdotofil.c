/**
*
*   Vitamin C Multi-User version 1.6
*   Copyright (c) 1985-1990
*   Creative Programming Consultants, Inc.
*   P.O. Box 112097
*   Carrollton, Texas  75006
*   (214) 416-6447
*   ALL RIGHTS RESERVED
*   Last Modification: .4 on 8/31/90 at 22:21:17
*
*   Name            wdotofil.c  --  write window to file
*
*   Description     This function writes window structure and 
*                   contents to a disk file.
*
*   Return Value    Returns -1 if error
*                    
*
**/

#include <vcstdio.h>

COUNT wdotofil(wptr,fnam)
WPTR wptr;          /* Window to save to file                       */
TEXT *fnam;         /* File name                                    */
    {
    FILE *vcfopen(),*fp;
    COUNT wlen;
    COUNT vcfclose();
    if((wptr != (WPTR)0) && (wptr->wctrl & WOPEN) )
        {
        if( (fp=vcfopen(fnam,VCF_WB)) == (FILE *)0 )
            return(-1);              /* ERROR: Unable to open file  */
        fprintf(fp,"%d %d %d %d %d %d %d %d %d %d ",
                wptr->upper_r,
                wptr->upper_c,
                wptr->lower_r,
                wptr->lower_c,
                wptr->wctrl,
                wptr->depth,
                wptr->width,
                wptr->fill_ch,
                wptr->border_at,
                wptr->bg_at);
        fprintf(fp,"%d %d %d %d %d %d %d %d\n%s\n",
                wptr->say_at,
                wptr->get_at,
                wptr->nget_at,
                wptr->tit_at,
                wptr->c_pos,
                wptr->r_pos,
                wptr->cur_r,
                wptr->cur_c,
                wptr->title);
        wlen = wptr->width * wptr->depth * 2;
        if( fwrite(wptr->location,sizeof(char),wlen,fp) != wlen )
            {
            vcfclose(fp);
            return(-2);              /* ERROR: Writing file */
            }
        if( vcfclose(fp) )
            return(-3);              /* ERROR: closing file */
        }
    else
        return(-4);                  /* ERROR: Bad wptr     */
    return(0);                       /* SUCCESS!            */
    }






