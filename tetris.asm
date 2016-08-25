;----------------------------------------------
; Tetris
; C64 conversion by Kees van Oss 2016
;----------------------------------------------
	.DEFINE asm_code $02a00
	.DEFINE header   1		; Header Wouter Ras emulator
	.DEFINE filenaam "TETRIS"

.org asm_code-22*header

.IF header
;********************************************************************
; ATM Header for Atom emulator Wouter Ras

name_start:
	.byte filenaam			; Filename
name_end:
	.repeat 16-name_end+name_start	; Fill with 0 till 16 chars
	  .byte $0
	.endrep

	.word asm_code			; 2 bytes startaddress
	.word exec			; 2 bytes linkaddress
	.word eind_asm-start_asm	; 2 bytes filelength

;********************************************************************
.ENDIF

exec:
start_asm:
	.include "main.inc"
	.include "blocks.inc"
	.include "input.inc"
	.include "screens.inc"
	.include "lines.inc"
	.include "scores.inc"
	.include "random.inc"
	.include "play.inc"
	.include "gameover.inc"
	.include "attract.inc"
	.include "levelselect.inc"
	.include "atomkernal.inc"
	.include "joykey.inc"
	.include "joystick.inc"
	.include "highscore.inc"

char_base:
	.incbin "tetris_chars2.raw"
playscreen:
	.incbin "tetris_playscreen.raw"
gameoverText:
	.incbin "tetris_gameover.raw"
pauseText:
	.incbin "tetris_paused.raw"
titleScreenData:
	.incbin "tetris_titlescreen.raw"
keysScreenData:
	.incbin "tetris_keys.raw"
creditsScreenData:
	.incbin "tetris_credits.raw"
selectScreenData:
	.incbin "tetris_select_and_high.raw"

; SID music

	.repeat ($5200-*)
	  .byte 0
	.endrep
	.include "music.inc"
	.include "sidplay.inc"
	.include "sound.inc"
eind_asm:
