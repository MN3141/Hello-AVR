;Codul citeste de pe A0 o valoare analogica intre 0v si 5v apoi o afiseaza pe pinii digitali 
;D2-D11. Am pus led-uri pentru afisaj.
;
.include "m328pdef.inc"

.cseg
.org $0000
rjmp RESET
.ORG $002A
rjmp ADC_COMPLETE

.def gr = r16
.def gr1 = r17
.def gr2 = r18

RESET:
	ldi gr,0xFC
	out DDRD,gr

	ldi gr,0xF
	out DDRB,gr

	;DIDR0--------------------------
	ldi gr,(1<<ADC0D)
	sts DIDR0,gr; Set A0 as analog input
	;DDIR0--------------------------

	;ADMUX--------------------------
	ldi gr,(1<<REFS0)
	sts ADMUX,gr; use the internal 5V source and use mux0 for A0
	;ADMUX--------------------------

	;ADCSRA-------------------------
	ldi gr,(1<<ADEN)|(0b111<<ADPS0)|(1<<ADIE)|(1<<ADSC)
	sts ADCSRA,gr; enable adc, interrupts, use prescaler 1024 and start conversion
	;ADCSRA-------------------------
	
    sei; set global interrupts
	
mainLoop:
    rjmp mainLoop

ADC_COMPLETE:

	lds gr,ADCL
	ldi gr1,4
	mul gr,gr1
	mov gr,r0
	out PORTD,gr
    ;Load ADCL value onto Port d (D2-D7)

	mov gr,r1
	lds gr1,ADCH
	ldi gr2,4
	mul gr1,gr2
	mov gr1,r0
	or gr,gr1
	OUT PORTB,gr
	;Load the rest of the ADCL and ADCH onto port b (D8-D11)

	lds gr,ADCSRA
	ldi gr1,1<<ADSC
	or gr,gr1
	sts ADCSRA,gr

	reti

