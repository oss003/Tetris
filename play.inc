
; play mode

linesPerLevel 		= 10		; level advance threshold
delayChange 		= 4 		; game goes this much faster each level
DEFAULT_DROP_DELAY 	= 70

; --------------------------------------------

; starts a new game
; level and drop delay have already been set!

StartPlayMode:

	; reset drop delay

	lda #DEFAULT_DROP_DELAY
	sta fallDelay
	sta fallDelayTimer

	; add the levels
	; currentLevel has been set by levelselect.asm

	ldx currentLevel
	beq @skip1
@loop1:
	jsr AddLevel
	dex
	bne @loop1
@skip1:
	jsr PrintPlayScreen
	jsr PrintLevel

	; set up player stats

	jsr ResetScore 			; reset player score...
	jsr ResetLinesMade		; and total lines made

	; reset play stats

	lda #$00 			; reset the lines counter...
	sta levelLinesCounter 		; which is used to go up levels.
	sta linesMade 			; and no lines made

	; set the next block value
	; NewBlock will use this value for a new block
	; and set the next block value again for the next call

	jsr GetRandom
	sta nextBlockID 		; this will be printed as the next block
					; to fall
	jsr NewBlock 			; get a new player block
	rts

; ----------------------------------------------

UpdatePlayMode:
	jsr UpdateRandom

	ldx #5
	jsr readinput
	cmp #PAUSE 			; pressed P?
	bne @skip2
	jmp TogglePause 		; toggle and abort rest of update
@skip2:
	ldx #6
	jsr readinput
	cmp #RESET 			; pressed Q?
	bne rskip3

	lda #MODE_ATTRACT
	sta gameMode
wait_reset_release:
	ldx #6
	jsr readinput
	cmp #RESET 			; pressed Q?
	beq wait_reset_release
	jmp StartAttractMode
	; jmp ResetGame
rskip3:
	lda pauseFlag 			; are we in pause mode?
	beq @skip4 			; no, so continue
	rts 				; yes, abort rest of update

@skip4:
	; check if we are flashing made lines

	lda linesMade 			; did we make lines in previous update?
	beq doInput			; no, continue
	jmp UpdateLineFlash 		; yes, do that, and abort rest of update

doInput:
	jsr GetInput
	ldx inputResult
	cpx #NOINPUT 			; if there was no input ...
	beq doLogic 			; perform game logic and @skip control process
doControls:
	cpx #LEFT
	bne @skipControl1
	jsr BlockLeft

	lda #SND_MOVE_BLOCK
	jsr playsound

	jmp doLogic
@skipControl1:
  	cpx #RIGHT
  	bne @skipControl2
  	jsr BlockRight

	lda #SND_MOVE_BLOCK
	jsr playsound

  	jmp doLogic
@skipControl2:
  	cpx #TURNCOUNTER
  	bne @skipControl3
  	jsr BlockRotateCCW

	lda #SND_ROTATE_BLOCK
	jsr playsound

  	jmp doLogic
@skipControl3:
 	cpx #TURNCLOCK
 	bne @skipControl4
 	jsr BlockRotateCW

	lda #SND_ROTATE_BLOCK
	jsr playsound

 	jmp doLogic
@skipControl4:
	cpx #DOWN
	bne doLogic1
	jsr BlockDown

	lda #SND_DROP_BLOCK
	jsr playsound

doLogic:

	lda #0
	sta key_pressed_flag
doLogic1:
	jsr DropBlock 			; move play block down if delay has passed
	cmp #$02 			; Acc=2 means that a new block is needed
	beq @skip5
	rts 				; block still in play, no line check needed
@skip5:
	jsr CheckLines 			; block has dropped, so check
	lda linesMade 			; are lines made?
	beq @skip6 			; no, place new block
	rts 				; yes. do not create a new block now
					; UpdateLineFlash will do that later on
@skip6:
	jsr NewBlock 			; Acc=0 means the new block fits
	beq @skip7 			; fits. so exit
	jmp EndPlayMode 		; no fit!
@skip7:
	rts

EndPlayMode:
	jsr CheckHighScore
	cpy #3
	beq no_highscore
	lda #MODE_ENTERNAME
	sta gameMode
	jsr StartGameOverMode
	rts
no_highscore:
	lda #MODE_GAMEOVER
	sta gameMode
	jsr StartGameOverMode
	rts

