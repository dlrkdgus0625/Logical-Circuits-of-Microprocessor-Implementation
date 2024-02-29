#include "header.h"
#include <xil_exception.h>
#define GTC_INT_ID 27

void myhandler();
volatile int count;

int main(void)
{
	count = 0;
	//setup UART
	configure_uart1();
	disable_arm_interrupts();

	configure_GIC();
	//configure_GIC_v2();
	configure_GTC();
	Xil_ExceptionRegisterHandler(5, myhandler, NULL);
	enable_arm_interrupts();
	for(;;);
}

void myhandler(void)
{
	LED_BASE = 0x1;
	uint32_t id;
	id = ICCIAR;

	if(id==GTC_INT_ID)
	{
		//LED_BASE = 0x1;
		service_GTC_int();
	}
	ICCEOIR = id;
}

void service_GTC_int()
{
	//int count = (int)'a';
	// data = (uint32_t)GTC_AI;
	//data = count;
	char buffer [sizeof(count)*8+1];

	for(int i = 0; i < sizeof(count); i++)
	{
		buffer[i] = count+48;
	}
	//int size = sizeof(buffer) / sizeof(buffer[0]);
	//itoa(count, buffer, 10);
	uart1_sendchar(count);
	//printf(buffer);


	count++;
	clear_flag_GTC();
}
