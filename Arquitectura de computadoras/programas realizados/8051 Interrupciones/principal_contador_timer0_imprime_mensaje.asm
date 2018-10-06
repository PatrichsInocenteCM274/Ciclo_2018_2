display equ 11Bh
sdelay  equ 142h
setintvec equ 145h
print  equ 136h
delay  equ 118h
	org 8000h
;cabecera de habilitacion del timer 0
	Mov TMOD, #21h ;Modo 0 del timer 0
	mov a, #1 ; Timer 0 es la fuente de interrupción
	mov dptr, #IntTimer0 ; IntTimer0 es la dirección inicial del ISR
	lcall setintvec ;Posibilita tener el ISR en RAM
	Setb TR0 ; inicia el timer 0
	Setb ET0 ; habilita interrupción del timer 0
	Setb EA ; habilita interrupción global
;.............................................. 
;cuenta desde 0 a 8191
	mov TL0,#0h
	mov TH0,#0h
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
	mov A,#60
	lcall delay
	inc R2
	djnz R3,lazo
	sjmp repite
	
IntTimer0:
	push acc
	lcall print
	db 0dh,0ah, "hola a todos",0
	mov TL0,#0
	mov TH0,#0
	pop acc
	reti
	end	