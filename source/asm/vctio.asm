;
;
;   Vitamin C Multi-User version 1.6
;   Copyright (c) 1985-1990
;   Creative Programming Consultants, Inc.
;   P.O. Box 112097
;   Carrollton, Texas  75006
;   (214) 416-6447
;   ALL RIGHTS RESERVED
;   Last Modification: .%L% on %G% at %U%
;
;   Name            vctio - read/write from/to screen
;                                   
;   Descriptions    Contains assembly functions VCTIOPUT and
;                   VCTIOGET.  Both are called with paramaters 
;                   (row,col,buffer,len) passed to them.  VCTIOPUT
;                   writes "len" number of items located in "buffer"
;                   to "row" and "col" of screen.  VCTIOGET reads
;                   "len" number of items located at "row" and "col" 
;                   of screen into "buffer".  These routines check
;                   CRT status ports to prevent "snow" when using a
;                   color monitor.
;                   Must be compiled with /ml and /d? where ? L for
;                   LARGE MEMORY MODEL, M for MEDIUM MEMORY MODEL, or
;                   S for SMALL MEMORY MODEL.
;
;   Return Values   VOID
;
;

IFDEF L
VCTIO_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
VCTIO_TEXT    ENDS

_DATA    SEGMENT  WORD PUBLIC 'DATA'
_DATA    ENDS

_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS

DGROUP	GROUP	_BSS,	_DATA

	ASSUME  CS: VCTIO_TEXT, DS: DGROUP, SS: DGROUP

    LPROG    EQU    1
    LDATA    EQU    1
ENDIF

IFDEF M
VCTIO_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
VCTIO_TEXT    ENDS

_DATA    SEGMENT  WORD PUBLIC 'DATA'
_DATA    ENDS

_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS

DGROUP	GROUP	_BSS,	_DATA

	ASSUME  CS: VCTIO_TEXT, DS: DGROUP, SS: DGROUP

    LPROG    EQU    1
    LDATA    EQU    0
ENDIF                                                                   

IFDEF S
_TEXT	SEGMENT  BYTE PUBLIC 'CODE'
_TEXT	ENDS

_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS

_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS

DGROUP	GROUP	_BSS,	_DATA

	ASSUME  CS: _TEXT, DS: DGROUP, SS: DGROUP

    LPROG	EQU	0
    LDATA	EQU	0
ENDIF

IF LPROG                                ; if large or medium model
        x    EQU    14                  ; adjustment for larger address
ELSE                                    ; else small model
        x    EQU    12                  ; adjustment for small address
ENDIF

_DATA    SEGMENT  WORD PUBLIC 'DATA'
    extrn    _vcvram:word               ; VDR address
    extrn    _vcsprt:word               ; status port address
_DATA    ENDS

;=================================================================
; Routine to write to video display ram...
;=================================================================

PUBLIC    _vctioput                     ; vctioput is public

IF    LPROG                             ; if large or medium model
VCTIO_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
_vctioput    PROC    FAR

ELSE                                    ; else small model
_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
_vctioput    PROC    NEAR
ENDIF


get_parms:  push    bp                  ; save registers that
            push    es                  ;   are used
            push    ds                  ;   "           "
            push    si                  ;   "           "
            push    di                  ;   "           "
            mov     dx,_vcvram          ; get address of VDR
            mov     es,dx               ; put VDR address in ES
            mov     bp,sp               ; current stack position
            mov     ax,[bp+x]           ; get row from stack
            mov     cl,80               ; set up and adjust
            mul     cl                  ;   for 80 charactes/row
            mov     dx,[bp+x+2]         ; get col from stack
            add     ax,dx               ; add col to row
            shl     ax,1                ; adjust for attribute byte
            mov     di,ax               ; put offset into DI
            mov     si,[bp+x+4]         ; get offset of buffer pointer
            mov     dx,_vcsprt          ; get status port address

IF LDATA                                ; if large model
    ; THIS IS FOR THE LARGE MODEL
            mov     cx,[bp+x+6]         ; get segment of buffer pointer
            mov     ds,cx               ; put segment into DS
            mov     cx,[bp+x+8]         ; get # of words to move
