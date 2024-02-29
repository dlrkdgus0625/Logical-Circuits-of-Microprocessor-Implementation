.text
.global main
.global DISPLAY_REAL

.set SW_DATA, 0x41220000
.set BTN_DATA, 0x41200000

.set SEG_CTL, 0x43c10000
.set SEG_DATA, 0x43C10004
.set SEG_DP, 0x43C10014

.extern DISPLAY_REAL

main:
ldr r11,=0xF
ldr r12,=0x80808080
ldr r5,=BTN_DATA
ldr r6,=SW_DATA

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

DISPLAY_REAL:
mov r0, #0
mov r2, #1
ldr r1,=SEG_CTL
str r2,[r1]
ldr r3,=SEG_DATA
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
