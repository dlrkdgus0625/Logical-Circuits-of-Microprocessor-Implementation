#include <stdint.h>

extern char uart1_readc();
extern void uart1_putc(char dat[]);
extern void uart1_init();
extern void uart1_set_baud(uint32_t d1, uint32_t d2);


char str_data[128];

int main ()
{


	uart1_init();
	uart1_set_baud(124, 6);

	for(int i=0; i < 128; i++)
	{
		str_data[i] = uart1_readc();
		uart1_putc(str_data[i]);

	}
}
