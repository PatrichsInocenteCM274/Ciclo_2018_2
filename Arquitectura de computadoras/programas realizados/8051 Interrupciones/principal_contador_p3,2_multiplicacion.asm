; Hacer un programa que utilizando un bot�n externo conectado al pin P3.2 interrumpa al
;TMC51 y en ese momento que multiplique dos n�meros. El programa principal es un
;contador de 0 a Fh que se env�a por el puerto serie.


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
	db 0dh,0ah,"Voy a multiplicar los numeros 4 y 5",0
	mov A,#4
	mov B,#5
	mul AB
	mov 30h,A
	lcall print
	db 0dh,0ah,"El resultado es: ",0dh,0ah,0
	mov A,30h
	mov B,#10
	div AB
	add A,#30h
	lcall sndchr
	mov A,B
	add A,#30h
	lcall sndchr
	lcall print
	db 0dh,0ah,0
	pop acc
	reti
	end