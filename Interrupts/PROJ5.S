.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000


main:
	ldr r1,=SW_DATA

	ldr r2,=LED_CTL

loop:
	ldr r0,[r1]	@load switch value, (*r1) ->r0


	cmp r0,#4	@compare switch value with 4
	blt led_light	@branch to 'led_light' if sw val is less than 4

	cmp r0,#8
	blt led_light2

	cmp r0,#12
	blt led_light3

	cmp r0,#16
	blt led_light4

led_dim:
	mov r0,#0
	str r0,[r2]
	b loop		@go back to start of loop
led_light:
	mov r0,#1 //light up led 1
	str r0,[r2]
	b loop
led_light2:
	mov r0,#2 //light up led 2
	str r0,[r2]
	b loop
led_light3:
	mov r0,#4 //light up led 2
	str r0,[r2]
	b loop
led_light4:
	mov r0,#8 //light up led 2
	str r0,[r2]
	b loop





.end
