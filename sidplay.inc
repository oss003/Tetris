; IRQ routine
; 50 Hz = 1.000.000 / 50 = 20.000 usec

irqtime	= 20000

init:
	sei

	jsr reset		; Reset SID

	lda #>irqvec		; Set IRQ vec
	sta $205
	lda #<irqvec
	sta $204

	lda #<(irqtime)		; Set IRQ timer
	sta $b804
	lda #>(irqtime)
	sta $b805

	lda $b80b		; Continuous IRQ on T1
	and #$7f
	ora #$40
	sta $b80b

	lda $b80e
	ora #$c0		; Enable T1-IRQ
	sta $b80e

	lda #0			; Init SID player
	tax
	tay
	jsr SIDinit

	cli
	rts

irqvec:
	lda $b804		; Clear IRQ flag
	txa
	pha
	tya
	pha

;	inc $c0

	jsr SIDplay		; SID IRQ entry

	pla
	tay
	pla
	tax
	pla
	rti

;--------------------------------------------------
;Reset SID
;--------------------------------------------------

SID	= $bdc0

reset:
      ldx #$1F               ; Reg pointer
      lda #$00
L30B5:
      sta SID,X              ; Clear reg
      dex 
      bpl L30B5
      rts

	