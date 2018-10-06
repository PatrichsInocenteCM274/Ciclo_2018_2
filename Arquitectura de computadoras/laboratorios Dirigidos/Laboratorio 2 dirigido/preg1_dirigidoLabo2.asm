;Hacer un programa que dado un número hexadecimal por ejemplo
; “45h” lo convierta a
;un número de 2 dígitos decimales almacenados en 40h y 41h y 
;los envíe al terminal
;serial.

	org 8000h
	mov A,#45h
	mov B,#10
	div AB
	mov 40h,A	;cociente
	mov 41h,B	;residuo
	ljmp 2f0h
	end