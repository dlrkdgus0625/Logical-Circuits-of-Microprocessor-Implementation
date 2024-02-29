#include "header.h"

void service_GPIO_interrupt(void)
{

	int flags = get_GPIO_int_status(BT4_BANK, BT4_MASK|BT5_MASK);

	if( (flags&BT4_MASK) && !(flags&BT5_MASK) )
	{
		//only BT4 flags set, BT5 flag not set
		en_GPIO_RGB_output();
		write_GPIO_RGB(0x7);
		clear_btn4_flag();
		clear_btn5_flag();

	}

	if( !(flags&BT4_MASK) && (flags&BT5_MASK) )
	{
		//only BT5 flags set, BT4 flag not set
		dis_GPIO_RGB_output();
		clear_btn4_flag();
		clear_btn5_flag();

	}
}

void disable_arm_interrupts()
{
	uint32_t cpsr_val =0;

	asm("mrs %0, cpsr\n" : "=r" (cpsr_val) );	//get current cpsr

	//cpsr_val &= ~(0xFF);	//clear lower 8 bits
	cpsr_val |= 0x80;	//set all bits but the 'T' bit


	asm("msr cpsr, %0\n" : : "r" (cpsr_val));	//writeback modified value

	return;
}

void enable_arm_interrupts()
{
	uint32_t cpsr_val =0;

	asm("mrs %0, cpsr\n" : "=r" (cpsr_val) );	//get current cpsr value

	//cpsr_val &= ~(0xFF);	//clear lower 8 bits
	cpsr_val &= ~0x80;	//set all bits but 'T' and 'I' bit


	asm("msr cpsr, %0\n" : : "r" (cpsr_val));	//writeback modified value

	return;
}
void configure_button_interrupts(void)
{
	disable_GPIO_interrupts(BT4_BANK, BT4_MASK | BT5_MASK);
	//set buttons 4 and 5 to edge sensitive
	set_GPIO_int_edge_sens(BT4_BANK, BT4_MASK | BT5_MASK);

	//set button 4 to rising edge interrupts
	set_GPIO_int_pol_high(BT4_BANK, BT4_MASK);

	//set button 5 to falling edge interrupts
	set_GPIO_int_pol_high(BT5_BANK, BT5_MASK);

	//set so only use the defined edge
	clear_GPIO_int_any_edge(BT4_BANK, BT4_MASK | BT5_MASK);

	//clear interrupt flags for button 4 and 5
	clear_GPIO_int_status(BT4_BANK, BT4_MASK | BT5_MASK);

	enable_GPIO_interrupts(BT4_BANK, BT4_MASK|BT5_MASK);


}
void disable_gic_dist() { (ICDDCR = 0); }

void enable_gic_dist() { (ICDDCR = 1); }

//Drive IRQ from the GIC
void disable_IRQ_passthrough() { (ICCICR =0x3); }

//sets the priority mask to the passed value 'priority'
void set_gic_pmr(uint32_t priority) { ICCPMR = (priority & 0xFF); }

void disable_GPIO_interrupts(int bank, uint32_t mask)
{
	GPIO_INT_DIS(bank) = mask;
}
void enable_GPIO_interrupts(int bank, uint32_t mask)
{
	GPIO_INT_EN(bank) = mask;
}
void set_GPIO_int_level_sens(int bank, uint32_t mask)
{
	GPIO_INT_TYPE(bank) &= ~mask;
}
void set_GPIO_int_edge_sens(int bank, uint32_t mask)
{
	GPIO_INT_TYPE(bank) |= mask;
}
void set_GPIO_int_pol_high(int bank, uint32_t mask)
{
	GPIO_INT_POL(bank) |= mask;
}
void set_GPIO_int_pol_low(int bank, uint32_t mask)
{
	GPIO_INT_POL(bank) &= ~mask;
}
void set_GPIO_int_any_edge(int bank, uint32_t mask)
{
	GPIO_INT_ANY(bank) |= mask;
}
void clear_GPIO_int_any_edge(int bank, uint32_t mask)
{
	GPIO_INT_ANY(bank) &= ~mask;
}
void clear_GPIO_int_status(int bank, uint32_t mask)
{
	GPIO_INT_STAT(bank) = mask;
}
uint32_t get_GPIO_int_status(int bank, uint32_t mask)
{
	return GPIO_INT_STAT(bank) & mask;
}

void disable_interrupt52(void)
{
	ICDIPTR(13) &= ~0x3; //remove processors from interrupt
	ICDICER(1) = 0x00100000; //disable interrupts from GPIO module
}

