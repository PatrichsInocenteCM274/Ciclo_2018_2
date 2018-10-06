;Hacer un programa que genere una frecuencia de 15hertz en el 
;pin P1.0 del Puerto 1
;Se va usar el modo 1 del timer 0 (0-65535)
	org 8000h
	
	mov TMOD,#21h; selecciono el modo 2 del timer 1 y el modo 1 del
			;timer 0
	mov TH0,#88h
	mov TL0,#0h	;mov TL0,#0h
repite:
	setb TR0	;inicio la cuenta poniendo TR0 a 1
	jnb TF0,$	;Veo si se ha desbordado
	clr TF0
	cpl P1.0
	clr TR0		;Detengo el temporizador
	mov TH0,#88h
	mov TL0,#0h
	sjmp repite
	end