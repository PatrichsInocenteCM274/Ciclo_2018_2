;Hacer un programa que utilizando dos botones conectados al pin P3.2 y P3.3 interrumpa
;al TMC51 y en ese momento envíe al puerto serie mensajes desde donde ha sido
;interrumpido. El programa principal es hacer un led parpadeante.
setintvec equ 145h
delay   equ 118h
print   equ 136h
	org 8000h
	;Habilita la interrupción externa 0
	clr IT0; fijamos la interrupcion externa sensible en el nivel bajo.
	mov A,#0
	mov dptr,#ISR0
	lcall setintvec
	setb EX0
	setb P3.2
	;Habilita la interrupción externa 1
	clr IT1; fijamos la interrupcion externa sensible en el nivel bajo.
	mov A,#2
	mov dptr,#ISR1
	lcall setintvec
	setb EX1
	setb EA
	setb P3.3
repite:
	setb P1.0
	mov A,#200
	lcall delay
	clr P1.0
	mov A,#200
	lcall delay
	sjmp repite
ISR0:
	clr EX0
	push acc
	mov A,#250
	lcall delay
	lcall print
	db 0dh,0ah,"Se interrumpe desde P3.2",0
	pop acc
	setb EX0
	reti
ISR1:
	clr EX1
	push acc
	mov A,#250
	lcall delay
	lcall print
	db 0dh,0ah,"Se interrumpe desde P3.3",0
	pop acc
	setb EX1
	reti
	end
	