
;----------------------------------------------------------
; Set PORTB direction
;----------------------------------------------------------

joyinit:
	lda #$ff   ; Write value to latch, bits 0-7 input
	sta $b401

	jsr interwritedelay

	lda #$a1   ; Write direction in latch to PORTB
	sta $b400

wait_until_not_busy:
	lda $b400
	bmi wait_until_not_busy

	rts

;----------------------------------------------------------
; Get PORTB value
;----------------------------------------------------------

joyget:
	lda #$a2   ; Read value PORTB in latch
	sta $b400

	jsr interwritedelay

	lda $b401
	beq no_joystick
	eor #$ff
	and #$1f
no_joystick:
	rts

;----------------------------------------------------------
; Short delay
;
; Enough to intersperse 2 writes to the FATPIC.
;----------------------------------------------------------

interwritedelay:
	lda  #8
	sec
loop:
	sbc  #1
	bne  loop
	rts

tmp_byte:   .byte 0
