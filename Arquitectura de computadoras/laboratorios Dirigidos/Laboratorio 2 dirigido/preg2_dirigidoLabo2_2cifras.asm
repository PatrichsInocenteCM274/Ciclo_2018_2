;Encontrar el valor m�s grande del siguiente listado de n�meros: 
;3, 2, 9, 5, 4, 7, 6, 8, 0, 1,4
;Mostrar este valor en el display y enviarlo al 
;terminal v�a el puerto serie.
sndchr  equ 148h

	org 8000h
	mov R5,#0; R5 hace las veces de largest
	mov R7,#11
	mov R2,#0
loop:
	mov A,R2
	clr C
	lcall selecciona_numero
	mov 30h,A	;A es current
	subb A,R5;A<--(A-R5)
	jc continua
	mov R5,30h
continua:
	inc R2
	djnz R7,loop
	mov A,R5
	;lcall display
	;cpl A
	;mov P1,A
	mov A,#0dh
	lcall sndchr
	mov A,#0Ah
	lcall sndchr
	mov 40h,R5
	;ljmp 2F0h
	mov A,R5
	lcall digitos
	ljmp 2f0h
digitos:
	mov B,#10
	div AB
	add A,#30h
	lcall sndchr
	mov A,B
	add A,#30h
	lcall sndchr
	ret	
selecciona_numero:
	inc A
	movc A,@A+PC
	ret
	db 30, 20, 0, 55, 41, 98, 65, 89, 0, 12,43
	end