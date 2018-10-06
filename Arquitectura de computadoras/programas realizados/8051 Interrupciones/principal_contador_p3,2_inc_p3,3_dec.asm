;Hacer un programa que utilizando dos botones conectados al pin P3.2 y P3.3 interrumpa
;al TMC51 y en ese momento envíe al puerto serie mensajes desde donde ha sido
;interrumpido. El programa principal es hacer un led parpadeante.
setintvec equ 145h
delay   equ 118h
print   equ 136h
prthex  equ 13Fh
sndchr	equ 148h
sdelay 	equ 142h
	org 8000h
	clr IT0; fijamos la interrupcion externa sensible en el nivel bajo.
	mov A,#0
	mov dptr,#ISR0
	lcall setintvec
	setb EX0
	setb P3.2
	clr IT1; fijamos la interrupcion externa sensible en el nivel bajo.
	mov A,#2
	mov dptr,#ISR1
	lcall setintvec
	setb EX1
	setb EA
	setb P3.3
repite:
	mov R3,#0
	mov R5,#10
lazo:
	mov A,R3
	lcall prthex
	mov A,#0dh
	lcall sndchr
	;mov A,R3
	;lcall display
	;cpl A
	;mov P1,A
	lcall sdelay
	inc R3
	djnz R5,lazo
	sjmp repite
ISR0:
	clr EX0
	push acc
	mov A,#250
	lcall delay
	inc R3
	pop acc
	setb EX0
	reti
ISR1:
	clr EX1
	push acc
	mov A,#250
	lcall delay
	dec R3
	pop acc
	setb EX1
	reti
	end
	