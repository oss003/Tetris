

; code concerning the player score



; resets player score and total lines made.
ResetScore:
	lda #$00
	sta score+0
	sta score+1
	sta score+2
	rts


; this adds the score that is put in the
; addition bytes.
AddScore:
	sed 			; set decimal mode
	clc 			; clear the carry bit
	lda score+0 		; get this score
	adc addition+0 		; add the first byte
	sta score+0 		; store it.
	lda score+1 		; and the 2nd byte
	adc addition+1
	sta score+1
	lda score+2		; and the 3rd byte
	adc addition+2
	sta score+2
	cld 			; clear decimal mode
	rts


; prints the score into the playing field
PrintScore:

	; set cursor position
	clc 			; clear carry bit so we set cursor
	ldx #4+2 			; row 4
	ldy #24-5 		; column 24
	jsr plot 		; move cursor so we can use chrout

	lda #<score
	sta ploop1+1
	lda #>score
	sta ploop1+2

PrintHighScore:
	ldx #$02 		; start with right most byte
ploop1:
	lda score,x 		; get the msb
	pha 			; push to stack
	lsr 			; shift 4 times to right
	lsr
	lsr
	lsr
	clc
	adc #$30 		; add #$30 to it to get a screencode
	jsr chrout 		; print it
	inc XPOS
	pla 			; restore value
	and #%00001111 		; get rid of leftmost bits
	clc
	adc #$30 		; create a screen code
	jsr chrout 		; print it
	inc XPOS
	dex 			; update counter
	bpl ploop1 		; continue
	rts


; this looks at the made lines amount, and the current
; level, and adds the appropriate score: (level+1) * line score
AddLineScore:
	ldy linesMade 		; get made lines amount
	dey 			; minus 1 to get currect offset to lineScore array
	lda lineScore1,y 	; get 1st byte
	sta addition+0 		; put in addition
	lda lineScore2,y 	; same for middle byte
	sta addition+1
	lda lineScore3,y 	; and last byte
	sta addition+2

	ldx currentLevel 	; get the current player level
				; this is how many times the score is added
@loop2:
	jsr AddScore 		; add the score
	dex
	bpl @loop2 		; keep doing this until all levels have been added
	rts




;prints the current play level on the screen
PrintLevel:
	clc 			; position cursor at 26,8
	ldx #8+2
	ldy #26-5
	jsr plot

	; do 1st byte.
	; only do the first 4 bits of this byte

	lda gameLevel+1
	and #%00001111 		; get rid of leftmost bits
	clc
	adc #$30 		; create a screen code
	jsr chrout 		; print it
	inc XPOS

	; do 2nd byte

	lda gameLevel+0
	pha 			; push to stack
	lsr 			; shift 4 times to right
	lsr
	lsr
	lsr
	clc
	adc #$30 		; add #$30 to it to get a screencode
	jsr chrout 		; print it
	inc XPOS

	pla 			; restore value
	and #%00001111 		; get rid of leftmost bits
	clc
	adc #$30 		; create a screen code
	jsr chrout 		; print it
	rts



; ---------------------------

score:
	.byte 0,0,0 		; 24 bits score value, LSB first.
addition:
	.byte 0,0,0 		; score to add goes here


; http:;tetris.wikia.com/wiki/Scoring
; lines:       1   2   3   4
lineScore1:
	.byte $40, 00, 00, 00 	; left most byte of scores
lineScore2:
	.byte  00, 01, 03,$12	; middle byte
lineScore3:
	.byte  00, 00, 00, 00   ; right most byte of score

