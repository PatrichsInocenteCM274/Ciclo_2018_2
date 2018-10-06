display equ 11Bh

	org 8000h
	mov TMOD,#20h
	mov TH0,#0
	mov TL0,#0
repite:
	mov R5,#10
	mov R2,#9
lazo:
	mov A,R2
	lcall display
	cpl A
	mov P1,A
	lcall segundo
	dec R2
	djnz R5,lazo
	sjmp repite
	
	
segundo:
	setb TR0
	mov R3,#113
loop:
	jnb TF0,$
	clr TF0
	djnz R3,loop
	clr TR0
	ret
	end

	