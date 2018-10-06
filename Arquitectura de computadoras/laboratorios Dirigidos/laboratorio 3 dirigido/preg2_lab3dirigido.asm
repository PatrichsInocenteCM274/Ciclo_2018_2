;Hacer un programa para el TMC51 que al presionar el botón conectado al pin P3.2
;interrumpa al TMC51 y en ese momento envié por el puerto serie dos cadenas: “curso:
;Arquitectura de Computadores” y en otra fila “Prof.: Martín Cruz”. El programa principal
;es un contador de 0 a F mostrado en el display de 7 segmentos.
sdelay  equ 142h
prthex  equ 13Fh
sndchr  equ 148h
setintvec equ 145h
print   equ 136h
display equ 11Bh
	org 8000h
	setb IT0; fijamos la interrupcion externa sensible en el flanco de
		; bajada.
	mov A,#0
	mov dptr,#ISR0
	lcall setintvec
	setb EX0
	setb EA
	setb P3.2
repite:
	mov R3,#0
	mov R5,#16
lazo:
	mov A,R3
	lcall prthex
	mov A,#0dh
	lcall sndchr
	mov A,R3
	lcall display
	cpl A
	mov P1,A
	lcall sdelay
	inc R3
	djnz R5,lazo
	sjmp repite
ISR0:
	push acc
	lcall print
	db 0dh,0ah,"Arquitectura de Computadores"
	db 0dh,0ah,"Prof.: Martin Cruz",0dh,0ah,0
	pop acc
	reti
	end