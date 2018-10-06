;Encontrar el valor más grande del 
;siguiente listado de números: 3, 2, 9, 5, 4, 7, 6, 8, 0, 1,4. 
;Mostrar este valor en el display y enviarlo al terminal vía el puerto serie. 
sndchr  equ 148h
display equ 11Bh
	org 8000h
	mov R4,#0;Hace las veces de largest
	mov R2,#0; R2 hace de contador
	mov R5,#11;Es la cantidad de números en el listado
lazo:
	mov A,R2
	lcall extraer_numero
	mov 30h,A
	subb A,R4	;A<--A - R4, Si A>R4, Carry(C)=0
	jnc cambio
regresa:
	inc R2
	djnz R5,lazo
	sjmp mostrar
cambio:
	mov R4,30h
	sjmp regresa
mostrar:
	mov A,R4
	add A,#30h
	lcall sndchr
	;mov A,R4
	;lcall display
	;cpl A
	;mov P1,A
	ljmp 2F0h
	
extraer_numero:
	inc A
	movc A,@A+PC
	ret
	db 3, 2, 1, 5, 4, 7, 6, 8, 0, 1,4
	end