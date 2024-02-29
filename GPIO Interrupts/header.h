#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

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


void service_GPIO_interrupt();
void disable_interrupt52(void);

void set_interrupt52_sensitivity(uint8_t sens);
void set_interrupt52_priority(uint8_t priority_val);
void enable_interrupt52();

void configure_GIC_interrupt52(void);

//interrupt mask readonly reg
#define GPIO_INT_MASK(n)	*(((uint32_t *) 0xE000A20C) + 16*(n))

//interrupt enable
#define GPIO_INT_EN(n)		*(((uint32_t *) 0xE000A210) + 16*(n))

//interrupt disable
#define GPIO_INT_DIS(n)		*(((uint32_t *) 0xE000A214) + 16*(n))

//interrupt status register
#define GPIO_INT_STAT(n)	*(((uint32_t *) 0xE000A218) + 16*(n))

//interrupt edge/level sensitivity register
#define GPIO_INT_TYPE(n)	*(((uint32_t *) 0xE000A21C) + 16*(n))

//interrupt polarity register
#define GPIO_INT_POL(n)		*(((uint32_t *) 0xE000A220) + 16*(n))

//interrupt any edge register
#define GPIO_INT_ANY(n)		*(((uint32_t *) 0xE000A224) + 16*(n))
#define BT4_MASK 0x40000
#define BT5_MASK 0x80000
//define the bank the buttons are in
#define BT4_BANK 1
#define BT5_BANK 1

// System Level Control Register Definitions
#define SLCR_LOCK	*((uint32_t *) 0xF8000004)
#define SLCR_UNLOCK	*((uint32_t *) 0xF8000008)
#define UNLOCK_KEY	0xDF0D
#define LOCK_KEY	0x767B

//  MIO pins register definitions
#define MIO_16		*((uint32_t *) 0xF8000740)
#define MIO_17		*((uint32_t *) 0xF8000744)
#define MIO_18		*((uint32_t *) 0xF8000748)
#define MIO_50		*((uint32_t *) 0xF80007C8)
#define MIO_51		*((uint32_t *) 0xF80007CC)

//output data register
#define GPIO_DATA(n)		*(((uint32_t*) 0xE000A040)+n)

//input data register
#define GPIO_DATA_RO(n) 	*(((uint32_t*) 0xE000A060)+n)

//direction register
#define GPIO_DIRM(n) 		*(((uint32_t*) 0xE000A204) + 16*n)

//output enable register
#define GPIO_OEN(n) 		*(((uint32_t*) 0xE000A208) + 16*n)

//RGB LED channels are bits 16-18, in bank 0
#define RGB_MASK 0x70000

//interrupt mask readonly reg
#define GPIO_INT_MASK(n)	*(((uint32_t *) 0xE000A20C) + 16*(n))
//interrupt enable
#define GPIO_INT_EN(n)		*(((uint32_t *) 0xE000A210) + 16*(n))
//interrupt disable
#define GPIO_INT_DIS(n)		*(((uint32_t *) 0xE000A214) + 16*(n))
//interrupt status register
#define GPIO_INT_STAT(n)	*(((uint32_t *) 0xE000A218) + 16*(n))
//interrupt edge/level sensitivity register
#define GPIO_INT_TYPE(n)	*(((uint32_t *) 0xE000A21C) + 16*(n))
//interrupt polarity register
#define GPIO_INT_POL(n)		*(((uint32_t *) 0xE000A220) + 16*(n))
//interrupt any edge register
#define GPIO_INT_ANY(n)		*(((uint32_t *) 0xE000A224) + 16*(n))

//btn4 is 18 in bank 1, btn5 is 19 in bank 1
//define bit masks for easy access in banks
#define BT4_MASK 0x40000
#define BT5_MASK 0x80000
//define the bank the buttons are in
#define BT4_BANK 1
#define BT5_BANK 1

void configure_button_interrupts(void);
void disable_GPIO_interrupts(int bank, uint32_t mask);
void enable_GPIO_interrupts(int bank, uint32_t mask);
void set_GPIO_int_level_sens(int bank, uint32_t mask);
void set_GPIO_int_edge_sens(int bank, uint32_t mask);
void set_GPIO_int_pol_high(int bank, uint32_t mask);
void set_GPIO_int_pol_low(int bank, uint32_t mask);
void set_GPIO_int_any_edge(int bank, uint32_t mask);
void clear_GPIO_int_any_edge(int bank, uint32_t mask);
void clear_GPIO_int_status(int bank, uint32_t mask);
uint32_t get_GPIO_int_status(int bank, uint32_t mask);

//
void disable_arm_interrupts();
void enable_arm_interrupts();
void configure_PS_MIO (void);
void set_GPIO_RGB_output(void);
void set_GPIO_RGB_input(void);
void en_GPIO_RGB_output(void);
void dis_GPIO_RGB_output(void);
void write_GPIO_RGB(uint32_t val);
void init_GPIO_RGB(void);

void set_GPIO_output(int n, uint32_t mask);
void set_GPIO_input(int n, uint32_t mask);
int read_GPIO_input(int n, uint32_t mask);

void configure_buttons(void);
void configure_buttons_alt(void);
int get_btn4_val(void);
int get_btn5_val(void);
int get_btn4_flag(void);
int get_btn5_flag(void);

void clear_btn4_flag(void);
void clear_btn5_flag(void);
void clear_bt4_flag_alt(void);
void clear_bt5_flag_alt(void);


#endif
