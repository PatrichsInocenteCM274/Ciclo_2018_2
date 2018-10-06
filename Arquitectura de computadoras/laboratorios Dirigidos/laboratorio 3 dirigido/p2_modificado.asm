;Hacer un programa para el TMC51 que al presionar el botón conectado al pin P3.2
;interrumpa al TMC51 y en ese momento envié por el puerto serie dos cadenas: “curso:
;Arquitectura de Computadores” y en otra fila “Prof.: Martín Cruz”. El programa principal
;es un contador de 0 a F mostrado en el display de 7 segmentos.
sdelay  equ 142h
prthex  equ 13Fh
sndchr  equ 148h
setintvec equ 145h
print   equ 136h
display equ 11Bh
break     equ  010ch  ; a, (lee acumulador)
inkey     equ  012ah  ; a
crlf      equ  115h 
endloop   equ  2f0h
getbyt    equ  11eh
	org 8000h
	setb IT0; fijamos la interrupcion externa sensible en el flanco de
		; bajada.
	mov A,#0
	mov dptr,#ISR0	;Muevo al registro DPTR una dirección de 16 bits
	lcall setintvec
	setb EX0
	setb EA
	setb P3.2
repite:
	mov R3,#0
	mov R5,#16	;R5 es mi contador
lazo:
	mov A,R3
	lcall prthex	;muestra el digito en el terminal
	mov A,#0dh	;retorno de carro
	lcall sndchr
	mov A,R3
	lcall display	;codigo para el display
	cpl A		;invierte los bits
	mov P1,A	;envio al puerto P1
	lcall sdelay	;tiempo de un segundo
	inc R3
	djnz R5,lazo
	sjmp repite
;Rutina de interrupcion
ISR0:
	push acc	;Salva el valor del acumulador en la pila de la memoria
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
 	;lcall crlf	;retorno de carro y un salto de linea
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
 	lcall break     ; termina programa si CTL-C
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
	pop acc		;Retorno el valor de la pila al acumulador
	reti
f2hz:
	jnb TF0,$	;esto se repite mientras TF0 es cero y no hay desbordamiento
				
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