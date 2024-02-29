#include "header.h"
#include <xil_exception.h>
#define UART1_INT_ID 82

void myhandler();

int main(void)
{
	//setup UART
	configure_uart1();

	//configure interrupt system below
	disable_arm_interrupts();
	Xil_ExceptionRegisterHandler(5, myhandler, NULL);
	configure_GIC();
	configure_uart1_interrupt();
	enable_arm_interrupts();

	for(;;);
}

void myhandler()
{
	uint32_t id;
	id = ICCIAR;


	if(id==UART1_INT_ID)
	{
		//service UART interrupt here
		service_uart1_int();
	}
	//inform GIC that this interrupt has ended
	ICCEOIR = id;

}
