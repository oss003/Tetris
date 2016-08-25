;
; Code equates
;
L00FC       = $00FC
L00FD       = $00FD

L10C1       = L10C0+1
L10CD       = L10CC+1
L1106       = L1105+1
L110A       = L1109+1
L114F       = L114E+1
L1154       = L1153+1
L1159       = L1158+1
L115B       = L115A+1
L1231       = L1230+1
L123A       = L1239+1
L1288       = L1287+1

LD400       = $BDC0
LD401       = $BDC1
LD402       = $BDC2
LD403       = $BDC3
LD404       = $BDC4
LD405       = $BDC5
LD406       = $BDC6
LD415       = $BDD5
LD416       = $BDD6
LD417       = $BDD7
LD418       = $BDD8
;
; Start of code
;
;            *= $1000
;
SIDinit:    jmp L10BC              ; 4C BC 10
SIDplay:    jmp L10CA              ; 4C CA 10
            jmp L10C6              ; 4C C6 10
L1009:      lda L15CE,Y            ; B9 CE 15
            jmp L1016              ; 4C 16 10
            tay                    ; A8
            lda #$00               ; A9 00
            sta L13F8,X            ; 9D F8 13
            tya                    ; 98
L1016:      sta L13CF,X            ; 9D CF 13
            lda L13BE,X            ; BD BE 13
            sta L13CE,X            ; 9D CE 13
            rts                    ; 60
            tay                    ; A8
            lda L1753,Y            ; B9 53 17
            sta L13B7              ; 8D B7 13
            lda L1756,Y            ; B9 56 17
            sta L13B8              ; 8D B8 13
            lda #$00               ; A9 00
            sta L13E5              ; 8D E5 13
            sta L13EC              ; 8D EC 13
            sta L13F3              ; 8D F3 13
            rts                    ; 60
L1039:      dec L13F9,X            ; DE F9 13
L103C:      jmp L12A3              ; 4C A3 12
L103F:      beq L103C              ; F0 FB
            lda L13F9,X            ; BD F9 13
            bne L1039              ; D0 F3
            lda #$00               ; A9 00
            sta L00FD              ; 85 FD
            lda L13F8,X            ; BD F8 13
            bmi L1058              ; 30 09
            cmp L1753,Y            ; D9 53 17
            bcc L1059              ; 90 05
            beq L1058              ; F0 02
            eor #$FF               ; 49 FF
L1058:      clc                    ; 18
L1059:      adc #$02               ; 69 02
            sta L13F8,X            ; 9D F8 13
            lsr A                  ; 4A
            bcc L108F              ; 90 2E
            bcs L10A6              ; B0 43
            tya                    ; 98
            beq L10B6              ; F0 50
            lda L1753,Y            ; B9 53 17
            sta L00FD              ; 85 FD
            lda L13CE,X            ; BD CE 13
            cmp #$02               ; C9 02
            bcc L108F              ; 90 1D
            beq L10A6              ; F0 32
            ldy L13E7,X            ; BC E7 13
            lda L13FB,X            ; BD FB 13
            sbc L1422,Y            ; F9 22 14
            pha                    ; 48
            lda L13FC,X            ; BD FC 13
            sbc L1482,Y            ; F9 82 14
            tay                    ; A8
            pla                    ; 68
            bcs L109F              ; B0 17
            adc L00FC              ; 65 FC
            tya                    ; 98
            adc L00FD              ; 65 FD
            bpl L10B6              ; 10 27
L108F:      lda L13FB,X            ; BD FB 13
            adc L00FC              ; 65 FC
            sta L13FB,X            ; 9D FB 13
            lda L13FC,X            ; BD FC 13
            adc L00FD              ; 65 FD
            jmp L12A0              ; 4C A0 12
L109F:      sbc L00FC              ; E5 FC
            tya                    ; 98
            sbc L00FD              ; E5 FD
            bmi L10B6              ; 30 10
L10A6:      lda L13FB,X            ; BD FB 13
            sbc L00FC              ; E5 FC
            sta L13FB,X            ; 9D FB 13
            lda L13FC,X            ; BD FC 13
            sbc L00FD              ; E5 FD
            jmp L12A0              ; 4C A0 12
L10B6:      ldy L13E7,X            ; BC E7 13
            jmp L1292              ; 4C 92 12
L10BC:      sta L10C1              ; 8D C1 10
            asl A                  ; 0A
L10C0:
            adc #$00               ; 69 00
            sta L10CD              ; 8D CD 10
            rts                    ; 60
L10C6:      sta L115B              ; 8D 5B 11
            rts                    ; 60
L10CA:      ldx #$00               ; A2 00
L10CC:
            ldy #$00               ; A0 00
            bmi L1105              ; 30 35
            txa                    ; 8A
            ldx #$29               ; A2 29
L10D3:      sta L13B9,X            ; 9D B9 13
            dex                    ; CA
            bpl L10D3              ; 10 FA
            sta LD415              ; 8D 15 D4
            sta L1154              ; 8D 54 11
            sta L1106              ; 8D 06 11
            stx L10CD              ; 8E CD 10
            tax                    ; AA
            jsr L10F0              ; 20 F0 10
            ldx #$07               ; A2 07
            jsr L10F0              ; 20 F0 10
            ldx #$0E               ; A2 0E
L10F0:      tya                    ; 98
            iny                    ; C8
            sta L13E3,X            ; 9D E3 13
            lda #$05               ; A9 05
            sta L13E5,X            ; 9D E5 13
            lda #$01               ; A9 01
            sta L13E6,X            ; 9D E6 13
            sta L13E8,X            ; 9D E8 13
            jmp L1398              ; 4C 98 13