ELSE                                    ; else small or medium model
    ; THIS IS FOR SMALL MODEL AND MEDIUM MODELS
            mov     cx,[bp+x+6]         ; get # of words to move 
ENDIF
                                                
pnxtchr:    cmp     cx,0                ; check for characters
            jbe     pdone               ;   if none, end
            mov     bx,[si]             ; get char & attrib from buffer
pwait_lo1:  in      al,dx               ; input from status port
            test    al,1                ; check if CRT is in retrace
            jnz     pwait_lo1           ; if yes, loop until CRT exits
                                        ;   retrace
pwait_hi1:  in      al,dx               ; input from status port
            test    al,1                ; check if CRT is in retrace
            jz      pwait_hi1           ; if no, loop until CRT enters
                                        ;   retrace
pputit:     mov     es:[di],bx          ; write to VDR safely
            inc     si                  ; adjust SI for next character
            inc     si                  ;   and attribute
            inc     di                  ; adjust DI for next screen
            inc     di                  ;   location
            loop    pnxtchr             ; repeat for next character

pdone:      pop     di                  ; restore registers that
            pop     si                  ;   were used
            pop     ds                  ;       "           "
            pop     es                  ;       "           "
            pop     bp                  ;       "           "
            ret                         ; return to parent routine
_vctioput   endp


;=================================================================
; Routine to read form video display ram...
;=================================================================

PUBLIC    _vctioget                     ; vctioget is public

IF    LPROG                             ; if large of medium model
_vctioget    PROC    FAR
    ELSE                                ; else small model
_vctioget    PROC    NEAR
ENDIF

            push    bp                  ; save registers that
            push    es                  ;   are used
            push    ds                  ;   "           "
            push    si                  ;   "           "
            push    di                  ;   "           "

            mov     dx,_vcvram          ; get address of VDR
            mov     es,dx               ; put VDR address in ES
            mov     bp,sp               ; current stack position
            mov     ax,[bp+x]           ; get row from stack
            mov     dx,[bp+x+2]         ; get col from stack
            mov     cl,80               ; set up and adjust
            mul     cl                  ;   for 80 charactes/row
            add     ax,dx               ; add col to row
            shl     ax,1                ; adjust for attribute byte
            mov     si,ax               ; put offset into SI
            mov     di,[bp+x+4]         ; get offset of buffer pointer
            mov     dx,_vcsprt          ; get status port address

IF LDATA                                ; if large model
    ; THIS IS FOR THE LARGE MODEL
            mov     cx,[bp+x+6]         ; get segment of buffer pointer
            mov     ds,cx               ; put segment into DS
            mov     cx,[bp+x+8]         ; get # of words to move
ELSE                                    ; else small or medium model
    ; THIS IS FOR SMALL MODEL AND MEDIUM MODELS
            mov     cx,[bp+x+6]         ; get # of words to move 
ENDIF

gnxtchr:    cmp     cx,0                ; check for characters
            jbe     gdone               ;   if none, end
gwait_lo1:  in      al,dx               ; input from status port
            test    al,1                ; check if CRT is in retrace
            jnz     gwait_lo1           ; if yes, loop until CRT exits
                                        ;   retrace
gwait_hi1:  in      al,dx               ; input from status port
            test    al,1                ; check if CRT is in retrace
            jz      gwait_hi1           ; if no, loop until CRT enters
                                        ;   retrace
gputit:     mov     bx,es:[si]          ; read from VDR safely
            mov     [di],bx             ; move data to buffer
            inc     si                  ; adjust SI for next character
            inc     si                  ;   and attribute
            inc     di                  ; adjust DI for next buffer
            inc     di                  ;   location
            loop    gnxtchr             ; repeat for next character

gdone:      pop     di                  ; restore registers that
            pop     si                  ;   were used
            pop     ds                  ;       "           "
            pop     es                  ;       "           "
            pop     bp                  ;       "           "
            ret                         ; return to parent routine
_vctioget   endp                        

    IF    LPROG                         ; if large or meduim model
VCTIO_TEXT    ENDS
    ELSE                                ; else small model
_TEXT    ENDS
    ENDIF
    end
