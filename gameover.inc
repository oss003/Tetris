
; code concerning the game over mode

STEP_FILLWELL = 0
STEP_CLEARWELL = 1
STEP_TEXT = 2

	; the character to fill the well with
drawCharacter:
	.byte 0

	; the mode step variable
currentStep:
	.byte 0

	; the amount of lines left to fill
linesLeft:
	.byte 0


; ------------------------------------------------

StartGameOverMode:

	; prepare for the first step

	lda #STEP_FILLWELL
	sta currentStep

	; we will render this block
	lda #88
	sta drawCharacter

	; and we need to do 20 lines
	lda #20
	sta linesLeft

	; point to the bottom line
	ldx #12
	stx blk_x
	ldy #19
	sty blk_y
	jsr SetScreenPointer

	lda #SND_MUSIC_GAMEOVER
	jsr playsound

	rts

; ---------------------------------------------------

UpdateGameOverMode:

	lda currentStep 	; which step to ...
	cmp #STEP_FILLWELL 	; perform?
	bne otherStep1

	jsr FillLine
	dec blk_y
	lda #12
	sta blk_x
	dec linesLeft		; all lines done?
	beq @skip1 		; yes. prepare next step
	rts 			; no. continue on next update
@skip1:
	; done filling
	; go to next step

	lda #STEP_CLEARWELL
	sta currentStep
	lda #$20
	sta drawCharacter
	lda #19
	sta linesLeft

	; point to the bottom line
	ldx #12+2
	ldy #19-3
	jsr SetScreenPointer
	rts

otherStep1:
	cmp #STEP_CLEARWELL
	bne otherStep2

	jsr FillLine
	dec linesLeft		; all lines done?
	beq @skip2 		; yes. prepare next step
	rts 			; no. continue on next update
@skip2:
	; done clearing
	; print text and go to next mode

	lda #STEP_TEXT 		; go to next step
	sta currentStep
	jsr PrintGameOver
otherStep2:

	; waiting for a key or fire button

	ldx #4
	jsr readinput
	cmp #DOWN 		; enter pressed?
	bne no_key_press
	lda #MODE_ATTRACT
	sta gameMode
wait_release:
	ldx #4
	jsr readinput
	cmp #DOWN 		; wait until released
	beq wait_release
	jmp StartAttractMode

no_key_press:
	rts


; ---------------------------------------------------

EndGameOverMode:



; ---------------------------------------------------


; files a line with the drawcharacter

FillLine:
	lda drawCharacter	 	; get char
	ldy #$00
@loop1:
	sta (screenPointer),y 	; store on screen
	jsr displayblock
	inc blk_x
	iny
	cpy #10 		; line done?
	bne @loop1
	lda #12+2
	sta blk_x
	jsr UpOneRow 	; prepare for next line
	rts

; -----------------------------------------------

PrintGameOver:

	; set start of data

	lda #<gameoverText
	sta dataSourceLo
	lda #>gameoverText
	sta dataSourceHi
	lda #10
	sta dataWidth
	lda #20
	sta dataHeight
	lda #>(L0400+12)
	sta dataDestinationHi
	lda #<(L0400+12)
	sta dataDestinationLo
	jsr WriteScreenData

	jmp CheckHighScore