L1105:      ldy #$00               ; A0 00
            beq L114E              ; F0 45
L1109:
            lda #$00               ; A9 00
            bne L1130              ; D0 23
            lda L172E,Y            ; B9 2E 17
            beq L1124              ; F0 12
            bpl L112D              ; 10 19
            asl A                  ; 0A
            sta L1159              ; 8D 59 11
            lda L1740,Y            ; B9 40 17
            sta L1154              ; 8D 54 11
            lda L172F,Y            ; B9 2F 17
            bne L1142              ; D0 1F
            iny                    ; C8
L1124:      lda L1740,Y            ; B9 40 17
            sta L114F              ; 8D 4F 11
            jmp L113F              ; 4C 3F 11
L112D:      sta L110A              ; 8D 0A 11
L1130:      lda L1740,Y            ; B9 40 17
            clc                    ; 18
            adc L114F              ; 6D 4F 11
            sta L114F              ; 8D 4F 11
            dec L110A              ; CE 0A 11
            bne L1150              ; D0 11
L113F:      lda L172F,Y            ; B9 2F 17
L1142:      cmp #$FF               ; C9 FF
            iny                    ; C8
            tya                    ; 98
            bcc L114B              ; 90 03
            lda L1740,Y            ; B9 40 17
L114B:      sta L1106              ; 8D 06 11
L114E:      lda #$00               ; A9 00
L1150:      sta LD416              ; 8D 16 D4
L1153:
            lda #$00               ; A9 00
            sta LD417              ; 8D 17 D4
L1158:
            lda #$00               ; A9 00
L115A:
            ora #$0F               ; 09 0F
            sta LD418              ; 8D 18 D4
            jsr L1169              ; 20 69 11
            ldx #$07               ; A2 07
            jsr L1169              ; 20 69 11
            ldx #$0E               ; A2 0E
L1169:      dec L13E6,X            ; DE E6 13
            beq L1188              ; F0 1A
            bpl L1185              ; 10 15
            lda L13E5,X            ; BD E5 13
            cmp #$02               ; C9 02
            bcs L1182              ; B0 0B
            tay                    ; A8
            eor #$01               ; 49 01
            sta L13E5,X            ; 9D E5 13
            lda L13B7,Y            ; B9 B7 13
            sbc #$00               ; E9 00
L1182:      sta L13E6,X            ; 9D E6 13
L1185:      jmp L123C              ; 4C 3C 12
L1188:      ldy L13BE,X            ; BC BE 13
            lda L13A2,Y            ; B9 A2 13
            sta L1231              ; 8D 31 12
            sta L123A              ; 8D 3A 12
            lda L13BC,X            ; BD BC 13
            bne L11C9              ; D0 30
            ldy L13E3,X            ; BC E3 13
            lda L14E2,Y            ; B9 E2 14
            sta L00FC              ; 85 FC
            lda L1500,Y            ; B9 00 15
            sta L00FD              ; 85 FD
            ldy L13B9,X            ; BC B9 13
            lda (L00FC),Y          ; B1 FC
            cmp #$FF               ; C9 FF
            bcc L11B5              ; 90 06
            iny                    ; C8
            lda (L00FC),Y          ; B1 FC
            tay                    ; A8
            lda (L00FC),Y          ; B1 FC
L11B5:      cmp #$E0               ; C9 E0
            bcc L11C1              ; 90 08
            sbc #$F0               ; E9 F0
            sta L13BA,X            ; 9D BA 13
            iny                    ; C8
            lda (L00FC),Y          ; B1 FC
L11C1:      sta L13E4,X            ; 9D E4 13
            iny                    ; C8
            tya                    ; 98
            sta L13B9,X            ; 9D B9 13
L11C9:      ldy L13E8,X            ; BC E8 13
            lda L15F8,Y            ; B9 F8 15
            sta L1412,X            ; 9D 12 14
            lda L13D0,X            ; BD D0 13
            beq L1236              ; F0 5F
            sec                    ; 38
            sbc #$60               ; E9 60
            sta L13E7,X            ; 9D E7 13
            lda #$00               ; A9 00
            sta L13CE,X            ; 9D CE 13
            sta L13D0,X            ; 9D D0 13
            lda L15E3,Y            ; B9 E3 15
            sta L13F9,X            ; 9D F9 13
            lda L15CE,Y            ; B9 CE 15
            sta L13CF,X            ; 9D CF 13
            lda L13BE,X            ; BD BE 13
            cmp #$03               ; C9 03
            beq L1236              ; F0 3E
            lda L160D,Y            ; B9 0D 16
            sta L13D2,X            ; 9D D2 13
            inc L13E9,X            ; FE E9 13
            lda L15A4,Y            ; B9 A4 15
            beq L120E              ; F0 08
            sta L13D3,X            ; 9D D3 13
            lda #$00               ; A9 00
            sta L13D4,X            ; 9D D4 13
L120E:      lda L15B9,Y            ; B9 B9 15
            beq L121B              ; F0 08
            sta L1106              ; 8D 06 11
            lda #$00               ; A9 00
            sta L110A              ; 8D 0A 11
L121B:      lda L158F,Y            ; B9 8F 15
            sta L13D1,X            ; 9D D1 13
            lda L157A,Y            ; B9 7A 15
            sta L140E,X            ; 9D 0E 14
            lda L1565,Y            ; B9 65 15
            sta L140D,X            ; 9D 0D 14
            lda L13BF,X            ; BD BF 13
L1230:
            jsr L1009              ; 20 09 10
            jmp L1374              ; 4C 74 13
L1236:      lda L13BF,X            ; BD BF 13
L1239:
            jsr L1009              ; 20 09 10
