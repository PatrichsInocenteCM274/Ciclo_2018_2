display equ 11Bh
sdelay  equ 142h
setintvec equ 145h
print  equ 136h
delay equ 118h
;Programando una interrupcion externa 1
;presionar el boton p3.3
	ORG 8000H
;cabecera de la interrupcion obligatorio
;.....................................
	clr IT1
	MOV A,#2
	MOV DPTR,#ISR1
	LCALL SETINTVEC
	SETB EX1
	SETB EA
;.......................................
;contador de 0 a 9
repite:
	mov R3,#10
	mov R2,#0
lazo:
	mov A,R2
	lcall display
	cpl A
	mov P1,A
	lcall sdelay
	inc R2
	djnz R3,lazo
	sjmp repite

ISR1:
	push acc
	lcall print
	db 0dh,0ah, "hola a todos",0
	mov A,#250
	lcall delay 
	pop acc
	reti	
	end
	
	