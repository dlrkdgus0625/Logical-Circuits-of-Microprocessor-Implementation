.text
.global main
.data
.comm dat_arr, 64

.extern uart1_init
.extern uart1_set_baud

.equ BG115200, 124
.equ BD115200, 6

main:
bl uart1_init
ldr r0, =BG115200
ldr r1, =BD115200
bl uart1_set_baud

ldr r6, =dat_arr
mov r2, #15

loop:
	bl uart1_readc
	//strb r3, [r6],#1
	strb r3, [r6],#1
	mov r0, r3
	bl uart1_putc
	//subs r2, r2, #1
	b loop

//strb r2, [r6], #1

b .
