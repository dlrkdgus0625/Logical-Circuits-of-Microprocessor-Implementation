.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000


main:
	ldr r1,=SW_DATA

	ldr r2,=LED_CTL
	ldr r5, = 4095

loop:
	ldr r0,[r1]	@load switch value, (*r1) ->r0
	////MOV r3,r1 @save all switch value

	cmp r0,r5
	beq led_light2

	cmp r0,#19	@compare switch value with 19
	beq led_light	@branch to 'led_light' if sw val is equal to 19
led_dim:
	mov r0,#0
	str r0,[r2]
	b loop		@go back to start of loop
led_light:
	mov r0,#1
	str r0,[r2]
	b loop
led_light2:
	mov r0,#2
	str r0,[r2]
	b loop


.end
