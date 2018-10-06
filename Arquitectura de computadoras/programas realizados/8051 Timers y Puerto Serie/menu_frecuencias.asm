
getbyt  equ 11Eh 
print   equ 136h  
 org 8000h
 clr 0CAh 
 clr 0C9h 
 mov 0C9h,#3 

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