void set_interrupt52_sensitivity(uint8_t sens)
{
	ICDICFR(3) &= ~0x300;
	ICDICFR(3) |= (sens&0x3)<<8;
}

void set_interrupt52_priority(uint8_t priority_val)
{
	ICDIPR(13) &= ~0xFF; //clear priority bits for interrupt 52
	ICDIPR(13) |= (priority_val) & 0xF8; //set top 5 bits based on passed value
}
void enable_interrupt52()
{
	ICDIPTR(13) |= 1; //set bit 1 of ICDIPTR13 (enable for cpu0)
	ICDISER(1) = 0x00100000;
}

void configure_GIC_interrupt52(void)
{

	//disable and configure GIC
	disable_gic_dist(); //disable GIC interrupt generation
	disable_IRQ_passthrough();	//drive IRQ from GIC

	set_gic_pmr(0xFF); //set priority mask

	//disable and configure interrupt 52
	disable_interrupt52();
	set_interrupt52_priority(0xA0); //set 52’s priority to 160
	set_interrupt52_sensitivity(1); //set to high level

	enable_interrupt52();	//reenable interrupt52

	enable_gic_dist();		//reenable distributor

}
// Configure MIO pins for the Blackboard's PS-connected buttons and LEDs
void configure_PS_MIO (void)
{
	SLCR_UNLOCK = UNLOCK_KEY;	//unlock SLCRs
	MIO_50 = 0x0600; // BTN4 is LVCMOS33
	MIO_51 = 0x0600; // BTN5 is LVCMOS33
	MIO_16 = 0x1600; // RGB_LED_B is LVCMOS33 with disabled input buffer
	MIO_17 = 0x1600; // RGB_LED_R is LVCMOS33 with disabled input buffer
	MIO_18 = 0x1600; // RGB_LED_G is LVCMOS33 with disabled input buffer
	SLCR_LOCK = LOCK_KEY;	//relock SLCRs
}
void set_GPIO_RGB_output()
{
	GPIO_DIRM(0) = RGB_MASK ;
}
void set_GPIO_RGB_input()
{
	GPIO_DIRM(0) &= ~RGB_MASK ;
}
void en_GPIO_RGB_output()
{
	GPIO_OEN(0) |= RGB_MASK ;
}
void dis_GPIO_RGB_output()
{
	GPIO_OEN(0) &= ~RGB_MASK;
}
void write_GPIO_RGB(uint32_t val)
{
	val = (0x7&val)<<16;	//use only bottom 3 bits, and shift to place
	GPIO_DATA(0) = (GPIO_DATA(0)&~RGB_MASK) | val;	//change only RGB bits
}
void init_GPIO_RGB()
{
	dis_GPIO_RGB_output();
	set_GPIO_RGB_output();	//configure as output
	write_GPIO_RGB(0);	//clear value of RGBs
	en_GPIO_RGB_output();
}

void set_GPIO_output(int n, uint32_t mask)
{
	GPIO_DIRM(n) |= mask;
}

void set_GPIO_input(int n, uint32_t mask)
{
	GPIO_DIRM(n) &= ~mask;
}
int read_GPIO_input(int n, uint32_t mask)
{
	return (GPIO_DATA_RO(n) & mask);
}


void configure_buttons(void)
{
	set_GPIO_input(BT4_BANK, BT4_MASK);
	set_GPIO_input(BT5_BANK, BT5_MASK);
}
void configure_buttons_alt(void)
{
	set_GPIO_input(BT4_BANK, BT5_MASK | BT5_MASK);
}
int get_btn4_val(void)
{
	return ( read_GPIO_input(BT4_BANK, BT4_MASK) !=0 );
}
int get_btn5_val(void)
{
	return ( read_GPIO_input(BT5_BANK, BT5_MASK) !=0 );
}

int get_btn4_flag()
{
	return 0!=get_GPIO_int_status(BT4_BANK, BT4_MASK);
}

int get_btn5_flag()
{
	return 0!=get_GPIO_int_status(BT5_BANK, BT5_MASK);
}

void clear_btn4_flag()
{
	clear_GPIO_int_status(BT4_BANK, BT4_MASK);
}
void clear_btn5_flag()
{
	clear_GPIO_int_status(BT5_BANK, BT5_MASK);
}


void clear_bt4_flag_alt()
{
	clear_GPIO_int_status(BT4_BANK, BT4_MASK);
}

void clear_bt5_flag_alt()
{
	clear_GPIO_int_status(BT5_BANK, BT5_MASK);
}


