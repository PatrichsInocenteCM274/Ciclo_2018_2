;Programa de menú de frecuencias con el timer2
;Autor: César Martín Cruz Salazar
;T2CON Address = 0C8H
;T2MOD Address = 0C9H
;TF2 EXF2 RCLK TCLK EXEN2 TR2 C/T2 CP/RL2
;C/T2 Timer or counter select for Timer 2. C/T2 = 0 for timer function.
;0C8H T2CON T2MOD RCAP2L RCAP2H TL2 TH2
getbyt equ 11Eh
print equ 136h
org 8000h
;Detiene el temporizador del timer2(clr TR2)
;clr TR2
clr 0CAh
; Configure Timer 2 as Clock Out
;CLR T2CON.1
clr 0C9h
;– – – – – – T2OE DCEN
;T2OE Timer 2 Output Enable bit
;DCEN When set, this bit allows Timer 2 to be configured as an up/down counter
mov 0C9h,#3
; Load Clock values [Crystal : 11.0592MHz]
lcall print
db "Seleccione Frecuencia",0dh,0ah
db "00) 42Hz",0dh,0ah
db "01) 100Hz",0dh,0ah
db "02) 500Hz",0dh,0ah
db "03) 1000Hz",0dh,0ah,0;
lcall getbyt
mov 60h,A
lcall selecciona_valor_menos_s; RECAP2L
MOV 61H,A
MOV 0CAh,A;0,0,66,33h
mov A,60h
lcall selecciona_valor_mas_s;RECAP2H
mov 62h,A
MOV 0CBh, A;0,94h,EAh,F5h
;Start Timer 2, señal sale por P1.0
;SETB TR2
setb 0CAh
ljmp 2F0h
selecciona_valor_menos_s:
inc A
movc A,@A+PC
ret
db 0,0,66h,33h
selecciona_valor_mas_s:
inc A
movc A,@A+PC
ret
db 0,94h,0EAh,0F5h
end