#include "header.h"

int main(void)
{
	configure_uart1();

	char buffer[3] = {0,0,0};

	uint32_t out1 = acc_gyro_read(0x8F);
	itoa(out1, buffer, 16);
	//buffer = acc_gyro_read(0x0F);
	uart1_sendchar('0');
	uart1_sendchar('x');
	for(int i = 0; i < 2; i++)
	{
		uart1_sendchar(buffer[i]);
	}
	uart1_sendchar('\n');


	//reset_SPI();
	uint32_t out2 = mag_read(0x8F);
	itoa(out2, buffer, 16);
	//buffer = mag_read(0x8F);
	uart1_sendchar('0');
	uart1_sendchar('x');
	for(int i = 0; i < 2; i++)
	{
		uart1_sendchar(buffer[i]);
	}
	uart1_sendchar('\n');

}
