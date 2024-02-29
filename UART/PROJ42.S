.text
.global main

.extern uart1_init
.extern uart1_set_baud
//.extern uart1_putc
.extern uart1_readflush

.equ BG115200, 124
.equ BD115200, 6
.equ LED_CTL, 0x41210000

main:
bl uart1_init
@load parameters to baud
	ldr r0, =BG115200
	ldr r1, =BD115200
	bl uart1_set_baud
loop:
	//bl uart1_init

	bl uart1_readc
	//bl uart1_readflush
	//bl compare


//compare:
	cmp r3, #'a'
	bleq led0_toggle
	cmp r3, #'b'
	bleq led1_toggle
	cmp r3, #'c'
	bleq led2_toggle
	cmp r3, #'d'
	bleq led3_toggle
	b loop

led0_toggle:
	push {lr}
	mov r0, #48
	bl uart1_putc
	ldr r1, =LED_CTL
	ldr r0, [r1]
	EOR r0, r0, #1
	str r0, [r1]
	pop {lr}
	bx lr

led1_toggle:
push {lr}
	mov r0, #49
	bl uart1_putc
	ldr r1, =LED_CTL
	ldr r0, [r1]
	EOR r0, r0, #2
	str r0, [r1]
	pop {lr}
	bx lr

led2_toggle:
push {lr}
	mov r0, #50
	bl uart1_putc
	ldr r1, =LED_CTL
	ldr r0, [r1]
	EOR r0, r0, #4
	str r0, [r1]
pop {lr}
	bx lr

led3_toggle:
push {lr}
	mov r0, #51
	bl uart1_putc
	ldr r1, =LED_CTL
	ldr r0, [r1]
	EOR r0, r0, #8
	str r0, [r1]
pop {lr}
	bx lr

