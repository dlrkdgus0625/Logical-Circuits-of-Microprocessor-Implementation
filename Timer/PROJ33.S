.text
.global main

//.set max, 99999999999999

.set SW_DATA, 0x41220000
.set BTN_DATA, 0x41200000

.set SEG_CTL, 0x43c10000
.set SEG_DATA, 0x43C10004
.set SEG_DP, 0x43C10014
main:
//ldr r9, =max
mov r11, sp
ldr r12,=0x80808080
ldr r10,=BTN_DATA

mov r0, #0
push {r0}
push {r0}
push {r0}
push {r0}

bl DISPLAY_REAL

reset:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

mov r0, #0
mov r1, #0
mov r2, #0
mov r3, #0

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
b loop

loop:
ldr r8,[r10]
cmp r8, #2
bleq reset

cmp r8, #1
bleq timer
bl DISPLAY_REAL
b loop

check:
ldr r8,[r10]
//and r8, #1
cmp r8, #1
beq check
bx lr

check1:
ldr r8,[r10]
//and r8, #1
cmp r8, #2
beq check1
bx lr

check4:
ldr r8,[r10]
//and r8, #1
cmp r8, #4
beq check4
bx lr

timer:
bl check
cmp r8, #2
bleq stop
bl check1
cmp r8, #8
bleq reset


bl T_INC
bl DISPLAY_REAL
movw r9,#0
movt r9,#0x1000
bl delay

b timer

delay:
subs r9,r9,#1
ldr r8, [r10]
cmp r8, #2
bleq stop
bne delay
bx lr

T_INC:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

cmp r0, #9
addne r0, #1
bleq T_INC1

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

T_INC1:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

mov r0, #0
cmp r1, #9
addne r1, #1
bleq T_INC2

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

T_INC2:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

cmp r0, #9
moveq r0, #0

cmp r1, #9
moveq r1, #0

cmp r2, #9
addne r2, #1
bleq T_INC3

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

T_INC3:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

add r3, #1
cmp r3, #10
bleq main

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

DISPLAY_REAL:

ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

mov r4, #0

mov r7, #1
ldr r6,=SEG_CTL
str r7,[r6]
ldr r5,=SEG_DATA
LSL r3, r3, #24
lsl r2, r2, #16
lsl r1, r1, #8
orr r4, r4, r3
orr r4, r4, r2
orr r4, r4, r1
orr r4, r4, r0
orr r4, r4, r12
str r4,[r5]
bx lr

done:
b done

stop:
ldr r8, [r10]
cmp r8, #4
bleq INC
bl check4

bl DISPLAY_REAL
cmp r8, #1
beq loop
cmp r8, #8
beq reset
b stop

INC:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

cmp r0, #9
addne r0, #1
bleq INC1

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

INC1:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

mov r0, #0
cmp r1, #9
addne r1, #1
bleq INC2

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

INC2:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

cmp r0, #9
moveq r0, #0

cmp r1, #9
moveq r1, #0

cmp r2, #9
addne r2, #1
bleq INC3

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

INC3:
push {fp, lr}
ldr r0,[fp,#-4]
ldr r1,[fp,#-8]
ldr r2,[fp,#-12]
ldr r3,[fp,#-16]

add r3, #1
cmp r3, #10
bleq main

str r0,[fp,#-4]
str r1,[fp,#-8]
str r2,[fp,#-12]
str r3,[fp,#-16]
pop {fp, lr}
bx lr

