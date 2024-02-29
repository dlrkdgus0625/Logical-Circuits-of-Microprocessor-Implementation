#include "header.h"
#include <xil_exception.h>
#define GPIO_INT_ID 52

void myhandler();
int main()
{
	configure_buttons();
	configure_PS_MIO();
	init_GPIO_RGB();
	disable_arm_interrupts();
	Xil_ExceptionRegisterHandler(5, myhandler, NULL);
	configure_GIC_interrupt52();
	configure_button_interrupts();
	enable_arm_interrupts();


	for(;;);

}

void myhandler()
{
	uint32_t id;
	id = ICCIAR;
	if(id==GPIO_INT_ID)
	{
		service_GPIO_interrupt();
	}
	ICCEOIR = id;
}
