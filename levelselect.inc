
FLASH_DELAY 	= 18

; ----------------------------------

StartLevelSelectMode:

	lda #$00
	sta currentLevel
	sta previousLevel
	sta levelDisplayFlag
	sta gameLevel
	sta gameLevel+1

	lda #1
	sta levelFlashDelay 		; and delay counter

	; print the screen

	lda #<selectScreenData
	sta dataSourceLo
	lda #>selectScreenData
	sta dataSourceHi
	lda #21
	sta dataWidth
	lda #21
	sta dataHeight
	lda #>(L0400+10)
	sta dataDestinationHi
	lda #<(L0400+10)
	sta dataDestinationLo
	jsr WriteScreenData
	jsr PrintHighScores

	lda #SND_MOVE_BLOCK
	jmp playsound

; --------------------------------------------------

UpdateLevelSelectMode:
	jsr GetInput 			; check for input
	ldx inputResult
	cpx #NOINPUT
	beq doLevelFlash

	; there is input

;	cpx #TURNCLOCK 			; hit fire?
;	bne @skip1
;	jmp EndLevelSelectMode
;@skip1:
	cpx #DOWN 			; hit return?
	bne @skip2

	lda #SND_OPTION
	jsr playsound

	jsr wait_press

	jmp EndLevelSelectMode
@skip2:
	cpx #LEFT
	bne @skip3
	lda currentLevel
	beq doLevelFlash 		; we cant go lower, goto flashing
	sta previousLevel 		; store level
	dec currentLevel 		; and change level
	jmp inputDone
@skip3:
	cpx #RIGHT
	bne doLevelFlash  		; no further relevant input, goto flashing
	lda currentLevel
	cmp #9
	beq doLevelFlash 		; we cannot go higher, goto flashing
	sta previousLevel
	inc currentLevel
inputDone:
	; level select has changed
	; make sure previous level is showing

	ldx previousLevel
	lda levelY,x
	pha
	lda levelX,x
	tay
	pla
	tax
	clc
	jsr plot

	lda previousLevel
	adc #$30  			; add #$30 to it to get a screencode
	jsr chrout

	; make sure to show change asap

	lda #$01
	sta levelDisplayFlag
	sta levelFlashDelay

doLevelFlash:
	dec levelFlashDelay
	beq @skip4 			; do flashing
	rts 				; nothing to do anymore
@skip4:
	; we are going to flash the level indicator

	lda #FLASH_DELAY
	sta levelFlashDelay 		; reset the delay counter

	; set cursor to correct location

	ldx currentLevel
	lda levelY,x
	pha
	lda levelX,x
	tay
	pla
	tax
	clc
	jsr plot

	; flip the display flag

	lda levelDisplayFlag
	eor #%00000001
	sta levelDisplayFlag

	beq space 			; flag clear? then print space
	lda currentLevel 		; get the level value
	adc #$30 			; add #$30 to it to get a screencode
	jmp chrout 			; print and exit
space:
	lda #$20
	jmp chrout 			; and exit

; ----------------------------------

EndLevelSelectMode:
	lda #MODE_PLAY
	sta gameMode
	jsr StartPlayMode
	rts

; ----------------------------------

; x/y positions of level numbers on screen

;              0  1  2  3  4  5  6  7  8  9
levelX:
	.byte 16-5,18-5,20-5,22-5,24-5,16-5,18-5,20-5,22-5,24-5
levelY:
	.byte 07+2,07+2,07+2,07+2,07+2,09+2,09+2,09+2,09+2,09+2

levelFlashDelay:
	.byte 0 			; counter
levelDisplayFlag:
	.byte 0				; render number or space
previousLevel:
	.byte 0
