L0400	= $4D00
L0500	= L0400+$100
L0600	= L0500+$100
L0700	= L0600+$100

; code concerning game screens

; game screen dimensions
screenWidth 	= 21
screenHeight 	= 21


; ----------------------------------------------

; subroutine to clear the screen and color ram
; also detroys sprite pointers.
ClearScreen:

	lda #>$8000
	sta clr_loop+2

clr_start:
	lda #$00 		; reset offset register
	tax
clr_loop:
	sta $8000,x
	inx 			; increment counter
	bne clr_loop 		; continue?

	inc clr_loop+2
	lda clr_loop+2
	cmp #$98
	bne clr_start

	ldx #$00 		; reset offset register
clr_shadow:
	lda #$20		; #$20 is space
	sta L0400,x 		; store in screen ram
	sta L0500,x
	sta L0600,x
	sta L0700,x
	inx
	bne clr_shadow		; continue?

	rts

; ---------------------------------------------

; this subroutine saves the content of the total play area
; into a buffer.
; If playAreaErase is set to 1 then the area is cleared as well

SavePlayArea:
	; point to the beginning of the first row

	ldx #12  		; x position is set to 12
	ldy #0	 		; y position to 0
	jsr SetScreenPointer 	; set screen memory pointer
	lda #12
	sta blk_x
	lda #0
	sta blk_y

	ldx #$00		; reset buffer pointer
	stx currentRow 		; reset the row counter
@loop1:
	lda (screenPointer),y 	; get screen data
	sta playAreaBuffer,x 	; store it in the buffer
	lda playAreaErase 	; erase it as well?
	beq @skip1 		; no
	lda #$20 		; write a space
	sta (screenPointer),y
	jsr displayblock
@skip1:
	inc blk_x
	inx 			; update buffer pointer
	iny  			; update row character counter
	cpy #10 		; stored whole line?
	bne @loop1 		; no, keep reading

	inc currentRow 		; go to the next row
	lda currentRow 		; what value is it now?
	cmp #20 		; all 20 rows checked?
	beq @skip2	 	; yes, exit
	jsr DownOneRow 		; no, go one row down
	inc blk_y
	ldy #$00 		; reset row character counter
	lda #12
	sta blk_x
	jmp @loop1	 	; do next row
@skip2:
	rts

; ---------------------------------------------

; restores the play area by reading the buffer

RestorePlayArea:
	ldx #12
	ldy #0
	jsr SetScreenPointer
	lda #12
	sta blk_x
	lda #0
	sta blk_y

	ldx #$00 		; reset buffer counter
	stx currentRow 		; and row index
@loop1:
	lda playAreaBuffer,x 	; get buffer data
	sta (screenPointer),y 	; store on screen
	jsr displayblock
@skip1:
	inc blk_x
	inx 			; update buffer pointer
	iny  			; update row character counter
	cpy #10 		; done whole line?
	bne @loop1 		; no

	inc currentRow 		; go to the next row
	lda currentRow 		; what value is it now?
	cmp #20 		; all 20 rows checked?
	beq @skip2	 	; yes, exit
	jsr DownOneRow 		; no, go one row down
	inc blk_y
	ldy #$00 		; reset row character counter
	lda #12
	sta blk_x
	jmp @loop1	 	; do next row
@skip2:
	rts

; ------------------------------------------------

; this routine will copy data to another memory location
; in this case the screen memory
; source and dimensions must be set before calling this

WriteScreenData:
	; get the source address

	lda dataSourceLo
	sta read+1
	lda dataSourceHi
	sta read+2

	; get the destination address
	lda dataDestinationLo
	sta write+1
	lda dataDestinationHi
	sta write+2

	lda dataDestinationLo
	sec
	sbc #5
	sta blk_x
	lda #2
	sta blk_y

	ldx #$00 			; reset read index
	ldy #$00 			; reset write index

	; start copy
read:
	lda $1000,x 			; get data
	pha
write:
	sta $1000,y 			; store at destination

	lda blk_x
	sta XPOS
	lda blk_y
	sta YPOS
	pla
	jsr chrout

	inx 				; update read counter
	bne @skip1 			; roll over?
	inc read+2  			; yes. go to next memory page
@skip1:
	inc blk_x
	iny 				; update row counter
	cpy dataWidth			; this row done?
	bne read 	 		; no, continue

	inc blk_y
	ldy #$00 			; reset the row counter

	lda dataDestinationLo
	sec
	sbc #5
	sta blk_x
	lda write+1 			; get lo byte of current screen position
	clc
	adc #40 			; add 40 to that, goto next row
	bcc @skip2 			; overflow?
	inc write+2  			; then go to next memory page
@skip2:
	sta write+1 			; store lo byte

	dec dataHeight 			; update counter
	lda dataHeight
	bne read 			; not all rows done yet
	rts

; where is the data coming from?
dataSourceHi:
	.byte 0
dataSourceLo:
	.byte 0

; what is the data size?
dataWidth:
	.byte 0
dataHeight:
	.byte 0

; where does it need to go?
; this is a screen memory location
dataDestinationHi:
	.byte 0
dataDestinationLo:
	.byte 0

tmp_x:
	.byte 0
tmp_y:
	.byte 0
row_cnt:
	.byte 0
col_cnt:
	.byte 0
blk_x:
	.byte 0
blk_y:
	.byte 0

; -----------------------------------------------

playAreaErase:
	.byte 0

playAreaBuffer:
	.repeat 10*20
	  .byte 0
	.endrep
