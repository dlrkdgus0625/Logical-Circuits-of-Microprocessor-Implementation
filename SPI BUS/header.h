#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#include <stdlib.h>

#define UART1_IER	*((uint32_t *) 0xE0001008)
#define UART1_IDR	*((uint32_t *) 0xE000100C)
#define UART1_ISR	*((uint32_t *) 0xE0001014)
#define UART1_RXTG	*((uint32_t *) 0xE0001020)
#define UART1_SR 0xE000102c
#define UART1_CR 0xE0001000
#define UART1_MR 0xE0001004
#define UART1_UBG 0xE0001018
#define UART1_UBD 0xE0001034
#define UART1_DATA 0xE0001030

//SLCR addresses for SPI reset
#define SLCR_LOCK		*( (uint32_t *) 0xF8000004)
#define SLCR_UNLOCK		*( (uint32_t *) 0xF8000008)
#define SLCR_SPI_RST 	*( (uint32_t *) 0xF800021C)

//SLCR lock and unlock keys
#define UNLOCK_KEY	0xDF0D
#define LOCK_KEY	0x767B

#define SPI_CR *( (uint32_t *) 0xE0006000)
#define SPI_SR *( (uint32_t *) 0xE0006004)
#define SPI_IER *( (uint32_t *) 0xE0006008)
#define SPI_IDR *( (uint32_t *) 0xE000600C)
#define SPI_IMR *( (uint32_t *) 0xE0006010)
#define SPI_ER *( (uint32_t *) 0xE0006014)
#define SPI_DR *( (uint32_t *) 0xE0006018)
#define SPI_TXD *( (uint32_t *) 0xE000601C)
#define SPI_RXD *( (uint32_t *) 0xE0006020)
#define SPI_SICR *( (uint32_t *) 0xE0006024)
#define SPI_TXWR *( (uint32_t *) 0xE0006028)
#define SPI_RX_THRES *( (uint32_t *) 0xE000602C)
#define SPI_MOD_ID *( (uint32_t *) 0xE00060FC)



void configure_SPI_SS0(void);
void configure_SPI_SS1(void);
void reset_SPI(void);
uint32_t acc_gyro_read(uint32_t address);
uint32_t mag_read(uint32_t address);


//uart
int res_ready();
int tx_ready();
char uart1_getchar();
void uart1_sendchar(char data);
void uart1_reset();
void uart1_setBaud(int a, int b);
void configure_uart1();


#endif
