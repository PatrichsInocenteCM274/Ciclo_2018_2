;Hacer un programa que dado un número hexadecimal por ejemplo “45h” lo convierta
;en decimal almacenados en las posiciones de memoria 40h, 41h y 42h y los envíe al terminal serial.

sndchr  equ 148h
getbyt  equ 11Eh
print   equ 136h
	org 8000h
	lcall print
	db "Ingrese el valor a convertir:",0dh,0ah,0
	lcall getbyt
	;dmov A,#0ffh	;Coloco el número que quiero convertir a decimal en el acumulador A
	lcall n_a_decimal
	ljmp 2F0h
n_a_decimal:
	mov B,#100
	div AB	; divido A/B, donde A=45h y B=100
	mov 40h,A	; el cociente se guarda en A y este le paso a 40h
	mov A,B		; mover a A el resto(residuo) de la división anterior
	mov B,#10
	div AB		; Divido el resto entre 10
	mov 41h,A
	mov 42h,B
;A partir de aqui envio los digitos a pantalla(terminal)
	mov A,#20h
	lcall sndchr
	mov A,#20h
	lcall sndchr
	mov A,#3dh
	lcall sndchr
	mov A,#20h
	lcall sndchr
	mov A,#20h
	lcall sndchr
	mov A,40h
	add A,#30h	;Lo convierto a código ASCII
	lcall sndchr
	mov A,41h
	add A,#30h	;Lo convierto a código ASCII
	lcall sndchr
	mov A,42h
	add A,#30h
	lcall sndchr
	ret
	end