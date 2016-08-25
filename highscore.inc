

; code concerning the high score
; ----------------------------------

CheckHighScore:

	lda #17				; Set screen position hscore
	sta char_xpos

	jsr CheckPosition		; Check if score = 1st, 2nd or 3rd
	lda scorepos
	cmp #3
	bne ThirdPlace
	rts				; No highscore

; Third place
; Nothing to shift
; Goto set highscore + name

ThirdPlace:
	cmp #2
	bne SecondPlace
	jmp SetHiscore

; Second place
; Shift score + name 2nd to 3rd
; Goto set highscore + name

SecondPlace:
	cmp #1
	bne FirstPlace
	ldx #2				; Shift score 2nd to 3rd 
second_loop:
	lda hscore2,x
	sta hscore3,x
	dex
	bpl second_loop
	ldx #6				; shift names 2nd to 3rd 
second_loop2:
	lda hscore_name2,x
	sta hscore_name3,x
	dex
	bpl second_loop2
	jmp SetHiscore

; First place
; Shift score + name 2nd to 3rd
; Shift score + name 1st to 2nd
; Goto set highscore + name

FirstPlace:
	ldx #5				; Shift score 2nd to 3rd and 1st to 2nd
first_loop:
	lda hscore1,x
	sta hscore2,x
	dex
	bpl first_loop
	ldx #13				; Shift names 2nd to 3rd and 1st to 2nd
first_loop1:
	lda hscore_name1,x
	sta hscore_name2,x
	dex
	bpl first_loop1

; Set new high score + clear name

SetHiscore:
	ldx scorepos
	ldy scoreptr,x

	ldx #2				; Set new high score
set_loop1:
	lda score,x
	sta hscore1,y
	dey
	dex
	bpl set_loop1

	ldy scorepos
	lda nameptr,y
	sta hscorePointer

	ldy hscorePointer		; Clear highscore name
	ldx #6
	lda #32
name_clear_loop:
	sta hscore_name1,y
	iny
	dex
	bpl name_clear_loop

	jsr StartLevelSelectMode	; Display Highscore screen
	rts	

; ----------------------------------
; Check if score = 1st, 2nd or 3rd

CheckPosition:					
	ldy #3
	lda #<hscore3			; Check if score>=hscore3
	sta chk_pos+1
	lda #>hscore3
	sta chk_pos+2
	jsr Check_GTE
	bcc end_chk
	dey
	lda #<hscore2			; Check if score>=hscore2
	sta chk_pos+1
	lda #>hscore2
	sta chk_pos+2
	jsr Check_GTE
	bcc end_chk
	dey
	lda #<hscore1			; Check if score>=hscore1
	sta chk_pos+1
	lda #>hscore1
	sta chk_pos+2
	jsr Check_GTE
	bcc end_chk
	dey
end_chk:
	sty scorepos
	rts

; ----------------------------------
; Check if score >= hiscore

Check_GTE:
	ldx #2
chk_loop:
	lda score,x
chk_pos:
	cmp hscore1,x
	bmi chk_nok
	bne chk_ok
	dex
	bpl chk_loop
chk_ok:
	sec				; score >= hiscore
	rts
chk_nok:
	clc				; score < hiscore
	rts

; ----------------------------------
; Print highscore + names on screen

PrintHighScores:

	clc 				; clear carry bit so we set cursor
	ldx #14+2 			; row 14
	ldy #14-5 			; column 14
	jsr plot 			; move cursor so we can use chrout

	lda #<hscore1			; Print highscore1
	sta ploop1+1
	lda #>hscore1
	sta ploop1+2
	jsr PrintHighScore

	clc 				; clear carry bit so we set cursor
	ldx #15+2 			; row 15
	ldy #14-5 			; column 14
	jsr plot 			; move cursor so we can use chrout

	lda #<hscore2			; Print highscore2
	sta ploop1+1
	lda #>hscore2
	sta ploop1+2
	jsr PrintHighScore

	clc 				; clear carry bit so we set cursor
	ldx #16+2 			; row 16
	ldy #14-5 			; column 14
	jsr plot 			; move cursor so we can use chrout

	lda #<hscore3			; Print higscore3
	sta ploop1+1
	lda #>hscore3
	sta ploop1+2
	jsr PrintHighScore

	lda #17
	sta  XPOS
	ldx #0
PrintNameLoop:
	lda #16
	sta YPOS
	lda hscore_name1,x		; Print names after highscore1
	jsr chrout
	inc YPOS
	lda hscore_name2,x		; Print names after highscore2
	jsr chrout
	inc YPOS
	lda hscore_name3,x		; Print names after highscore3
	jsr chrout
	inc XPOS
	inx
	cpx #7
	bne PrintNameLoop
	rts

