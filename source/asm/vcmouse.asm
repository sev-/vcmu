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
;   Name            vcmouse.asm - update mouse message buffer
;                                   
;   Descriptions    Puts an updated message into the mouse buffer
;                   every time a mouse interrupt is initiated.
;                   Deletes any duplicate messages that are generated.
;                   Formats message as follows: (ROW,COLUNM,STATUS).
;                   Must be assembled using switch /d? where ? is L
;                   for LARGE MEMORY MODEL, M for MEDIUM MEMORY MODEL, 
;                   or S for SMALL MEMORY MODEL.
;
;
;   Return Values   VOID
;
;
    FLAG = 0                            ; if NOT! LARGE or HUGE MODEL

IFDEF L
    FLAG = 1                            ; if LARGE MODEL
ENDIF

IFDEF H
    FLAG = 1                            ; if HUGE MODEL
ENDIF


IF FLAG                                 ; if LARGE or HUGE MODEL
VCMOUSE_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
VCMOUSE_TEXT    ENDS

_DATA    SEGMENT  WORD PUBLIC 'DATA'
_DATA    ENDS

_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS

DGROUP	GROUP	_BSS,	_DATA

	ASSUME  CS: VCMOUSE_TEXT, DS: DGROUP, SS: DGROUP

    LPROG    EQU    1
    LDATA    EQU    1
ENDIF

IFDEF C                                 ; if COMPACT MODEL
_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
_TEXT    ENDS

_DATA    SEGMENT  WORD PUBLIC 'DATA'
_DATA    ENDS

_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS

DGROUP	GROUP	_BSS,	_DATA

	ASSUME  CS: _TEXT, DS: DGROUP, SS: DGROUP

    LPROG    EQU    0
    LDATA    EQU    1
ENDIF                                                                   

IFDEF M                                 ; if MEDIUM MODEL
VCMOUSE_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
VCMOUSE_TEXT    ENDS

_DATA    SEGMENT  WORD PUBLIC 'DATA'
_DATA    ENDS

_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS

DGROUP  GROUP   _BSS,   _DATA

    ASSUME  CS: VCMOUSE_TEXT, DS: DGROUP, SS: DGROUP

    LPROG    EQU    1
    LDATA    EQU    0
ENDIF                                                                   

IFDEF S                                 ; if SMALL MODEL
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
IF LDATA
    extrn   _vcmoushead:dword           ; define external variables
    extrn   _vcmoustail:dword           ;       "           "
    extrn   _vcmoustop:dword            ;       "           "
    extrn   _vcmousend:dword            ;       "           "
ENDIF

_DATA    SEGMENT  WORD PUBLIC 'DATA'
axdummy     dw  0                       ; setup varialbles
bxdummy     dw  0                       ;       "           "
cxdummy     dw  0                       ;       "           "
dxdummy     dw  0                       ;       "           "
IFE LDATA
    extrn   _vcmoushead:word            ; define external variables
    extrn   _vcmoustail:word            ;       "           "
    extrn   _vcmoustop:word             ;       "           "
    extrn   _vcmousend:word             ;       "           "
ENDIF
_DATA    ENDS

PUBLIC    _vcmouse                      ; vctioput is public

IF    LPROG                             ; if LARGE or MEDIUM MODEL
VCMOUSE_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
_vcmouse    PROC    FAR                 ; setup for FAR return

ELSE                                    ; else SMALL MODEL
_TEXT    SEGMENT  BYTE PUBLIC 'CODE'
_vcmouse    PROC    FAR                 ; setup for NEAR return
ENDIF
            pushf                       ; save flags on stack
            cli                         ; disable maskable interrupts
            push    bp                  ; save registers that
            push    es                  ;   are used
            push    ds                  ;   "           "
            push    si                  ;   "           "
            push    di                  ;   "           "
            push    bx                  ;   "           "
            push    ax                  ;   "           "

            mov     di,DGROUP           ; set up data segment 
            mov     ds,di               ;   to acces variables
            and     ax,7fh              ; mask off unwanted bits
            and     bx,07h              ;       "       "
            cmp     ax,axdummy          ; is AX a duplicate
            jnz     doit                ;   if no, continue
            cmp     bx,bxdummy          ; is BX a duplicate
            jnz     doit                ;   if no, continue
            cmp     cx,cxdummy          ; is CX a duplicate
            jnz     doit                ;   if no, continue
            cmp     dx,dxdummy          ; is DX a duplicate
            jnz     doit                ;   if no, continue
            pop     ax                  ; clean up stack for
            pop     ax                  ;   return
            jmp     good                ; exit, no change

doit:       mov     axdummy,ax          ; save AX for duplicate check
            mov     bxdummy,bx          ; save BX for duplicate check
            mov     cxdummy,cx          ; save CX for duplicate check
            mov     dxdummy,dx          ; save DX for duplicate check

            mov     ax,seg _vcmoustail  ; get segment of tail
            mov     es,ax               ;   and load into ES
            mov     di,offset _vcmoustail; get offset of tail
            mov     si,es:[di]          ; SI points to location tail