L123C:      ldy L13D1,X            ; BC D1 13
            beq L1271              ; F0 30
            lda L1622,Y            ; B9 22 16
            cmp #$10               ; C9 10
            bcs L1252              ; B0 0A
            cmp L13FA,X            ; DD FA 13
            beq L1257              ; F0 0A
            inc L13FA,X            ; FE FA 13
            bne L1271              ; D0 1F
L1252:      sbc #$10               ; E9 10
            sta L13D2,X            ; 9D D2 13
L1257:      lda L1623,Y            ; B9 23 16
            cmp #$FF               ; C9 FF
            iny                    ; C8
            tya                    ; 98
            bcc L1264              ; 90 04
            clc                    ; 18
            lda L167D,Y            ; B9 7D 16
L1264:      sta L13D1,X            ; 9D D1 13
            lda #$00               ; A9 00
            sta L13FA,X            ; 9D FA 13
            lda L167C,Y            ; B9 7C 16
            bne L128A              ; D0 19
L1271:      lda L13E6,X            ; BD E6 13
            beq L12A6              ; F0 30
            ldy L13CE,X            ; BC CE 13
            lda L13B2,Y            ; B9 B2 13
            sta L1288              ; 8D 88 12
            ldy L13CF,X            ; BC CF 13
            lda L1756,Y            ; B9 56 17
            sta L00FC              ; 85 FC
L1287:
            jmp L103F              ; 4C 3F 10
L128A:      bpl L1291              ; 10 05
            adc L13E7,X            ; 7D E7 13
            and #$7F               ; 29 7F
L1291:      tay                    ; A8
L1292:      lda #$00               ; A9 00
            sta L13F8,X            ; 9D F8 13
            lda L1422,Y            ; B9 22 14
            sta L13FB,X            ; 9D FB 13
            lda L1482,Y            ; B9 82 14
L12A0:      sta L13FC,X            ; 9D FC 13
L12A3:      lda L13E6,X            ; BD E6 13
L12A6:      cmp L1412,X            ; DD 12 14
            beq L12F9              ; F0 4E
            ldy L13D3,X            ; BC D3 13
            beq L12F6              ; F0 46
            ora L13BC,X            ; 1D BC 13
            beq L12F6              ; F0 41
            lda L13D4,X            ; BD D4 13
            bne L12CE              ; D0 14
            lda L16D8,Y            ; B9 D8 16
            bpl L12CB              ; 10 0C
            sta L13FE,X            ; 9D FE 13
            lda L1703,Y            ; B9 03 17
            sta L13FD,X            ; 9D FD 13
            jmp L12E7              ; 4C E7 12
L12CB:      sta L13D4,X            ; 9D D4 13
L12CE:      lda L1703,Y            ; B9 03 17
            clc                    ; 18
            bpl L12D7              ; 10 03
            dec L13FE,X            ; DE FE 13
L12D7:      adc L13FD,X            ; 7D FD 13
            sta L13FD,X            ; 9D FD 13
            bcc L12E2              ; 90 03
            inc L13FE,X            ; FE FE 13
L12E2:      dec L13D4,X            ; DE D4 13
            bne L12F6              ; D0 0F
L12E7:      lda L16D9,Y            ; B9 D9 16
            cmp #$FF               ; C9 FF
            iny                    ; C8
            tya                    ; 98
            bcc L12F3              ; 90 03
            lda L1703,Y            ; B9 03 17
L12F3:      sta L13D3,X            ; 9D D3 13
L12F6:      jmp L1374              ; 4C 74 13
L12F9:      ldy L13E4,X            ; BC E4 13
            lda L151E,Y            ; B9 1E 15
            sta L00FC              ; 85 FC
            lda L1542,Y            ; B9 42 15
            sta L00FD              ; 85 FD
            ldy L13BC,X            ; BC BC 13
            lda (L00FC),Y          ; B1 FC
            cmp #$40               ; C9 40
            bcc L1327              ; 90 18
            cmp #$60               ; C9 60
            bcc L1331              ; 90 1E
            cmp #$C0               ; C9 C0
            bcc L1345              ; 90 2E
            lda L13BD,X            ; BD BD 13
            bne L131E              ; D0 02
            lda (L00FC),Y          ; B1 FC
L131E:      adc #$00               ; 69 00
            sta L13BD,X            ; 9D BD 13
            beq L136B              ; F0 46
            bne L1374              ; D0 4D
L1327:      sta L13E8,X            ; 9D E8 13
            iny                    ; C8
            lda (L00FC),Y          ; B1 FC
            cmp #$60               ; C9 60
            bcs L1345              ; B0 14
L1331:      cmp #$50               ; C9 50
            and #$0F               ; 29 0F
            sta L13BE,X            ; 9D BE 13
            beq L1340              ; F0 06
            iny                    ; C8
            lda (L00FC),Y          ; B1 FC
            sta L13BF,X            ; 9D BF 13
L1340:      bcs L136B              ; B0 29
            iny                    ; C8
            lda (L00FC),Y          ; B1 FC
L1345:      cmp #$BD               ; C9 BD
            bcc L134F              ; 90 06
            beq L136B              ; F0 20
            ora #$F0               ; 09 F0
            bne L1368              ; D0 19
L134F:      adc L13BA,X            ; 7D BA 13
            sta L13D0,X            ; 9D D0 13
            lda L13BE,X            ; BD BE 13
            cmp #$03               ; C9 03
            beq L136B              ; F0 0F
            lda #$00               ; A9 00
            sta L140E,X            ; 9D 0E 14
            lda #$0F               ; A9 0F
            sta L140D,X            ; 9D 0D 14
            lda #$FE               ; A9 FE