; ----------------------------------
; Blink letter + update in highscore name if changed
; LEFT 		, <   = 1 Character left
; RIGHT		. >   = 1 character right
; TURNCOUNTER	A     = previous letter
; TURNCLOCK 	S     = next letter
; DOWN 		SPACE = End

UpdateHighScoremode:
	jsr GetInput 			; check for input
	ldx inputResult
	cpx #NOINPUT
	bne key_input
	jmp doCharFlash

	; there is input

key_input:
	cpx #DOWN			; Hit space?
	bne chrskip2
	jmp EndHighscoreMode		; Yes, end of update

chrskip2:
	cpx #TURNCOUNTER 		; hit return?
	bne chrskip3
;	ldx charPointer
;	lda charSelection,x
;	sta previousChar
	inc charPointer
	lda charPointer
	cmp #36
	bne no_ptr_reset
	lda #0
	sta charPointer
no_ptr_reset:
	jmp chrInputDone
chrskip3:
	cpx #TURNCLOCK 			; hit return?
	bne chrskip4
;	ldx charPointer
;	lda charSelection,x
;	sta previousChar
	dec charPointer
	bpl no_ptr_reset2
	lda #35
	sta charPointer
no_ptr_reset2:
	jmp chrInputDone
chrskip4:
	cpx #LEFT
	bne chrskip5

	lda char_xpos
	cmp #17
	beq doCharFlash
	jsr chrInputDone
	dec hscorePointer
	dec char_xpos
	lda #0
	sta charPointer
	rts

chrskip5:
	cpx #RIGHT
	bne doCharFlash  		; no further relevant input, goto flashing
	lda char_xpos
	cmp #23
	beq doCharFlash
	jsr chrInputDone
	inc hscorePointer
	inc char_xpos
	lda #0
	sta charPointer
	rts

chrInputDone:
	; level select has changed
	; make sure previous level is showing

	lda scorepos			; Set char position
	clc
	adc #16
	tax
	ldy char_xpos
	clc
	jsr plot

	ldx charPointer
	lda charSelection,x 		; get the level value
	ldx hscorePointer
	sta hscore_name1,x
	jsr chrout

	; make sure to show change asap

	lda #$01
	sta charDisplayFlag
	lda #FLASH_DELAY
	sta charFlashDelay

doCharFlash:
	dec charFlashDelay
	beq chrskip6 			; do flashing
	rts 				; nothing to do anymore
chrskip6:
	; we are going to flash the character

	lda #FLASH_DELAY
	sta charFlashDelay 		; reset the delay counter

	; set cursor to correct location

	lda scorepos			; Set char position
	clc
	adc #16
	tax
	ldy char_xpos
	clc
	jsr plot

	; flip the display flag

	lda charDisplayFlag
	eor #%00000001
	sta charDisplayFlag

	beq chrspace 			; flag clear? then print space
	ldx charPointer
	lda charSelection,x 		; get the level value
	ldx hscorePointer
	sta hscore_name1,x
	jmp chrout 			; print and exit
chrspace:
	lda #38
	jmp chrout 			; and exit
	
; ----------------------------------

EndHighscoreMode:
	jmp otherStep2

char_xpos:
	.byte 0
;currentChar:
;	.byte 0
;previousChar:
;	.byte 0
charSelection:
	.byte 32
	.byte 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
	.byte 16,17,18,19,20,21,22,23,24,25,26
	.byte 48,49,50,51,52,53,54,55,56,57
charPointer:
	.byte 0
hscorePointer:
	.byte 0
charFlashDelay:
	.byte FLASH_DELAY		; counter
charDisplayFlag:
	.byte 0				; render number or space
charLevel:
	.byte 0

; ----------------------------------

scorepos:	.byte 0

scoreptr:	.byte 2,5,8
nameptr:	.byte 0,7,14

hscore1:	.byte $00,$00,$02
hscore2:	.byte $00,$00,$01
hscore3:	.byte $00,$50,$00

hscore_name1:	.byte 23,9,5,2,15,32,32
hscore_name2:	.byte 11,5,5,19,32,32,32
hscore_name3:	.byte 20,5,20,18,9,19,32

hs_pos1		= selectScreenData+14*21+4
hs_pos2		= selectScreenData+15*21+4
hs_pos3		= selectScreenData+16*21+4

hs_name1	= hs_pos1+8
hs_name2	= hs_pos2+8
hs_name3	= hs_pos3+8


