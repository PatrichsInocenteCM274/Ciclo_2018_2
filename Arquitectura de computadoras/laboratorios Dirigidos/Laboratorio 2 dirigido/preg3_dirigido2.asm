;Hacer un programa que calcule el factorial de “5”. 
;Mostrar este resultado en las
;posiciones de memoria 31h, 32h y 33h como dígitos decimales. 
;Este resultado enviarlo al terminal.
;n=5!,  1x2x3x4x5=120
sndchr  equ 148h
prthex  equ 13Fh
	org 8000h
	mov R5,#1; hace las veces de F
	mov R6,#1; hace las veces de i
lazo:
	mov A,R5
	mov B,R6
	mul AB
	mov R5,A
	inc R6
	mov A,R6
	cjne A,#6,lazo
	mov A,R5
	lcall n_a_decimal
	mov A,40h
	mov 31h,A
	mov A,41h
	mov 32h,A
	mov A,42h
	mov 33h,A
	ljmp 2F0h
n_a_decimal:
	mov B,#100
	div AB
	mov 40h,A
	mov A,B
	mov B,#10
	div AB
	mov 41h,A
	mov 42h,B
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
	