IF LDATA                                ; if LARGE MODEL
            mov     bx,es:[di]+ 2       ; get segment of tail
            mov     ds,bx               ; tail segment is now default
ELSE                                    ; else if SMALL OR MEDIUM 
            mov     ax,DGROUP           ; get default segment
            mov     ds,ax               ; _DATA is now default
ENDIF
            mov     ax,dx               ; put DX in AX for divide
            mov     bl,8                ; setup divisor
            div     bl                  ; divide AX for correct row
            mov     [si],al             ; put row into buffer
            inc     si                  ; point to next location
            mov     ax,cx               ; put CX in AX for divide
            div     bl                  ; divide AX for correct col
            mov     [si],al             ; put column into buffer
            inc     si                  ; point to next location

            mov     bx,0h               ; clear BX for storage
            pop     ax                  ; get MASK status 
            mov     ah,0h               ; clear upper byte
            clc                         ; clear the carry flag
            shl     al,1                ; shift AL once to left
            rcl     al,1                ; rotate MSB into carry
            jnc     mb2                 ; if MBP = 0, check MBR
            or      bl,20h              ;   else set MB bit
mb2:        clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     rb_trig             ; if MBR = 0, check RBP
            or      bl,20h              ;   else set MB bit
rb_trig:    clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     rb2                 ; if RBP = 0, check RBR
            or      bl,10h              ;   else set RB bit
rb2:        clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     lb_trig             ; if RBR = 0, check LBP
            or      bl,10h              ;   else set RB bit
lb_trig:    clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     lb2                 ; if LBP = 0, check LBR
            or      bl,40h              ;   else set LB bit
lb2:        clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     p_trig              ; if LBR = 0, check PC 
            or      bl,40h              ;   else set LB bit
p_trig:     clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     buttstat            ; if PC = 0, check BS
            or      bl,80h              ;   else set PC bit
buttstat:   pop     ax                  ; get BUTTON status           
            and     ax,07h              ; mask off unwanted bits
            mov     cl,5                ; setup for shift
            shl     al,cl               ; shift AL left 5
            clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     rb_stat             ; if MB = 0, check RB
            or      bl,02h              ;   else set MB bit
rb_stat:    clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     lb_stat             ; if RB = 0, check LB
            or      bl,01h              ;   else set RB bit
lb_stat:    clc                         ; clear the carry flag
            rcl     al,1                ; rotate MSB into carry
            jnc     continue            ; if LB = 0, continue
            or      bl,04h              ;   else set LB bit
continue:   mov     [si],bl             ; put message into buffer

            inc     si                  ; point to next location
            mov     ax,seg _vcmousend   ; get segment of end and
            mov     ds,ax               ;   put in DS
            mov     bx,OFFSET _vcmousend; get offset of end
            cmp     si,ds:[bx]          ; compare tail with end
            jna     tail_ok             ; if tail < end, continue
            mov     ax,seg _vcmoustop   ;   else get segment of top
            mov     ds,ax               ;   and put in DS
            mov     bx,OFFSET _vcmoustop;   get offset of top
            mov     si,ds:[bx]          ;   put address of top in SI

tail_ok:    mov     es:[di],si          ; update tail address

            mov     dx,si               ; mov tail address to DX
            mov     ax,seg _vcmoushead  ; get segment of head
            mov     ds,ax               ;   and put in DS
            mov     si,offset _vcmoushead; get offset of head
            cmp     dx,ds:[si]          ; compare tail and head
            jne     good                ; if NOT equal, exit
            inc     dx                  ; point to next byte
            inc     dx                  ; point to next byte
            inc     dx                  ; point to next byte
            
            mov     ax,seg _vcmousend   ; get segment of end
            mov     es,ax               ;   and put in ES
            mov     bx,OFFSET _vcmousend; get offset of end
            cmp     dx,es:[bx]          ; compare head with end
            jna     head_ok             ; if head < end continue
            mov     ax,seg _vcmoustop   ;   else get segment of top
            mov     es,ax               ;   and put in ES
            mov     bx,OFFSET _vcmoustop;   get offset of top
            mov     dx,es:[bx]          ;   put address of top in DX

head_ok:    mov     ds:[si],dx          ; update head address
good:       pop     di                  ; restore registers that
            pop     si                  ;   were used
            pop     ds                  ;       "           "
            pop     es                  ;       "           "
            pop     bp                  ;       "           "
            popf                        ; retore flags (STI)
            ret                         ; return to parent routine
_vcmouse   endp

    IF    LPROG                         ; if LARGE or MEDIUM MODEL
VCMOUSE_TEXT    ENDS
    ELSE                                ; else SMALL MODEL
_TEXT    ENDS
    ENDIF
    end
