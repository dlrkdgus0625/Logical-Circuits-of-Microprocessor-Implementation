.text
.global main

.set SW_DATA, 0x41220000

.set PWM_EN, 0x43C00000
.set PWM_P, 0x43C00004
.set PWM_W, 0x43C00008

main:
ldr r9, =16

loop:

ldr r1, =PWM_EN
ldr r2, =PWM_P
ldr r3, =PWM_W


mov r8, #0
bl SW_VALUE
bl PWM_OFF
mov r8, #1
bl SW_VALUE
bl PWM_OFF
mov r8, #2
bl SW_VALUE
bl PWM_OFF
mov r8, #3
bl SW_VALUE
bl PWM_OFF
mov r8, #4
bl SW_VALUE
bl PWM_OFF
mov r8, #5
bl SW_VALUE

bl PWM_OFF

bl GET_SW
//mov r7, #1
bl SW_VALUE
bl PWM_ON

b loop

GET_SW:
ldr r10, =SW_DATA
ldr r7, [r10]
lsl r7, r7, #24
lsr r7, r7, #24


ldr r8, [r10]
lsr r8, r8, #9
AND r8, #7
bx lr

SW_VALUE:
mul r8, r8, r9 //multiply 16 * sw data
add r4, r1, r8 //add to the PWM_EN value
add r5, r2, r8 //period
add r6, r3, r8 //width
bx lr


PWM_ON:
mov r0, #1
mov r11, #255 //binary number 11111111 -> 255 in decimal
//mov r12, #1
//subs r6, r11, r7
str r0, [r4]
str r11, [r5]
str r7, [r6]
bx lr

PWM_OFF:
mov r0, #0
mov r11, #255 //binary number 11111111 -> 255 in decimal
//mov r12, #1
str r0, [r4]
str r0, [r5]
str r0, [r6]
bx lr

.end
