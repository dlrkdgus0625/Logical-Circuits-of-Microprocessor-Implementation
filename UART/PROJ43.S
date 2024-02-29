.text
.global main
.data
data_start:
		.byte 76, 101, 101, 0

.extern uart1_init
.extern uart1_set_baud
//.extern uart1_putc

.equ BG115200, 124
.equ BD115200, 6

main:
	bl uart1_init


	@load parameters to baud
	ldr r0, =BG115200
	ldr r1, =BD115200
	bl uart1_set_baud

	ldr r7, =data_start
	ldr r8, =(data_start+3)

	loop:
		ldrb r3, [r7],#1
		mov r0, r3
		bl uart1_putc
		cmp r7, r8
	bne loop

b .