L1368:      sta L13E9,X            ; 9D E9 13
L136B:      iny                    ; C8
            lda (L00FC),Y          ; B1 FC
            beq L1371              ; F0 01
            tya                    ; 98
L1371:      sta L13BC,X            ; 9D BC 13
L1374:      lda L13FD,X            ; BD FD 13
            sta LD402,X            ; 9D 02 D4
            lda L13FE,X            ; BD FE 13
            sta LD403,X            ; 9D 03 D4
            lda L140E,X            ; BD 0E 14
            sta LD406,X            ; 9D 06 D4
            lda L140D,X            ; BD 0D 14
            sta LD405,X            ; 9D 05 D4
            lda L13FB,X            ; BD FB 13
            sta LD400,X            ; 9D 00 D4
            lda L13FC,X            ; BD FC 13
            sta LD401,X            ; 9D 01 D4
L1398:      lda L13D2,X            ; BD D2 13
            and L13E9,X            ; 3D E9 13
            sta LD404,X            ; 9D 04 D4
            rts                    ; 60
L13A2:      .byte $09,$0F,$0F,$16,$16,$20,$20,$20
            .byte $20,$20,$20,$20,$20,$20,$20,$2F
L13B2:      .byte $3F,$66,$66,$63,$46
L13B7:      .byte $08
L13B8:      .byte $05
L13B9:      .byte $00
L13BA:      .byte $00,$00
L13BC:      .byte $00
L13BD:      .byte $00
L13BE:      .byte $00
L13BF:      .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00
L13CE:      .byte $00
L13CF:      .byte $00
L13D0:      .byte $00
L13D1:      .byte $00
L13D2:      .byte $00
L13D3:      .byte $00
L13D4:      .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00
L13E3:      .byte $00
L13E4:      .byte $00
L13E5:      .byte $00
L13E6:      .byte $00
L13E7:      .byte $00
L13E8:      .byte $01
L13E9:      .byte $FE,$01,$00
L13EC:      .byte $00,$00,$00,$01,$FE,$02,$00
L13F3:      .byte $00,$00,$00,$01,$FE
L13F8:      .byte $00
L13F9:      .byte $00
L13FA:      .byte $00
L13FB:      .byte $00
L13FC:      .byte $00
L13FD:      .byte $00
L13FE:      .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00
L140D:      .byte $00
L140E:      .byte $00,$00,$00,$00
L1412:      .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
L1422:      .byte $17,$27,$39,$4B,$5F,$74,$8A,$A1
            .byte $BA,$D4,$F0,$0E,$2D,$4E,$71,$96
            .byte $BE,$E8,$14,$43,$74,$A9,$E1,$1C
            .byte $5A,$9C,$E2,$2D,$7C,$CF,$28,$85
            .byte $E8,$52,$C1,$37,$B4,$39,$C5,$5A
            .byte $F7,$9E,$4F,$0A,$D1,$A3,$82,$6E
            .byte $68,$71,$8A,$B3,$EE,$3C,$9E,$15
            .byte $A2,$46,$04,$DC,$D0,$E2,$14,$67
            .byte $DD,$79,$3C,$29,$44,$8D,$08,$B8
            .byte $A1,$C5,$28,$CD,$BA,$F1,$78,$53
            .byte $87,$1A,$10,$71,$42,$89,$4F,$9B
            .byte $74,$E2,$F0,$A6,$0E,$33,$20,$FF
L1482:      .byte $01,$01,$01,$01,$01,$01,$01,$01
            .byte $01,$01,$01,$02,$02,$02,$02,$02
            .byte $02,$02,$03,$03,$03,$03,$03,$04
            .byte $04,$04,$04,$05,$05,$05,$06,$06
            .byte $06,$07,$07,$08,$08,$09,$09,$0A
            .byte $0A,$0B,$0C,$0D,$0D,$0E,$0F,$10
            .byte $11,$12,$13,$14,$15,$17,$18,$1A
            .byte $1B,$1D,$1F,$20,$22,$24,$27,$29
            .byte $2B,$2E,$31,$34,$37,$3A,$3E,$41
            .byte $45,$49,$4E,$52,$57,$5C,$62,$68
            .byte $6E,$75,$7C,$83,$8B,$93,$9C,$A5
            .byte $AF,$B9,$C4,$D0,$DD,$EA,$F8,$FF

;------------------------------------------------
; Table pointers

L14E2:      .byte <L1759,<L175D,<L1761,<L1765,<L1769,<L176D,<L1771,<L1775
            .byte <L1779,<L177D,<L1781,<L1785,<L1789,<L178D,<L1791,<L1795
            .byte <L1799,<L179D,<L17A1,<L17A6,<L17AB,<L17B0,<L17B4,<L17B9
            .byte <L17BE,<L17C2,<L17C9,<L17D3,<L17D6,<L17E2

L1500:      .byte >L1759,>L175D,>L1761,>L1765,>L1769,>L176D,>L1771,>L1775
            .byte >L1779,>L177D,>L1781,>L1785,>L1789,>L178D,>L1791,>L1795
            .byte >L1799,>L179D,>L17A1,>L17A6,>L17AB,>L17B0,>L17B4,>L17B9
            .byte >L17BE,>L17C2,>L17C9,>L17D3,>L17D6,>L17E2

;------------------------------------------------

L151E:      .byte <L17EE,<L17F3,<L17F7,<L17FC,<L1809,<L1812,<L181F,<L182E
            .byte <L184D,<L1857,<L1862,<L1872,<L1882,<L1887,<L188D,<L1892
            .byte <L1897,<L189D,<L18AD,<L18B6,<L18BE,<L1901,<L190C,<L192D
            .byte <L1969,<L19B7,<L1932,<L1A88,<L1AE3,<L1AE7,<L1B37,<L1B83
            .byte <L1BDB,<L1C33,<L1C81,<L1CE5

