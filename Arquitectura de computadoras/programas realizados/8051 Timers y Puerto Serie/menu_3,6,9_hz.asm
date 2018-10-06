getbyt equ 11Eh 
print equ 136h 
 
org 8000h 
	mov tmod,#21h 
	lcall print 
	db "Seleccione Frecuencia",0dh,0ah 
	db "00) 3 Hz",0dh,0ah 
	db "01) 6 Hz",0dh,0ah 
	db "02) 9 Hz",0dh,0ah 
	db "03) SALIR",0dh,0ah,0; 
	lcall getbyt 
	cjne A,#03h,proceso 
	ljmp 2f0h 
 
proceso:  
	mov 60h,A  
	lcall selecciona_valor_menos_s   
	MOV 61H,A  
	mov A,60h  
	lcall selecciona_valor_mas_s  
	mov 62h,A  
	mov A,60h  
	lcall repeticiones  
	mov 64h,A  
	setb tr0 

repite:  
	mov R5,64h 
lazo:  
	jnb tf0,$  
	clr tf0  
	mov th0,62h         
	mov tl0,61h         
	djnz R5,lazo         
	cpl p1.0         
	sjmp repite 
 
 
selecciona_valor_menos_s: 
	inc A 
	movc A,@A+PC 
	ret 
	db 00h,00h,00h 
 
selecciona_valor_mas_s: 
	inc A 
	movc A,@A+PC 
	ret 
	db 38h,6Ah,0CEh 
 
repeticiones: 
	inc A 
	movc A,@A+PC 
	ret 
	db 3h,2h,4h 

end 