

; attrack mode steps

STEP_TITLE 	= 0
STEP_CREDITS 	= 1
STEP_CONTROLS 	= 2
STEP_HIGHSCORE	= 3
ATTRACT_DELAY 	= 50 * 5

attractStep:
	.byte 0

attractDelay:
	.byte 0

; -----------------------------------------

StartAttractMode:
	lda #ATTRACT_DELAY
	sta attractDelay
	lda #STEP_TITLE
	sta attractStep

	; set the screen size
	; this is the same for all steps
	; so doing it once is enough

	; set data dimensions
	lda #21
	sta dataWidth
	lda #20
	sta dataHeight

	; set start of area to print to

	lda #>(L0400+10)
	sta dataDestinationHi
	lda #<(L0400+10)
	sta dataDestinationLo

	; print the first screen

	lda #<titleScreenData
	sta dataSourceLo
	lda #>titleScreenData
	sta dataSourceHi
	jsr WriteScreenData

	lda #SND_MUSIC_TITLE
	jmp playsound


; -----------------------------------------

UpdateAttractMode:
	jsr $fe6b
	jsr $fe6b
	dec attractDelay
	beq triggered 		; swap screen when triggered

	; check for key or joy button press

	ldx #4
	jsr readinput
	cmp #DOWN 		; enter pressed?
	beq @skip1 		; yes
	rts
@skip1:
	jsr wait_press
	jmp EndAttractMode	; start the game
triggered:
	lda #ATTRACT_DELAY 	; reset the delay
	sta attractDelay

	inc attractStep 	; go to next screen
	lda attractStep
	cmp #4 			; have we done 4 screens?
	bne @skip2		; no. continue cycle
	lda #STEP_TITLE    	; yes. reset cycle
	sta attractStep
@skip2:
	; set data dimensions

	lda #21
	sta dataWidth
	lda #20
	sta dataHeight

	; reset the screen pointer

	lda #>(L0400+10)
	sta dataDestinationHi
	lda #<(L0400+10)
	sta dataDestinationLo

	; set start of data
	; dependent on attract step

	lda attractStep
	cmp #STEP_TITLE
	bne nextstep1
	lda #<titleScreenData
	sta dataSourceLo
	lda #>titleScreenData
	sta dataSourceHi
	jmp WriteScreenData
nextstep1:
	cmp #STEP_CREDITS
	bne nextstep2
	lda #<creditsScreenData
	sta dataSourceLo
	lda #>creditsScreenData
	sta dataSourceHi
	jmp WriteScreenData

nextstep2:
	cmp #STEP_CONTROLS
	bne nextstep3
	lda #<keysScreenData
	sta dataSourceLo
	lda #>keysScreenData
	sta dataSourceHi
	jmp WriteScreenData
nextstep3:
	cmp #STEP_HIGHSCORE
	bne nextstep4
	lda #<selectScreenData
	sta dataSourceLo
	lda #>selectScreenData
	sta dataSourceHi
	jsr WriteScreenData
	jmp PrintHighScores
nextstep4:
	rts
; -----------------------------------------

EndAttractMode:
	lda #MODE_SELECTLEVEL
	sta gameMode
	jsr StartLevelSelectMode
	rts