L1542:      .byte >L17EE,>L17F3,>L17F7,>L17FC,>L1809,>L1812,>L181F,>L182E
            .byte >L184D,>L1857,>L1862,>L1872,>L1882,>L1887,>L188D,>L1892
            .byte >L1897,>L189D,>L18AD,>L18B6,>L18BE,>L1901,>L190C,>L192D
            .byte >L1969,>L19B7,>L1932,>L1A88,>L1AE3,>L1AE7,>L1B37,>L1B83
            .byte >L1BDB,>L1C33,>L1C81

;------------------------------------------------
L1759	= L1500+$259
L175D	= L1500+$25D
L1761	= L1500+$261
L1765	= L1500+$265
L1769	= L1500+$269
L176D	= L1500+$26D
L1771	= L1500+$271
L1775	= L1500+$275
L1779	= L1500+$279
L177D	= L1500+$27D
L1781	= L1500+$281
L1785	= L1500+$285
L1789	= L1500+$289
L178D	= L1500+$28D
L1791	= L1500+$291
L1795	= L1500+$295
L1799	= L1500+$299
L179D	= L1500+$29D
L17A1	= L1500+$2A1
L17A6	= L1500+$2A6
L17AB	= L1500+$2AB
L17B0	= L1500+$2B0
L17B4	= L1500+$2B4
L17B9	= L1500+$2B9
L17BE	= L1500+$2BE
L17C2	= L1500+$2C2
L17C9	= L1500+$2C9
L17D3	= L1500+$2D3
L17D6	= L1500+$2D6
L17E2	= L1500+$2E2
L17EE	= L1500+$2EE
L17F3	= L1500+$2F3
L17F7	= L1500+$2F7
L17FC	= L1500+$2FC
L1809	= L1500+$309
L1812	= L1500+$312
L181F	= L1500+$31F
L182E	= L1500+$32E
L184D	= L1500+$34D
L1857	= L1500+$357
L1862	= L1500+$362
L1872	= L1500+$372
L1882	= L1500+$382
L1887	= L1500+$387
L188D	= L1500+$38D
L1892	= L1500+$392
L1897	= L1500+$397
L189D	= L1500+$39D
L18AD	= L1500+$3AD
L18B6	= L1500+$3B6
L18BE	= L1500+$3BE
L1901	= L1500+$401
L190C	= L1500+$40C
L192D	= L1500+$42D
L1969	= L1500+$469
L19B7	= L1500+$4B7
L1932	= L1500+$432
L1A88	= L1500+$588
L1AE3	= L1500+$5E3
L1AE7	= L1500+$5E7
L1B37	= L1500+$637
L1B83	= L1500+$683
L1BDB	= L1500+$6DB
L1C33	= L1500+$733
L1C81	= L1500+$781
L1CE5	= L1500+$7E5

L1565:      .byte $1C,$00,$00,$12,$29,$33,$21,$00
            .byte $2F,$2F,$02,$C0,$00,$06,$AB,$C8
            .byte $00,$00,$00,$00,$00
L157A:      .byte $01,$35,$25,$00,$00,$00,$01,$50
            .byte $AA,$49,$22,$0A,$E5,$00,$0A,$AC
            .byte $A8,$F4,$F5,$C8,$C8
L158F:      .byte $22,$01,$1B,$08,$0B,$0E,$15,$19
            .byte $24,$1E,$28,$2C,$31,$34,$19,$3A
            .byte $3C,$42,$4D,$58,$52
L15A4:      .byte $15,$01,$07,$05,$01,$01,$00,$00
            .byte $00,$00,$00,$0C,$25,$00,$00,$25
            .byte $00,$25,$25,$27,$27
L15B9:      .byte $00,$01,$00,$01,$01,$00,$05,$00
            .byte $00,$00,$00,$00,$08,$00,$00,$00
            .byte $00,$00,$00,$0B,$0B
L15CE:      .byte $00,$00,$00,$01,$00,$00,$00,$00
            .byte $01,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00
L15E3:      .byte $00,$00,$00,$0F,$00,$00,$00,$00
            .byte $01,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00
L15F8:      .byte $00,$02,$02,$01,$02,$01,$02,$02
            .byte $04,$02,$02,$02,$02,$02,$02,$02
            .byte $02,$02,$02,$02,$02
L160D:      .byte $02,$09,$19,$07,$09,$09,$09,$09
            .byte $02,$02,$09,$09,$09,$09,$09,$09
            .byte $09,$09,$09,$09,$09
L1622:      .byte $09
L1623:      .byte $51,$51,$51,$51,$51,$51,$FF,$91
            .byte $21,$FF,$21,$21,$FF,$21,$21,$21
            .byte $21,$21,$21,$FF,$91,$01,$90,$FF
            .byte $21,$FF,$21,$51,$FF,$27,$27,$27
            .byte $27,$27,$FF,$21,$20,$20,$FF,$91
            .byte $91,$20,$FF,$31,$00,$00,$00,$FF
            .byte $91,$90,$FF,$21,$21,$21,$21,$21
            .byte $FF,$27,$FF,$21,$00,$21,$00,$20
            .byte $FF,$51,$50,$20,$20,$20,$20,$20
            .byte $20,$20,$20,$FF,$91,$51,$50,$90
            .byte $FF,$91,$91,$20,$20,$51,$FF,$21
            .byte $20
