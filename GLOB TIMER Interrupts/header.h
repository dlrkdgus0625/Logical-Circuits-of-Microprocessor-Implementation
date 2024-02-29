#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

#define LED_BASE *((uint32_t *) 0x41210000)


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

#define GTC_CR *((uint32_t *) 0xF8F00208)
#define GTC_ISR *((uint32_t *) 0xF8F0020C)
#define GTC_AI *((uint32_t *) 0xF8F00218)
#define GTC_COMP1 *((uint32_t *) 0xF8F00210)
#define GTC_COMP2 *((uint32_t *) 0xF8F00214)
#define GTC_DRX1 *((uint32_t *) 0xF8F00200)
#define GTC_DRX2 *((uint32_t *) 0xF8F00204)



//definitions for GIC configuration registers
#define ICCPMR	*((uint32_t *) 0xF8F00104)	//Priority mask reg
#define ICCICR	*((uint32_t *) 0xF8F00100)	//CPU interface control reg
#define ICDDCR	*((uint32_t *) 0xF8F01000)	//Distributor Control reg
#define ICDISER(n)	*(((uint32_t *) 0xF8F01100) + n )	//Int. set enable reg
#define ICDICER(n)	*(((uint32_t *) 0xF8F01180) + n )	//Int. Clear Enable reg
#define ICDIPR(n)	*(((uint32_t *) 0xF8F01400) + n )	//Int. Priority reg
#define ICDIPTR(n)	*(((uint32_t *) 0xF8F01800) + n )	//Int. Processor Targets reg
#define ICDICFR(n)	*(((uint32_t *) 0xF8F01C00) + n )	//Int. Configuration reg
#define ICCIAR *((uint32_t *) 0xF8F0010C)
#define ICCEOIR *((uint32_t *) 0xF8F00110)

//volatile int count;

//uarts
int res_ready();
int tx_ready();
char uart1_getchar();
void uart1_sendchar(char data[]);
void uart1_reset();
void uart1_setBaud(int a, int b);
void configure_uart1();


//interrupts
void disable_arm_interrupts(void);
void enable_arm_interrupts(void);
void configure_GIC(void);

//service interrupt - done
void service_uart1_int(void);

void enable_interrupt_GTC(void);
void disable_interrupt_GTC(void);
void enable_GTC(void);
void disable_GTC(void);
void clear_flag_GTC(void);
void service_GTC_int(void);
void configure_GTC(void);
void enable_AI(void);
void comp();

#endif
