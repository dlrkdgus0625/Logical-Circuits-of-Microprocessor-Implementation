
.text
.global main
.global DISPLAY_NUM
.global DISPLAY_REAL
//.global loop

.set SW_DATA, 0x41220000
.set BTN_DATA, 0x41200000

.set SEG_CTL, 0x43c10000
.set SEG_DATA, 0x43C10004
.set SEG_DP, 0x43C10014

.set R_DIG, 0x2F
.set E_DIG, 6
.set A_DIG, 8
.set L_DIG, 0x47

.extern DISPLAY_NUM
.extern DISPLAY_REAL
//.extern loop

main:
ldr r11,=0xF
ldr r12,=0x80808080
ldr r5,=BTN_DATA
ldr r6,=SW_DATA

/*
ldr r2,=SW_DATA
ldr r3,[r2]
and r3, r3, r11
ldr r6,=SW_DATA
*/
ldr r7, [r5]
and r7, r7, r11

ldr r10,[r6]
and r10, r10, r11

ldr r9,[r6]
lsr r9, r9, #4
and r9, r9, r11

ldr r8,[r6]
lsr r8, r8, #8
and r8, r8, r11

bl DISPLAY_REAL
b main



DISPLAY_NUM:
ldr r11,=0xF
mov r10,#8
mov r2, #1
ldr r1,=SEG_CTL
str r2, [r1]
ldr r5,=SEG_DATA


mov r0, #0

for_loop:
mov r0, #1
mov r1, #4
add r0, r0, #1
and r3, r3, r11
mul r4, r0, r10
lsl r3, r3, r4
orr r0, r0,r3
lsr r3, r3, #4
cmp r0, r1
ble for_loop
orr r0, r0, r12
str r0,[r5]
bx lr

DISPLAY_REAL:
mov r0, #0
mov r2, #1
ldr r1,=SEG_CTL
str r2,[r1]
ldr r3,=SEG_DATA
/*
ldr r7,=R_DIG
ldr r8,=E_DIG
ldr r9,=A_DIG
ldr r10,=L_DIG*/
LSL r7, r7, #24
lsl r8, r8, #16
lsl r9, r9, #8
orr r0, r0, r7
orr r0, r0, r8
orr r0, r0, r9
orr r0, r0, r10
orr r0, r0, r12
str r0,[r3]
bx lr

.end



/*
@Declare functions as global
@This makes the labels acccessible in other functions
.text
.global main
.global enable_disp_hex
.global disable_disp
.global clear_disp
.global set_disp


.equ SEG_CTL,	0x43c10000
.equ SEG_DATA,	0x43c10004
.set SW_DATA, 0x41220000
.set BTN_DATA, 0x41200000

@enables the 7-seg display in hex mode
enable_disp_hex:
	ldr r1,=SEG_CTL
	mov r0,#1
	str r0,[r1]
	bx lr

@disables the 7-seg display
disable_disp:
	ldr r1,=SEG_CTL
	mov r0,#1
	str r0,[r1]
	bx lr

@clears the 7-seg display
clear_disp:
	ldr r1,=SEG_DATA
	mov r0,#0
	str r0,[r1]
	bx lr

@set the SW_DATA to the value 7-seg display
set_disp:
	ldr r1,=SEG_DATA
	ldr r2,=SW_DATA
	ldr r3,[r2]
	mov r0, r3
	str r0,[r1]
	bx lr

.extern enable_disp_hex
.extern	clear_disp
.extern set_disp

@program to enable, then clear display
@then sit in infinite loop
main:
	bl enable_disp_hex
	bl set_disp
	bl clear_disp

	b .

*/
