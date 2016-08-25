;---------------------------------------------
; Read key in matrix
;
; Select row and read column:
;
; X = key to be checked
;
; columnbit = 0 - key pressed,
;             1 - key not pressed
;---------------------------------------------

inputsource	= $23f

readinput:
	bit inputsource		; Check controls
	bvs inp_joykey		; Control = Joykey
	bmi inp_joymmc		; Control = JoyMMC

inp_key:
	lda key_row,x
	ora #$f0
	sta $b000		; Select row

	lda $b001		; Read column
	and key_column,x
	bne not_pressed

	lda #$80
	sta key_pressed_flag

	lda key_return,x
	rts

not_pressed:
	lda #$ff
;	bit key_pressed_flag
;	bpl end_key
;	lda key_return,x
end_key:
	rts

key_pressed_flag:	.byte 0

;--------------------------------------------------------
; Control = Joykey
;--------------------------------------------------------

inp_joykey:
	cpx #5			; P,Q key
	bcs inp_key

	inx
	inx
	inx
	inx
	inx
	inx
	inx
	jmp inp_key

;--------------------------------------------------------
; Control = JoyMMC
;--------------------------------------------------------

inp_joymmc:
	cpx #5			; P,Q key
	bcs inp_key

	jsr joyget
	sta joy_scan
scan_l:
	cpx #0
	bne scan_r
	lda joy_scan
	and #$02
	beq scan_r
	lda #47
	rts
scan_r:
	cpx #1
	bne scan_u
	lda joy_scan
	and #$01
	beq scan_u
	lda #44
	rts
scan_u:
	cpx #2
	bne scan_d
	lda joy_scan
	and #$08
	beq scan_d
	lda #13
	rts
scan_d:
	cpx #3
	bne scan_f
	lda joy_scan
	and #$04
	beq scan_f
	lda #10
	rts
scan_f:
	cpx #4
	bne scan_no
	lda joy_scan
	and #$10
	beq scan_no
	lda #1
	rts
scan_no:
	lda #0
	rts

;--------------------------------------------------------
; Keyboard/joystick
;
;Key    move    mat joy ret
;----------------------------
;  <  = left	 0   L   47
;  >  = right	 1   R   44
;  S  = turn CCW 2   U   13
;  A  = turn CW	 3   D   10
; SPC = dump	 4   F    1
;  P  = pause	 5       41
; ESC = reset	 6        4
;--------------------------------------------------------

joy_scan:	.byte 0

;                      L   R   U   D   F   P   Q   JL  JR  JU  JD  JF
key_row:	.byte $01,$09,$08,$06,$09,$01,$00,$00,$00,$00,$00,$00
key_column:	.byte $04,$08,$20,$08,$01,$10,$20,$02,$08,$10,$04,$01
key_return:	.byte  47, 44, 13, 10,  1, 41,  4, 47, 44, 13, 10,  1

