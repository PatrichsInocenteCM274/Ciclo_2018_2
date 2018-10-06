sdelay 	equ 142h
sndchr 	equ 148h
display equ 11Bh
print	equ 136h
setintvec equ 145h
delay	equ 118h

	org 8000h
; cabecera de interrupcion automatica
	;mov 	TMOD, #20h		;modo 0 al timer 0, y al timer 1 en otro modo para que funcione la comunicacion serial
	mov 	TMOD, #21h		;modo 1 timer 0
	mov	A, #1			;el timer 0 es la fuente de interrupcion
	mov	dptr, #IntTimer0	;intimer0 es la direccion inicial del ISR
	lcall	setintvec		;posibilita tener el ISR en RAM
	setb	TR0			;inicia el timer 0
	setb	ET0			;habilita interrupcion del timer0
	setb	EA			;habilita interrupcion global
;-----------------------------------------------------
;cuenta desde 0 a 2^13-1 = 8191		a frecuencia de 1/12 la velocidad del reloj	
;en modo 1 timer 0 contara hasta 2^16-1 = 65531 
	mov	TL0, #0h
	mov	TH0, #0h	
	
	
	
fibo:	
	mov A,#1
	lcall sdelay
	mov A,#1
	lcall display
	cpl A
	mov P1,A	
	mov A,#31h
	lcall sndchr
	lcall sdelay	
	;mov A,#2ch	;coma
	mov A,#20h	;espacio en blanco
	lcall sndchr
	;A partir de aqui empieza el cálculo
	mov R5,#1 	;hace las veces de a
	mov R6,#1	;hace las veces de b
	mov R2,#3	;hace las veces de i

lazo:
	mov A,R5
	add A,R6	;add R5,R6(esta prohibido)
	mov R7,A	;;hace las veces de c
	mov A,R6
	mov R5,A
	mov A,R7
	mov R6,A
	mov A,R7
	lcall display
	cpl A
	mov P1,A
	mov A,R7
	add A,#30h
	lcall sndchr
	lcall sdelay
	mov P1,#0
	;mov A,#2ch	;coma
	mov A,#20h 	;espacio en blanco
	lcall sndchr
	lcall sdelay
	inc R2
	mov A,R2
	cjne A,#7,lazo
	sjmp fibo  ;para q se repita el programa
	;ljmp 2F0h
	
IntTimer0:
	push acc
	lcall	 print
	db 	0dh,0ah, "Hola amiwos :)",0
;decrem:
	
;conteo:
	mov	TL0, #0
	mov	TH0, #0
;	djnz	R7, conteo
;	djnz	R6, decrem
	pop	acc
	reti
		
	end
