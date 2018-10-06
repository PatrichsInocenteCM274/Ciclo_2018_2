;Hacer un programa que calcule el factorial de “5”. 
;Mostrar este resultado en las
;posiciones de memoria 31h, 32h y 33h 
;como dígitos decimales. Este resultado enviarlo
;al terminal.
;1x2x3x4x5=120
sndchr  equ 148h
	org 8000h
	mov R2,#1	;hace las veces de F
	mov R3,#1	;hace las veces de i
	mov R5,#5	;hace las veces de n
loop:
	mov A,R2
	mov B,R3
	mul AB	;no existe mul R2, R3
	mov R2,A
	inc R3
	djnz R5,loop
;A partir de aqui se muestra en decimal el 
;número encontrado
	mov A,R2
	mov B,#100
	div AB
	mov 31h,A
	mov A,B
	mov B,#10
	div AB
	mov 32h,A
	mov 33h,B
	mov A,31h
	add A,#30h
	lcall sndchr
	mov A,32h
	add A,#30h
	lcall sndchr
	mov A,33h
	add A,#30h
	lcall sndchr
	ljmp 2f0h
	end