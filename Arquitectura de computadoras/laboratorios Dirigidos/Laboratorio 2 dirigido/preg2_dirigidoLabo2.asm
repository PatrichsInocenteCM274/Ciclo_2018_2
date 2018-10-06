;Encontrar el valor más grande del siguiente listado de números: 
;3, 2, 9, 5, 4, 7, 6, 8, 0, 1,4
;Mostrar este valor en el display y enviarlo al 
;terminal vía el puerto serie.
sndchr  equ 148h
display equ 11Bh
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
	lcall display
	cpl A
	mov P1,A
	mov A,#0dh
	lcall sndchr
	mov A,#0Ah
	lcall sndchr
	mov A,R5
	add A,#30h
	lcall sndchr
	ljmp 2f0h	
selecciona_numero:
	inc A
	movc A,@A+PC
	ret
	db 3, 2, 0, 5, 4, 7, 6, 8, 0, 1,4
	end