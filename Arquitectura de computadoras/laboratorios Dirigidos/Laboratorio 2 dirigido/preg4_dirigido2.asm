;Hacer un programa que encuentre 
;la serie de Fibonacci para n=6. 
;Los números de esta
;serie enviarlo al terminal. 
;Considerar la serie desde n=1.
;n=1  1
;n=2  1  1
;n=3  1  1  2
;n=4  1  1  2  3
;n=5  1  1  2  3  5
;n=6  1  1  2  3  5  8
sdelay  equ 142h
sndchr  equ 148h
display equ 11Bh
	org 8000h
	mov A,#1
	;lcall display
	;cpl A
	;mov P1,A
	mov A,#31h
	lcall sndchr
	lcall sdelay
	;mov A,#0
	;mov P1,A
	mov A,#2Ch
	lcall sndchr
	lcall sdelay
	mov A,#1
	;lcall display
	;cpl A
	;mov P1,A
	mov A,#31h
	lcall sndchr
	lcall sdelay
	mov A,#2Ch
	lcall sndchr
;A partir de aqui empieza el calculo
	mov R5,#1	; hace las veces de a
	mov R6,#1	; hace las veces de b
	mov R2,#3	; hace las veces de i
lazo:
	mov A,R5
	add A,R6	;add R5,R6(esta prohibido)
	mov R7,A	; hace las veces de c
	mov A,R6
	mov R5,A
	mov A,R7
	mov R6,A
	mov A,R7
	;lcall display
	;cpl A
	;mov P1,A
	;mov A,R7
	add A,#30h
	lcall sndchr
	lcall sdelay
	;mov P1,#0
	mov A,#2Ch
	lcall sndchr
	lcall sdelay
	inc R2
	mov A,R2
	cjne A,#7,lazo
	ljmp 2F0h
	end