L167C:      .byte $51
L167D:      .byte $FF,$80,$80,$84,$84,$87,$87,$01
            .byte $50,$80,$09,$80,$80,$0C,$80,$85
            .byte $83,$85,$83,$80,$10,$5F,$5F,$4F
            .byte $00,$80,$00,$8C,$80,$00,$8C,$8C
            .byte $8C,$8C,$8C,$00,$80,$8C,$80,$00
            .byte $68,$58,$80,$00,$80,$84,$87,$8E
            .byte $2C,$28,$20,$32,$80,$81,$86,$88
            .byte $8C,$05,$80,$00,$82,$81,$80,$80
            .byte $80,$00,$2A,$28,$24,$20,$1C,$18
            .byte $14,$13,$10,$0B,$00,$46,$2E,$2D
            .byte $5F,$00,$3D,$22,$90,$90,$80,$00
            .byte $3D,$22,$80
L16D8:      .byte $00
L16D9:      .byte $31,$88,$00,$FF,$80,$FF,$85,$03
            .byte $07,$07,$FF,$70,$01,$80,$04,$80
            .byte $04,$80,$04,$80,$04,$80,$04,$80
            .byte $04,$80,$04,$80,$04,$80,$04,$80
            .byte $04,$80,$04,$FF,$88,$FF,$88,$81
            .byte $10,$10
L1703:      .byte $FF,$18,$88,$06,$01,$00,$00,$00
            .byte $0A,$D0,$20,$09,$80,$00,$60,$00
            .byte $70,$00,$80,$00,$90,$00,$A0,$00
            .byte $B0,$00,$A0,$00,$90,$00,$80,$00
            .byte $70,$00,$60,$00,$0C,$00,$00,$00
            .byte $10,$20,$E0
L172E:      .byte $29
L172F:      .byte $88,$00,$7F,$FF,$A0,$00,$FF,$10
            .byte $10,$7F,$B0,$00,$88,$00,$0A,$04
            .byte $04
L1740:      .byte $FF,$81,$88,$FA,$04,$F1,$A0,$00
            .byte $11,$40,$01,$A1,$A2,$C1,$03,$01
            .byte $11,$F0,$10
