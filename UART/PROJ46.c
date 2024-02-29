#include "PROJ46.h"

char cha;
char str_data[128];

int main()
{
	configure_uart1();

	/*
	cha = uart1_getchar();
	uart1_sendchar(cha);
	*/

	/*
	for(int i = 0; i < 128; i++)
	{
		str_data[i] = uart1_getchar();
		uart1_sendstr(str_data[i]);
	}
	*/


	int num = uart1_getln(str_data, 128);

}

