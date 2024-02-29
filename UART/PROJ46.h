#ifndef PROJ46_H
#define PROJ46_H

#include <stdint.h>

#define UART1_SR 0xE000102c
#define UART1_CR 0xE0001000
#define UART1_MR 0xE0001004
#define UART1_DATA 0xE0001030
#define UART1_UBG 0xE0001018
#define UART1_UBD 0xE0001034

int tx_ready();

int res_ready();

void uart1_reset();

void uart1_setBaud(int a, int b);

void configure_uart1();

char uart1_getchar();
void uart1_sendchar(char data);
void uart1_sendstr(char buffer[]);
int uart1_getln(char buffer[], int max);

#endif