L1753:      .byte $00,$03,$09
L1756:      .byte $00,$10,$05,$00,$01,$FF,$01,$02
            .byte $01,$FF,$01,$0E,$01,$FF,$01,$0F
            .byte $01,$FF,$01,$10,$01,$FF,$01,$01
            .byte $01,$FF,$01,$0C,$01,$FF,$01,$0C
            .byte $01,$FF,$01,$0D,$01,$FF,$01,$11
            .byte $01,$FF,$01,$13,$01,$FF,$01,$12
            .byte $01,$FF,$01,$07,$01,$FF,$01,$05
            .byte $01,$FF,$01,$06,$01,$FF,$01,$0A
            .byte $01,$FF,$01,$08,$01,$FF,$01,$09
            .byte $01,$FF,$01,$F3,$0B,$01,$FF,$02
            .byte $F3,$08,$01,$FF,$02,$F3,$09,$01
            .byte $FF,$02,$03,$01,$FF,$01,$EB,$03
            .byte $01,$FF,$02,$E4,$04,$01,$FF,$02
            .byte $E4,$14,$FF,$00,$15,$17,$19,$18
            .byte $19,$FF,$00,$F0,$16,$EE,$16,$EC
            .byte $16,$EE,$16,$FF,$00,$1B,$FF,$00
            .byte $1E,$1E,$1E,$1E,$22,$1E,$22,$22
            .byte $22,$1E,$FF,$00,$1C,$1A,$1D,$1F
            .byte $20,$1C,$23,$21,$1F,$20,$FF,$00
            .byte $03,$40,$60,$F9,$00,$40,$BE,$F9
            .byte $00,$06,$40,$78,$F9,$00,$08,$4F
            .byte $04,$97,$43,$00,$9C,$A3,$AA,$40
            .byte $BE,$FD,$00,$09,$40,$8B,$90,$97
            .byte $9E,$BE,$FD,$00,$08,$40,$90,$43
            .byte $00,$95,$94,$97,$90,$95,$94,$9C
            .byte $00,$07,$40,$9C,$43,$00,$A0,$A3
            .byte $A8,$50,$43,$00,$A1,$A0,$BE,$00
            .byte $02,$4F,$07,$84,$06,$4F,$05,$78
            .byte $01,$4F,$07,$9C,$4F,$05,$9C,$02
            .byte $4F,$07,$84,$08,$4F,$05,$84,$01
            .byte $4F,$07,$9C,$4F,$05,$9C,$00,$04
            .byte $40,$86,$43,$00,$8B,$8F,$50,$FC
            .byte $00,$0B,$4F,$07,$9E,$40,$BE,$FE
            .byte $9C,$BE,$FE,$00,$02,$40,$9B,$43
            .byte $00,$9C,$9E,$A0,$9C,$40,$BE,$8F
            .byte $43,$00,$8B,$00,$02,$40,$9B,$43
            .byte $00,$9C,$9E,$A0,$9C,$40,$BE,$8B
            .byte $43,$00,$92,$00,$0C,$40,$84,$F9
            .byte $00,$02,$40,$6C,$BE,$FA,$00,$0A
            .byte $40,$6C,$F9,$00,$0D,$40,$90,$F9
            .byte $00,$05,$40,$90,$BE,$FA,$00,$02
            .byte $4F,$07,$84,$06,$4F,$05,$78,$01
            .byte $4F,$07,$9C,$4F,$05,$9C,$00,$07
            .byte $40,$9C,$43,$00,$A0,$A3,$A8,$00
            .byte $03,$40,$78,$78,$BD,$0A,$84,$00
            .byte $04,$40,$90,$BD,$95,$BD,$97,$BD
            .byte $9C,$BD,$90,$BD,$95,$BD,$97,$BD
            .byte $9C,$BD,$8E,$BD,$93,$BD,$95,$BD
            .byte $9A,$BD,$8E,$BD,$93,$BD,$95,$BD
            .byte $9A,$BD,$8C,$BD,$90,$BD,$93,$BD
            .byte $98,$BD,$8C,$BD,$90,$BD,$93,$BD
            .byte $98,$BD,$8E,$BD,$92,$BD,$95,$BD
            .byte $9A,$BD,$8E,$BD,$92,$BD,$95,$BD
            .byte $9A,$BD,$00,$0E,$40,$9C,$F1,$9F
            .byte $F1,$A1,$F1,$9E,$F1,$00,$0F,$40
            .byte $9C,$BE,$07,$9C,$52,$01,$0D,$40
            .byte $90,$0F,$A8,$43,$00,$AA,$AD,$05
            .byte $40,$97,$BD,$07,$97,$52,$01,$0D
            .byte $40,$90,$BD,$05,$97,$BD,$00,$0E
            .byte $40,$9C,$FE,$BE,$07,$9C,$FD,$43
            .byte $00,$9F,$50,$FA,$0E,$9E,$FE,$BE
            .byte $07,$9A,$FD,$43,$00,$95,$50,$FA
            .byte $0E,$93,$FE,$BE,$07,$92,$BD,$43
            .byte $00,$93,$50,$43,$00,$92,$50,$FE
            .byte $43,$00,$93,$50,$FE,$0E,$95,$FE
            .byte $BE,$9A,$FE,$BE,$9E,$FE,$BE,$9A
            .byte $FE,$BE,$00,$0E,$40,$9C,$43,$00
            .byte $9E,$9F,$A3,$9C,$9E,$9F,$A3,$9C
            .byte $9E,$9F,$A3,$9C,$9E,$9F,$A3,$40
            .byte $9A,$43,$00,$9C,$9E,$A1,$9A,$9C
            .byte $9E,$A1,$9A,$9C,$9E,$A1,$9A,$9C
            .byte $9E,$A1,$40,$98,$43,$00,$9C,$9E
            .byte $9F,$98,$9C,$9E,$9F,$98,$9C,$9E
            .byte $9F,$98,$9C,$9E,$9F,$40,$9A,$43
            .byte $00,$9E,$A1,$A6,$9A,$9E,$A1,$A6
            .byte $9A,$9E,$A1,$A6,$9A,$9E,$A1,$A6
            .byte $00,$0E,$40,$A6,$BD,$43,$00,$A5
            .byte $50,$43,$00,$A3,$50,$43,$00,$A1
            .byte $50,$43,$00,$9F,$50,$43,$00,$9E
            .byte $50,$43,$00,$9C,$50,$43,$00,$9A
            .byte $50,$97,$BD,$43,$00,$9A,$50,$43
            .byte $00,$9E,$50,$43,$00,$A1,$50,$43
            .byte $00,$A6,$50,$43,$00,$A1,$50,$43
            .byte $00,$9E,$50,$43,$00,$9A,$50,$98
            .byte $BD,$43,$00,$9C,$50,$43,$00,$9F
            .byte $50,$43,$00,$A4,$50,$43,$00,$A8
            .byte $50,$43,$00,$A4,$50,$43,$00,$9F
            .byte $50,$43,$00,$9C,$50,$9A,$BD,$43
            .byte $00,$9E,$50,$43,$00,$A1,$50,$43
            .byte $00,$A6,$50,$43,$00,$AA,$50,$43
            .byte $00,$A6,$50,$43,$00,$A1,$50,$43
            .byte $00,$9E,$50,$00,$50,$BD,$10,$9C
            .byte $BD,$02,$A0,$43,$00,$A1,$A3,$50
            .byte $BD,$BE,$A0,$BD,$BE,$BD,$A1,$BD
            .byte $43,$00,$A0,$50,$10,$A1,$BD,$02
            .byte $9C,$BD,$10,$A1,$BD,$02,$97,$BD
            .byte $BE,$BD,$94,$BD,$95,$BD,$97,$BD
            .byte $10,$9C,$BD,$02,$9C,$BD,$10,$9C
            .byte $BD,$02,$A0,$BD,$9C,$FD,$95,$43
            .byte $00,$97,$9A,$50,$10,$9A,$BD,$02
            .byte $9A,$BD,$10,$9A,$BD,$02,$9B,$BD
            .byte $10,$9B,$BD,$02,$9B,$BD,$10,$9B
            .byte $BD,$00,$13,$40,$78,$BE,$84,$BE
            .byte $14,$78,$BE,$13,$84,$06,$9C,$13
            .byte $78,$BE,$84,$BE,$14,$78,$BE,$13
            .byte $84,$BE,$76,$BE,$82,$BE,$14,$76
            .byte $BE,$13,$82,$06,$9C,$13,$76,$BE
            .byte $82,$BE,$14,$76,$BE,$13,$82,$BE
            .byte $75,$BE,$81,$BE,$14,$75,$BE,$13
            .byte $81,$06,$9C,$13,$75,$BE,$81,$BE
            .byte $14,$75,$BE,$13,$81,$BE,$76,$BE
            .byte $82,$BE,$14,$76,$BE,$13,$82,$06
            .byte $9C,$13,$77,$BE,$83,$BE,$14,$77
            .byte $BE,$13,$83,$BE,$00,$40,$BE,$C1
            .byte $00,$08,$40,$9C,$BD,$A0,$BD,$0A
            .byte $90,$BE,$08,$A1,$BD,$07,$A1,$BD
            .byte $08,$A0,$BD,$0A,$84,$BE,$FE,$08
            .byte $9A,$BD,$9E,$BD,$0A,$84,$BE,$08
            .byte $A6,$FE,$BE,$A1,$BD,$0A,$84,$BE
            .byte $FE,$08,$A0,$BD,$9C,$BD,$0A,$84
            .byte $BE,$08,$A0,$BD,$07,$A0,$BD,$08
            .byte $A1,$BD,$0A,$84,$BE,$FE,$08,$9E
            .byte $BD,$9C,$BD,$0A,$84,$BE,$08,$9A
            .byte $FD,$07,$9B,$BD,$0A,$84,$BE,$FE
            .byte $00,$5E,$02,$50,$02,$97,$BE,$0D
            .byte $90,$BD,$02,$97,$BE,$FE,$97,$BE
            .byte $0D,$90,$BD,$02,$97,$BE,$FE,$95
            .byte $BE,$0D,$8E,$BD,$02,$95,$BE,$FE
            .byte $95,$BE,$0D,$8E,$BD,$02,$95,$BE
            .byte $FE,$94,$BE,$0D,$8D,$BD,$02,$94
            .byte $BE,$FE,$94,$BE,$0D,$8D,$BD,$02
            .byte $94,$BE,$FE,$92,$BE,$0D,$8E,$BD
            .byte $02,$92,$BE,$FE,$92,$BE,$0D,$8E
            .byte $BD,$02,$92,$BE,$00,$02,$40,$97
            .byte $BD,$43,$00,$94,$50,$43,$00,$90
            .byte $50,$43,$00,$8B,$50,$43,$00,$8E
            .byte $50,$43,$00,$90,$50,$43,$00,$8B
            .byte $50,$BE,$FD,$05,$A3,$A3,$FE,$A3
            .byte $A3,$FE,$A3,$A3,$FE,$A3,$A3,$02
            .byte $95,$BD,$43,$00,$94,$50,$43,$00
            .byte $95,$50,$43,$00,$94,$50,$43,$00
            .byte $90,$50,$43,$00,$92,$50,$43,$00
            .byte $90,$50,$43,$00,$92,$50,$BE,$BD
            .byte $05,$A3,$A3,$FE,$A3,$A3,$FE,$A3
            .byte $A3,$FE,$A3,$A3,$00,$02,$40,$97
            .byte $BD,$43,$00,$94,$50,$43,$00,$90
            .byte $50,$43,$00,$8B,$50,$43,$00,$8E
            .byte $50,$43,$00,$90,$50,$43,$00,$8B
            .byte $50,$BE,$FD,$05,$A3,$A3,$0A,$A3
            .byte $A3,$A3,$BD,$A3,$BD,$A3,$FB,$02
            .byte $A1,$BD,$43,$00,$A0,$50,$43,$00
            .byte $A1,$50,$43,$00,$A3,$50,$43,$00
            .byte $A1,$50,$43,$00,$A0,$50,$43,$00
            .byte $A1,$50,$43,$00,$A3,$50,$BE,$BD
            .byte $05,$A3,$A3,$FE,$A3,$A3,$FE,$A3
            .byte $A3,$FE,$A3,$A3,$00,$0A,$40,$A8
            .byte $A8,$01,$9C,$0C,$9C,$0A,$A8,$BD
            .byte $01,$9C,$BE,$0D,$9C,$BD,$01,$9C
            .byte $BD,$BE,$0F,$9C,$01,$9C,$BE,$0A
            .byte $A8,$A8,$01,$9A,$0C,$9C,$0A,$A8
            .byte $BD,$01,$9A,$BE,$F8,$0A,$A8,$A8
            .byte $01,$9C,$0C,$9C,$0A,$A8,$BD,$01
            .byte $9C,$BE,$0D,$9C,$BD,$01,$9C,$BD
            .byte $BE,$BD,$9C,$BE,$0A,$A8,$A8,$01
            .byte $9A,$0C,$9C,$0A,$A8,$BD,$01,$9A
            .byte $BE,$F8,$00,$11,$4E,$02,$A3,$15
            .byte $40,$90,$90,$90,$12,$A3,$BD,$15
            .byte $90,$90,$11,$A3,$BD,$15,$90,$90
            .byte $12,$A3,$BD,$15,$90,$90,$11,$A3
            .byte $BD,$15,$90,$90,$12,$A3,$BD,$15
            .byte $90,$90,$11,$A3,$BD,$15,$90,$90
            .byte $12,$A3,$BD,$15,$90,$90,$11,$A3
            .byte $BD,$15,$90,$90,$12,$A3,$BD,$15
            .byte $90,$90,$11,$A3,$BD,$15,$90,$90
            .byte $12,$A3,$BD,$15,$90,$90,$11,$A3
            .byte $BD,$15,$90,$90,$12,$A3,$BD,$15
            .byte $90,$90,$11,$A3,$BD,$15,$90,$90
            .byte $12,$A3,$BD,$15,$90,$90,$00,$0E
            .byte $40,$9A,$43,$00,$99,$97,$95,$90
            .byte $50,$F6,$8E,$BD,$43,$00,$92,$50
            .byte $43,$00,$95,$50,$43,$00,$9A,$50
            .byte $F8,$89,$BD,$43,$00,$8D,$50,$43
            .byte $00,$95,$50,$43,$00,$99,$50,$F8
            .byte $8E,$BD,$43,$00,$92,$50,$43,$00
            .byte $95,$50,$43,$00,$99,$50,$FE,$43
            .byte $00,$97,$50,$43,$00,$95,$50,$FE
            .byte $00
