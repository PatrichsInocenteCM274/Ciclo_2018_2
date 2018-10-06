;Hacer un programa para el TMC51 para seleccionar una frecuencia de 
;2hz, 12hz, 22hz y 32h de tal manera que enviando un “01” por el 
;puerto serie seleccione una frecuencia de 2
;hertz, enviando un “02” seleccione 12 hertz, 
;enviando “03” seleccione 22 hertz y
;enviando “04” seleccione 32 hertz. La señal saldrá por el pin P1.0 
;del Puerto 1.Sugerencia: Usar el timer 0 en modo 0.

break     equ  010ch  ; a, (lee acumulador)
inkey     equ  012ah  ; a
crlf      equ  115h 
endloop   equ  2f0h
print     equ  136h
getbyt    equ  11eh
          org       8000h    ;El programa empieza en esta direcci¢n de
                             ;de memoria
ejemplo:  
          lcall     print   ;PRINT es una subrutina grabado en el FlashRom
                            ;se usa para imprimir mensajes en el terminal de la PC.
          db        0dh,0ah," M E N U "
          db        0dh,0ah,"=========",0dh,0ah
          db        0dh,0ah," HECHO POR: C. Martin Cruz Salazar",0dh,0ah
          db        0dh,0ah," 01) FRECUENCIA: 2 HZ"
          db        0dh,0ah," 02) FRECUENCIA: 12 HZ"         
          db        0dh,0ah," 03) FRECUENCIA: 22 HZ",0dh,0ah
          db        0dh,0ah," Seleccione numero hexadecimal: ",0
          lcall     getbyt
          cjne      a,#1h,salir                  
          sjmp      frec2hz
salir:
          sjmp      otrafrecuencia

frec2hz:
	  lcall     print
          db       0dh,0ah,"FRECUENCIA SELECCIONADA: 2Hz"
          db       0dh,0ah,"==============================",0dh,0ah,0h
          mov TMOD,#20h		;configura el timer 0 en modo 0
				; como un temporizador de 13 bits
	  mov TH0,#0
	  mov TL0,#0		;
	  setb TR0		;inicia el timer 0
	  mov R7,#28		;contador
loop:
	  lcall f2hz
	  lcall inkey         ; 
 	  lcall break         ; termina programa si CTL-C
	  sjmp loop
	
otrafrecuencia:
	cjne      a,#2h,salir1                  
  	sjmp      frec12hz
salir1:
	sjmp otrafrecuencia1
frec12hz:
	lcall     print
          db       0dh,0ah,"FRECUENCIA SELECCIONADA: 12Hz"
          db       0dh,0ah,"==============================",0dh,0ah,0h
	mov TMOD,#20h	;configura el timer 0 en modo 0
			;como un temporizador de 13 bits
	mov TH0,#0
	mov TL0,#0	
	setb TR0	;inicia el timer 0
	mov R7,#5	;contador
loop1:
	lcall f12hz
	lcall inkey         ; 
 	lcall break         ; termina programa si CTL-C
	sjmp loop1
otrafrecuencia1:
	cjne      a,#3h,salir2                  
  	sjmp      frec22hz
salir2:
	ljmp 2F0h
frec22hz:
	lcall     print
          db       0dh,0ah,"FRECUENCIA SELECCIONADA: 22Hz"
          db       0dh,0ah,"==============================",0dh,0ah,0h
	mov TMOD,#20h		;configura el timer 0 en modo 0
				; como un temporizador de 13 bits
	mov TH0,#0
	mov TL0,#0		
	setb TR0		;inicia el timer 0
	mov R7,#3		;contador
loop2:
	lcall f22hz
	lcall inkey         ; 
 	lcall break         ; termina programa si CTL-C
	sjmp loop2


f2hz:
	jnb TF0,$	;esto se repite mientras TF0 es cero y no hay
			;desbordamiento
				
	clr TF0		;este flag de desbordamiento se pone a 1 por hardware,
			;este flag debe ser puesto a 0 por software
	djnz R7,f2hz		
	mov R7,#28
	cpl P1.0		
	ret
f12hz:
	jnb TF0,$	;esto se repite mientras TF0 es cero y no hay
			;desbordamiento
	clr TF0		;este flag de desbordamiento se pone a 1 por hardware,
			;este flag debe ser puesto a 0 por software
	djnz R7,f12hz	;
	mov R7,#5
	cpl P1.0	
	ret
	
f22hz:
	jnb TF0,$	;esto se repite mientras TF0 es cero y no hay
	clr TF0		;este flag de desbordamiento se pone a 1 por hardware,
			;este flag debe ser puesto a 0 por software
	djnz R7,f22hz	;
	mov R7,#3
	cpl P1.0	
	clr TF0
	ret
	end