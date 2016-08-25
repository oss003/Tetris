
; sound main file.
; sets up irq and provides a way to play sounds

; music definitions in sound file

SND_MOVE_BLOCK = 0
SND_ROTATE_BLOCK = 1
SND_DROP_BLOCK = 2
SND_LINE = 3
SND_TETRIS = 4
SND_PAUSE_ON = 5
SND_PAUSE_OFF = 6
SND_OPTION = 7
SND_MUSIC_TITLE = 9
SND_MUSIC_GAMEOVER = 8

; set accumulator before calling this

playsound:
	stx tmpx
	sty tmpy

        ldx #0
        ldy #0
        jsr SIDinit

	ldx tmpx
	ldy tmpy
	rts

tmpx:	.byte 0
tmpy:	.byte 0

