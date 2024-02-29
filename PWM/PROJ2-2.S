.text
.global main


.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000

main:
	/*
	bl led0_on
	bl led0_off
	bl led0_toggle
	bl led0_toggle
    b main
    */


blinky_loop:
	bl led0_toggle
	ldr r11, =SW_DATA
	ldr r0, [r11]
	LSL r0, r0, #20
	bl soft_delay
	b blinky_loop

soft_delay:
	subs r0, r0, #1
	bne soft_delay
	bx lr

led0_on:
	ldr r1, =LED_CTL
	ldr r0, [r1]	@get current value
	orr r0,r0,#1	@set the first bit (don't affect other bits)
	str r0, [r1]	@write back to LED_DATA
	bx lr


led0_off:
	ldr r1, =LED_CTL
	ldr r0, [r1]
	mov r3, #1
	mvn r3, r3
	and r0, r3,r0
	str r0, [r1]
	bx lr

led0_toggle:
	ldr r1, =LED_CTL
	ldr r0, [r1]
	EOR r0, r0, #1
	str r0, [r1]
	bx lr
