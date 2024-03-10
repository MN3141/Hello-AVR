.cseg

;init stack
ldi r18,high(RAMEND)
out SPH, r18
ldi r18,low(RAMEND)
out SPL, r18
;----------

.def n=r16
.def temp=r17

var1: 
.db 4,0; Padding-ul care trb sa nu avem probleme cand scoatem date din memorie

rez:
.db 0,0

start:
	ldi zl,low(2*var1)
	ldi zh,high(2*var1)
	
	lpm n,z
	call factorial 
	rjmp start

factorial:
	mov r17,n
loop:
	dec r17
	breq end
	muls n,r17
	mov n,r0
	jmp loop
end:
	ret