
setintvec equ 145h

org 8000h

Mov TMOD, #11h ;Modo 1 del timer 0
mov a, #1 ; Timer 0 es la fuente de interrupción
mov dptr, #IntTimer0 ; IntTimer0 es la dirección inicial del ISR
lcall setintvec ;Posibilita tener el ISR en RAM
mov Th0,#38h;
mov tl0,#0h;
Setb TR0 ; inicia el timer 0
Setb ET0 ; habilita interrupción del timer 0
Setb EA ; habilita interrupción global 
mov a, #3 ; Timer 0 es la fuente de interrupción
mov dptr, #IntTimer1 ; IntTimer0 es la dirección inicial del ISR
lcall setintvec ;Posibilita tener el ISR en RAM
mov Th1,#0A6h;
mov tl1,#00h;
Setb TR0 ; inicia el timer 0
Setb ET0 ; habilita interrupción del timer 0
Setb EA ; habilita interrupción global 

repite:
    cjne R4,#4,repite1
    cpl p1.1
    mov R4,#0
repite1:
    cjne R5,#1,repite
    cpl p1.3
    mov R5,#0
    sjmp repite


IntTimer0:
    clr TF0
    mov Th0,#38h;
    mov tl0,#00h;
    inc R4
    reti

IntTimer1:
    clr TF1
    mov Th1,#0A6h;
    mov tl1,#0h;
    inc R5
    reti
end