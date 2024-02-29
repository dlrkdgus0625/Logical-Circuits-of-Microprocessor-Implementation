.text
.global main

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

	mov r0, #70
	bl uart1_putc

b .
