.text

.equ UART1_CR, 0xE0001000
.equ UART1_MR, 0xE0001004

.equ UART1_UBG, 0xE0001018
.equ UART1_UBD, 0xE0001034

.equ UART1_SR, 0xE000102c
.equ UART1_DATA, 0xE0001030
.equ UART1_FIFO, 0xE0001030

.global uart1_init
.global uart1_set_baud
.global uart1_putc
.global uart1_readc
.global uart1_readflush

//return 1 in r0 if ready, 0 other wise
uart1_tx_ready:
	ldr r1, =UART1_SR
	ldr r0, [r1]
	ands r0, #0b10000
	movne r0, #0
	moveq r0, #1
	bx lr

uart1_RES_ready:
	ldr r1, =UART1_SR
	ldr r0, [r1]
	ands r0, #0b10
	//lsr r0, #1
	movne r0, #0
	moveq r0, #1
	bx lr

uart1_readc:
	push { lr }
	mov r4, r0
	RES_poll:
		bl uart1_RES_ready
		cmp r0, #1
		bne RES_poll

	get_data:
		ldr r1, =UART1_DATA
		ldr r0,[r1]
		//ldr r9,[r1]
		pop { lr }
	bx lr

uart1_readflush:
	ldr r1, =UART1_DATA
	ldr r9, [r1]
	bx lr


@transmit character in r0 over uart
uart1_putc:

	push {r4, lr}
	mov r4, r0
	@wait for room in tx FIFO
	tx_poll:
		bl uart1_tx_ready
		cmp r0, #1
		bne tx_poll
	@write to tx FIFO
	ldr r1, =UART1_DATA
	str r4,[r1]
	pop {r4, lr}
bx lr

uart1_init:

	push {lr}
	bl uart1_reset

	ldr r1, =UART1_MR
	mov r0, #0b00100000
	str r0, [r1]

	ldr r1, =UART1_CR
	mov r0, #0b00010100
	str r0, [r1]
	pop {lr}

	bx lr

uart1_reset:
	ldr r1, =UART1_CR
	mov r0, #0b11
	str r0, [r1]

	reset_loop:
		ldr r0,[r1]
		ands r0, #0b11
		bne reset_loop

	bx lr

uart1_set_baud:
	ldr r2, =UART1_UBG
	str r0, [r2]

	ldr r2, =UART1_UBD
	str r1, [r2]

bx lr
