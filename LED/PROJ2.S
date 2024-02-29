.text
.global main

@define constants, these can be used as symbols in your code
.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000

@the set and equ directives are equivalent and can be used interchangeably

main:
	ldr r1,=SW_DATA	@load switch address from constant
	ldr r2,=LED_CTL	@load LED address from constant
loop:
	ldr r0,[r1]	@load switch value *r1 ->r0
	//CINV [r0], [r0], <r0 = 1>
	mvn r0, r0
	str r0,[r2]	@store value to led register *r2 <-r0
	b loop		@go back to "loop"

.end
