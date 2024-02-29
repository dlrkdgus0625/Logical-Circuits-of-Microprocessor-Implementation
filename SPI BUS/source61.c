#include "header.h"

uint32_t acc_gyro_read(uint32_t address)
{
	configure_SPI_SS0();
	SPI_CR &= ~(0xF << 10);
	SPI_TXD = address;
	SPI_TXD = 0x0;

	SPI_CR |= 0x1<<16;

	//uint32_t* data1;
	//uint32_t* data2;
	//uint32_t temp = SPI_SR;
	SPI_RX_THRES = 2;
	while((SPI_SR & 0x10) == 0);

	uint32_t data = SPI_RXD;
	data = SPI_RXD;
	//data = SPI_RXD;
	//data2 = SPI_RXD;


	return data;
}

uint32_t mag_read(uint32_t address)
{
	configure_SPI_SS1();
	SPI_CR &= ~(0xE << 10);
	SPI_TXD = address;
	SPI_TXD = 0x0;
	//SPI_TXD = 0x1

	SPI_CR |= 0x1<<16;
	SPI_RX_THRES = 2;
	while((SPI_SR & 0x10) == 0);

	uint32_t data = SPI_RXD;
	data = SPI_RXD;

	return data;
}

/*
SPI in master mode
SPI mode 3 (CPOL=1 and CPHA=1)
Divide clock to 5.2MHz (BAUD_RATE=4)
Slave select 0000 (slave 0)
No external decoder (PERI_SEL=0)
Manual chip-select (MANUAL_CS=1)
Manual start (MANUAL_START_EN=1)
 */
void configure_SPI_SS0(void)
{
	reset_SPI();
	SPI_CR = 0x2FC27;//  10 1 1 1111 0 0 00  100  1 1 1

	SPI_ER = 0x1;

}

/*
SPI in master mode
SPI mode 3 (CPOL=1 and CPHA=1)
Divide clock to 5.2MHz (BAUD_RATE=4)
Slave select 0001 (slave 1)
No external decoder (PERI_SEL=0)
Manual chip-select (MANUAL_CS=1)
Manual start (MANUAL_START_EN=1)
 */
void configure_SPI_SS1(void)
{
	reset_SPI();
	//SPI_CR = 0xC427;//1 0 1 0001 0 0 00 100 1 1 1
	SPI_CR = 0x2FC27;
	SPI_ER = 0x1;
}

void reset_SPI(void)
{
	int i=0; //i for delay
	SLCR_UNLOCK = UNLOCK_KEY;	//unlock SLCRs
	SLCR_SPI_RST = 0xF;		//assert SPI reset
	for(i=0;i<1000;i++);		//make sure Reset occurs
	SLCR_SPI_RST = 0;		//deassert
	SLCR_LOCK = LOCK_KEY;		//relock SLCRs
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
