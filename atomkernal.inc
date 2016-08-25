; routine to set cursor position

XPOS	= $84
YPOS	= $85

plot:
	sty XPOS
	stx YPOS
	rts

; ------------------------------------------------
; routine to print character

SCR	= $86

chrout:
	pha

	asl a			; Calculate char address
	rol chr_loop+2
	asl a
	rol chr_loop+2
	asl a
	rol chr_loop+2

	clc
	adc #<char_base
	sta chr_loop+1

	lda chr_loop+2
	and #$07
	adc #>char_base
	sta chr_loop+2

	txa
	pha
	tya
	pha

	lda XPOS		; Calculate screenaddress
	sta SCR
	lda YPOS
	clc
	adc #$80
	sta SCR+1
	
	ldx #7
chr_loop:
	lda $4000,x
	ldy scrtab,x
	sta (SCR),y
	dex
	bpl chr_loop

	pla
	tay
	pla
	tax
	pla
	rts

scrtab:
	.byte $00,$20,$40,$60,$80,$a0,$c0,$e0

wait_press:
	ldx #4
	jsr readinput
	cmp #DOWN 			; enter pressed?
	beq wait_press	 		; yes
	rts