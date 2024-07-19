.include "m328pdef.inc"
;Codul genereaza un delay de ~1 secunda pe altenranta high cat si pe cea low. 
;Ca iesire am folosit pinul 13, ledul de pe placa, pentru a afisa efectul delay-ului.
.cseg
.org $0000
rjmp RESET
.ORG $0016
rjmp TCA

.def n = r19

RESET:
	ldi r16,(1<<5)
	out DDRB,r16  ; Setez portul b ca output (Pinul digital 13)

	eor r16,r16
	out PORTB5,r16 ; Initializez valoarea de inceput cu 0 logic

	ldi r16,0b1101 
	sts TCCR1B,r16 ; Setez timer-ul sa functioneze in CTC mode cu un prescaler de 1024
	
	ldi r16,$3d
	ldi r17,$09
	sts OCR1AH,r16
	sts OCR1AL,r17 ; Incarc valoarea $3d09 in OCR1A pentru un delay de ~1 secunda

	ldi r16,2	
	sts TIMSK1, r16 ; Pornesc flagul genera o intrerupere atunci cand TCN1 == OCR1A.
	
    sei

mainLoop:
    rjmp mainLoop

TCA:
	ldi r16,(1<<5)
	eor r0,r16
	out PORTB,r0

	reti

