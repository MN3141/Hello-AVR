.include "m328pdef.inc"
.cseg
.org $0000
rjmp RESET

RESET:
	ldi r16,(1<<2)
	out DDRD,r16  
	ldi r17,(1<<2)
mainLoop:
	eor r16,r17
	out PORTD,r16
	nop
    rjmp mainLoop