; -------------------------------------------------

; up the player level

AddLevel:
	inc currentLevel		; go up a level

	; update the level values
	; so we can print it later

	sed 				; set decimal mode
	clc 				; clear the carry bit
	lda gameLevel+0  		; get current total lines value
	adc #$01   			; go up a level
	sta gameLevel+0 		; store it.

	lda gameLevel+1 		; and the 2nd byte.
	adc #$00 			; always 0, we can add 4 lines max.
	sta gameLevel+1
	cld 				; clear decimal mode

	; reset the 'lines made this level' counter

	lda levelLinesCounter
	sec
	sbc #linesPerLevel		; restart count ...
	sta levelLinesCounter 		; ... so we can restart this check.

	; decrease the game delay

	lda fallDelay 			; get the current delay
	sec
	sbc #delayChange		; make delay shorter
	bcs @skip8 			; is delay lower than 0?
	lda #delayChange 		; yes: set shortest delay.
@skip8:
	sta fallDelay 			; store the new delay value
	sta fallDelayTimer 		; reset the current delay counter
	rts


; --------------------------------------------------

UpdateLineFlash:
	jsr FlashLines
	lda totalFlashDelay 		; flashed long enough?
	beq exitflash			; yes. remove the lines and update score
	rts 				; not yet. do this again on next update

exitflash:
	; flashing is all done

	jsr AddLinesTotal 		; add the made lines to total
	jsr PrintTotalLinesMade 	; and print these

	jsr AddLineScore		; add score made by lines
	jsr PrintScore 			; show the score

	jsr RemoveLines 		; then remove lines from screen

	lda levelLinesCounter 		; get lines made so far in this level
	clc
	adc linesMade 			; add the made lines
	sta levelLinesCounter

	lda #$00			; reset the lines made
	sta linesMade

	; go up a level?

	lda levelLinesCounter		; get lines made so far at this level
	cmp #linesPerLevel 		; did we make enough to go up a level?
	bcc @skip9 			; no: If the C flag is 0, then A (unsigned) < NUM (unsigned)
					; and BCC will branch
	jsr AddLevel 			; go up 1 level
	jsr PrintLevel 			; print it
@skip9:
	; add a new block to play with

	jsr NewBlock 			; create a new block
	beq @skip10 			; fits. so exit
	jmp EndPlayMode 		; no fit!
@skip10:
	rts

; --------------------------------------------------

TogglePause:
	ldx #5
	jsr readinput
	cmp #PAUSE 			; pressed p?
	beq TogglePause

	lda pauseFlag 			; get the current pause flag
	eor #%00000001 			; flip between 0 and 1
	sta pauseFlag 			; store it

	cmp #$01 			; pause mode?
	beq @skip11 			; yes

	lda #SND_PAUSE_OFF
	jsr playsound

	jmp RestorePlayArea 		; no, restore the screen
@skip11:
	; game is paused. so clear the screen

	lda #$01 			; set the erase flag
	sta playAreaErase 		; so area gets cleared as well
	jsr SavePlayArea 		; save and clear the play area

	lda #SND_PAUSE_ON
	jsr playsound

	jmp PrintPaused

; --------------------------------------------------


PrintPlayScreen:

	; set start of data

	lda #<playscreen
	sta dataSourceLo
	lda #>playscreen
	sta dataSourceHi

	; set data dimensions

	lda #21
	sta dataWidth
	lda #21
	sta dataHeight

	; set start of area to print to

	lda #>(L0400+10)
	sta dataDestinationHi
	lda #<(L0400+10)
	sta dataDestinationLo

	jmp WriteScreenData

; -----------------------------------------------------

PrintPaused:
	lda #<pauseText
	sta dataSourceLo
	lda #>pauseText
	sta dataSourceHi
	lda #10
	sta dataWidth
	lda #20
	sta dataHeight
	lda #>(L0400+12)
	sta dataDestinationHi
	lda #<(L0400+12)
	sta dataDestinationLo
	jmp WriteScreenData

; -----------------------------------------------------

currentLevel:
	.byte 0 			; current player level

gameLevel:
	.byte 0,0 			; values for printing the current level. LSB first.

levelLinesCounter:
	.byte 0 			; this byte holds lines made after last
					; level increase. threshold is declared on top of file.
