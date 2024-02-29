#include "header.h"
//#include "main.c"



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
void disable_interrupt27(void)
{
	ICDIPTR(6) &= ~(0x3 << 24); //remove processors from interrupt
	ICDICER(0) |= (0x1 << 27); //disable interrupts from GPIO module
}

//enables interrupt 52
void enable_interrupt27()
{
	ICDIPTR(6) |= (0x1 << 24); //set bit 1 of ICDIPTR13 (enable for cpu0)
	ICDISER(0) |= (0x1 << 27);
}

//sets the interrupt priority of 52 to 몆riority_val�
void set_interrupt27_priority(uint8_t priority_val)
{
	ICDIPR(6) &= ~(0xFF<<24); //clear priority bits for interrupt 52
	ICDIPR(6) |= ((priority_val) & 0xF8) << 24; //set top 5 bits based on passed value
}

//sets interrupt sensitivity of interrupt52 to 몊ens�
void set_interrupt27_sensitivity(uint8_t sens)
{
	ICDICFR(1) &= ~(0x3<11);
	ICDICFR(1) |= (sens&0x3)<<11;
}

void configure_GIC(void)
{

	//disable and configure GIC
	disable_gic_dist(); //disable GIC interrupt generation
	disable_IRQ_passthrough();	//drive IRQ from GIC

	set_gic_pmr(0xFF); //set priority mask

	//disable and configure interrupt 52
	disable_interrupt27();
	set_interrupt27_priority(0xA0); //set 52뭩 priority to 160
	set_interrupt27_sensitivity(1); //set to high level

	enable_interrupt27();	//re-enable interrupt52

	enable_gic_dist();		//re-enable distributor
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

void uart1_sendchar(char data[])
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

void enable_interrupt_GTC()
{
	GTC_ISR = 0x1;
}

void disable_interrupt_GTC()
{
	GTC_CR = ~0x4;
}
void configure_GIC_v2()
{
	ICDIPTR(6) = 0x0;
	ICDICER(0) = 0x08000000;
	ICDDCR = 0x0;
	ICDIPR(6) = 0x90000000;
	ICDIPTR(6) = 0x01000000;
	ICDICFR(1) = 0xFFFFFFFF;
	ICDISER(0) = 0x08000000;
	ICCPMR = 0xFFFFFFFF;
	ICCICR = 0x1;
	ICDDCR = 0x1;

}
void enable_GTC()
{
	//GTC_CR = 0x15;
	GTC_CR = 0x30F;


}
void disable_GTC()
{
	GTC_CR = 0x0;
}
void clear_flag_GTC()
{
	GTC_ISR = 0x1;
}
void comp()
{

	GTC_COMP1 = 133333330;
	//GTC_COMP1 = 0x13DE4355;
	//GTC_COMP1 = 0xB2FE307B;
	//GTC_CR = 0x2;
}
void configure_GTC()
{
	//disable_interrupt_GTC();
	disable_GTC();
	enable_interrupt_GTC();
	comp();
	enable_GTC();

}

void configure_GTC_interrupts()
{
	disable_interrupt_GTC();

}
