#include "header.h"


void configure_uart1()
{
	uart1_reset();

	uint32_t* data1;
	data1 = (uint32_t*)UART1_MR;
	*data1 = 0b00100000;

	uint32_t* data2;
	data2 = (uint32_t*)UART1_CR;
	*data2 = 0b00010100;
	uart1_setBaud(124, 6);
}

void uart1_reset()
{
	int i = 0;
	uint32_t digit = 0b11;

	uint32_t* data;
	data = (uint32_t*)UART1_CR;
	*data = digit;

	while(i == 0)
	{
		digit = *data;
		digit &= 0b11;
		if(digit == 0b0)
		{
			i = 1;
		}
	}
}

void uart1_setBaud(int a, int b)
{
	uint32_t* data1;
	data1 = (uint32_t*)UART1_UBG;

	uint32_t* data2;
	data2 = (uint32_t*)UART1_UBD;

	*data1 = a;
	*data2 = b;

}

void disable_arm_interrupts(void)
{
	uint32_t cpsr_val =0;

	asm("mrs %0, cpsr\n" : "=r" (cpsr_val) );	//get current cpsr

	//cpsr_val &= ~(0xFF);	//clear lower 8 bits
	cpsr_val |= 0x80;	//set all bits but the 'T' bit


	asm("msr cpsr, %0\n" : : "r" (cpsr_val));	//writeback modified value

	return;
}
void enable_arm_interrupts(void)
{
	uint32_t cpsr_val =0;

	asm("mrs %0, cpsr\n" : "=r" (cpsr_val) );	//get current cpsr value

	//cpsr_val &= ~(0xFF);	//clear lower 8 bits
	cpsr_val &= ~0x80;	//set all bits but 'T' and 'I' bit


	asm("msr cpsr, %0\n" : : "r" (cpsr_val));	//writeback modified value

	return;
}

//configure_GIC mini funcs

//disables the GIC distributor
void disable_gic_dist() { (ICDDCR = 0); };

//enables the GIC distributor
void enable_gic_dist() { (ICDDCR = 1); };

//Drive IRQ from the GIC
void disable_IRQ_passthrough() { (ICCICR =0x3); };

//sets the priority mask to the passed value 'priority'
void set_gic_pmr(uint32_t priority) { ICCPMR = (priority & 0xFF); };

//disables interrupt ID 52
void disable_interrupt82(void)
{
	ICDIPTR(20) &= ~(0x3 << 16); //remove processors from interrupt
	ICDICER(2) |= (0x1 << 18); //disable interrupts from GPIO module
}

//enables interrupt 52
void enable_interrupt82()
{
	ICDIPTR(20) |= (0x1 << 16); //set bit 1 of ICDIPTR13 (enable for cpu0)
	ICDISER(2) |= (0x1 << 18);
}

//sets the interrupt priority of 52 to ‘priority_val’
void set_interrupt82_priority(uint8_t priority_val)
{
	ICDIPR(20) &= ~(0xFF<<16); //clear priority bits for interrupt 52
	ICDIPR(20) |= ((priority_val) & 0xF8) << 16; //set top 5 bits based on passed value
}

//sets interrupt sensitivity of interrupt52 to ‘sens’
void set_interrupt82_sensitivity(uint8_t sens)
{
	ICDICFR(5) &= ~0x30;
	ICDICFR(5) |= (sens&0x3	)<<4;
}

void configure_GIC(void)
{

	//disable and configure GIC
	disable_gic_dist(); //disable GIC interrupt generation
	disable_IRQ_passthrough();	//drive IRQ from GIC

	set_gic_pmr(0xFF); //set priority mask

	//disable and configure interrupt 52
	disable_interrupt82();
	set_interrupt82_priority(0xA0); //set 52’s priority to 160
	set_interrupt82_sensitivity(1); //set to high level

	enable_interrupt82();	//re-enable interrupt52

	enable_gic_dist();		//re-enable distributor
}

void set_uart1_rx_trigger(uint32_t n)
{
	/*
	uint32_t* data;
	data = (uint32_t*)UART1_RXTG;
	*data = n;
	*data */
	UART1_RXTG = n;
}
void unmask_uart1_rxtg_int(void)
{
	/*
	uint32_t* data;
	data = (uint32_t*)UART1_IER;
	*data =1;
	*data */
	UART1_IER = 1;
}

void mask_uart1_rxtg_int(void)
{
	/*
	uint32_t* data;
	data = (uint32_t*)UART1_IDR;
	*data =1;
	*/
	UART1_IDR = 1;

}
void enable_uart1_byte_rx_int(void)
{
	set_uart1_rx_trigger(1);
	unmask_uart1_rxtg_int();
}
void configure_uart1_interrupt(void)
{
	mask_uart1_rxtg_int();
	enable_uart1_byte_rx_int();
}
void clear_uart1_flags()
{
	UART1_ISR = UART1_ISR;
}

int tx_ready()
{
	int ready;

	uint32_t* data;
	uint32_t temp;
	data = (uint32_t*)UART1_SR;

	temp = *data;
	temp &= 0b10000;


	if(temp == 0b0)
	{
		ready = 0;
	}
	else
		ready = 1;

	return ready;
}

int res_ready()
{
	int ready;
	uint32_t* data;
	uint32_t temp;
	data = (uint32_t*)UART1_SR;

	temp = *data;

	temp &= 0b10;

	if(temp == 0b0)
	{
		ready = 0;
	}
	else
		ready = 1;

	return ready;
}
void service_uart1_int(void)
{
	char dummy;

	//read until FIFO is empty

	dummy = uart1_getchar(); //place in dummy character
	uart1_sendchar(dummy);
	//uart1_sendchar()
	clear_uart1_flags();	//clear flags
}

char uart1_getchar()
{
	int ready = 1;
	while(ready == 1)
	{
		ready = res_ready();
	}

	char* data;
	data = (char*)UART1_DATA;

	char temp;
	temp = *data;

	return temp;
}

void uart1_sendchar(char data)
{
	int ready = 1;

	while(ready == 1)
	{
		ready = tx_ready();
	}

	uint32_t* u_data;
	u_data = (uint32_t*)UART1_DATA;
	*u_data = data;
}
