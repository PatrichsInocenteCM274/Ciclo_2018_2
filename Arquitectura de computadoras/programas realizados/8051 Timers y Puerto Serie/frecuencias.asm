;RECORDAR QUE SOLO EL MODO 2 ES CON CARGA DE AUTO-RECARGA AUTOMATICA!!
org 8000h
mov TMOD,#21h ;
 ; como un temporizador de 16 bits con recarga no automatica.
mov TH0,#1fh ;valor de recarga
mov TL0,#0h
setb TR0 ;inicia el timer 0
espera_desborde:
	mov TH0,#1fh ;valor de recarga
	mov TL0,#0h
	jnb TF0,$ 
	clr TF0
	mov TH0,#1fh ;valor de recarga
	mov TL0,#0h
	jnb TF0,$ 
	clr TF0
	mov TH0,#1fh ;valor de recarga
	mov TL0,#0h
	jnb TF0,$ 
	clr TF0
	mov TH0,#1fh ;valor de recarga
	mov TL0,#0h
	jnb TF0,$ 
	clr TF0
	cpl P1.0
	sjmp espera_desborde
end
