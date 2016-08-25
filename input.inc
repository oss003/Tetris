
keyPressed 		= $83 	; scnkey puts code of held key here.
INPUTDELAY		= 15	; update delay between input checks

; keycodes to check for in inputResult values
; valid controls are also used for joystick results.

LEFT 			= 47 	; , <
RIGHT			= 44	; . >
TURNCOUNTER		= 13	; A
TURNCLOCK 		= 10	; S
DOWN 			= 1 	; ENTER
PAUSE 			= 41 	; P
RESET 			= 4	; F1

CHANGEBACKGROUND 	= 5 	; F3
CHANGECOLOUR 		= 6 	; F5

NOKEY 			= 64
NOINPUT 		= 255	; no input detected

; this byte holds the result of the input query
; game modes can check this byte and get the
; registered input after calling GetInput

inputResult:
	.byte 0


; ------------------------------------------------------

; this routine will scan keyboard first and then the joystick
; but only if there was no input from the keyboard

GetInput:
	jsr GetKeyInput
	lda inputResult
	cmp #NOINPUT
	bne @skip1
	jsr GetJoyInput
@skip1:
	rts

; ------------------------------------------------------

; this subroutine gets keyboard input
; only one key at a time is registered
; "inputResult" will hold the registered input

GetKeyInput:
	lda #NOINPUT 		; first assume there is no input
	sta inputResult

	lda keyPressed
	cmp previousKey 	; is it a different key than before?
	bne skip21	 	; if yes, then @skip the current input delay
				; because we want snappy controls
doDelay:	
	dec inputDelayCounter 	; count down
	beq skip21 		; continue if delay passed
	rts 			; delay ongoing. exit. no input.
skip21:
	sta previousKey 	; save key code for next update
	cmp #NOKEY 		; is it the no key held code?
	bne @skip3 		; no
	lda #NOINPUT 		; yes. select that input result
@skip3:
	sta inputResult 	; store input result

	lda #INPUTDELAY 	; restore key delay counter
	sta inputDelayCounter
	rts

; -------------------------------------------------

; this subroutine checks for joystick input from port 2
; the input register is rotated and the carry bit is checked
; we have only one joystick button, so UP is used for rotate CCW
; "inputResult" will hold the registered input

CIAPRA = $dc00 			; joystick port 2 input register
NOJOY  = $ff 			; value for no joy input

GetJoyInput:
	lda inputResult
	sta keyPressed

	lda #NOINPUT 		; assume there is no input
	sta inputResult

	lda keyPressed 		; load the input byte
	cmp previousJoy 	; same as previous input?
	bne skip41 		; no, so @skip delay
joyDelay:
	dec inputDelayCounter	; update delay
	beq skip41		; continue if delay complete
	rts
skip41:
	ldx #INPUTDELAY 	; reset the delay counter
	stx inputDelayCounter

	sta previousJoy 	; save this input value
;	cmp #NOJOY 		; same as noinput?
;	bne nextjoy1 		; no, so go check the possiblities

;	lda #NOINPUT 		; there is no input, store it
;	sta inputResult 	; in result
;	rts
nextjoy1:
;	clc 			; clear the carry bit
;	lsr 			; check bit 0: joy up
;	bcs nextjoy2

	ldx #2
	jsr readinput
	cmp #TURNCOUNTER 	; store the correct code ...
	bne nextjoy2

	sta inputResult 	; as result
	rts
nextjoy2:
;	lsr 			; check bit 1: joy down
;	bcs nextjoy3 		; bit set means not pressed

	ldx #3
	jsr readinput
	cmp #TURNCLOCK	 	; store the correct code ...
	bne nextjoy3

	sta inputResult
	rts
nextjoy3:
;	lsr 			; check bit 2: joy left
;	bcs nextjoy4

	ldx #0
	jsr readinput
	cmp #LEFT	 	; store the correct code ...
	bne nextjoy4

	sta inputResult
	rts
nextjoy4:
;	lsr 			; check bit 3: joy right
;	bcs nextjoy5

	ldx #1
	jsr readinput
	cmp #RIGHT	 	; store the correct code ...
	bne nextjoy5

	sta inputResult
	rts
nextjoy5:
;	lsr 			; check bit 4: joy fire button
;	bcs nextjoy6

	ldx #4
	jsr readinput
	cmp #DOWN	 	; store the correct code ...
	bne nextjoy6

	sta inputResult
	rts
nextjoy6:
	rts 			; those were all the relevant bits.
				; if we get to this, NOINPUT is still
				; stored in inputResult.

; ------------------------------------------------

inputDelayCounter:
	.byte INPUTDELAY	; if this reaches 0, the player input is read

previousKey:
	.byte DOWN		; previous key held

previousJoy:
	.byte 255 		; previous joy direction held

