
;
;----------------------------------
;Tetris for 6502. (c) WdW 2015
;----------------------------------
;

; game modes

MODE_ATTRACT 		= 1
MODE_SELECTLEVEL	= 2
MODE_PLAY 		= 3
MODE_GAMEOVER 		= 4
MODE_ENTERNAME 		= 5

DEBUG 			= 0


; ------------------------------------------------

	; initial setup

	lda #$f0			; MODE4
	sta $b000

	lda #$40
	sta $b80b

        jsr SetupRandom 		; set the rnd seed
        jsr ClearScreen 		; clear the screen and set colors
	jsr joyinit
	jsr init

	; initial setup done
	;select mode and call mode entry routine.

	lda #MODE_ATTRACT
	sta gameMode
	jsr StartAttractMode

; --------------------------------------------------

loopstart:

wait:
	lda $b809
	cmp #$ff
	bne wait
	lda #<10000			; Wait 1/50 sec
	sta $b808
	lda #>10000
	sta $b809

	; determine game mode and update accordingly

	lda gameMode
	cmp #MODE_ATTRACT
	bne @skip1
	jsr UpdateAttractMode
	jmp loopstart
@skip1:
	cmp #MODE_SELECTLEVEL
	bne @skip2
	jsr UpdateLevelSelectMode
	jmp loopend
@skip2:
	cmp #MODE_PLAY
	bne @skip3
	jsr UpdatePlayMode
	jmp loopend
@skip3:
	cmp #MODE_GAMEOVER
	bne @skip4
	jsr UpdateGameOverMode
	jmp loopend
@skip4:
	cmp #MODE_ENTERNAME
	bne loopend
	jsr UpdateHighScoremode
loopend:

	jmp loopstart

; ------------------------------------------

gameMode:
	.byte 0
pauseFlag:
	.byte 0 			; game is pause when this is set to 1

