;Hacer un programa para el TMC51 que al presionar el bot�n conectado al pin P3.2
;interrumpa al TMC51 y en ese momento envi� por el puerto serie dos cadenas: �curso:
;Arquitectura de Computadores� y en otra fila �Prof.: Mart�n Cruz�. El programa principal
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
	mov dptr,#ISR0	;Muevo al registro DPTR una direcci�n de 16 bits
	lcall setintvec
	setb EX0
	setb EA
	setb P3.2
repite:
	mov R3,#0
	mov R5,#16	;R5 es mi contador
lazo:
	mov A,R3
	lcall prthex	;muestra el digito en el terminal
	mov A,#0dh	;retorno de carro
	lcall sndchr
	mov A,R3
	lcall display	;codigo para el display
	cpl A		;invierte los bits
	mov P1,A	;envio al puerto P1
	lcall sdelay	;tiempo de un segundo
	inc R3
	djnz R5,lazo
	sjmp repite
ISR0:
	push acc	;Salva el valor del acumulador en la pila de la memoria
	lcall print
	db 0dh,0ah,"Arquitectura de Computadores"
	db 0dh,0ah,"Prof.: Martin Cruz",0dh,0ah,0
	pop acc		;Retorno el valor de la pila al acumulador
	reti
	end