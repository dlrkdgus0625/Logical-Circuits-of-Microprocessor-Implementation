#include "PROJ46.h"

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

void uart1_sendstr(char buffer[])
{
	int ready = 1;
	while(ready == 1)
	{
		ready = tx_ready();
	}

	uint32_t *u_data;
	u_data = (uint32_t*)UART1_DATA;
	*u_data = buffer;
}

int uart1_getln(char buffer[], int max)
{
	int i;
	for(i = 0; i < max; i++)
	{
		buffer[i] = uart1_getchar();
		//uart1_sendstr(buffer[i]);

		if(buffer[i] == '\r' || i == max)
		{
			break;
		}
	}
	return i;
}
