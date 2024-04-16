#include"STD_types.h"
#include"BIT_math.h"
#include"SPI_Interface.h"
#include"SPI_Private.h"

static uint8 i=0;

static uint8 global_uint8datatotransmit=0;

static uint8 global_uint8flag=0;

static uint8* global_uint8datarecieved='/0';

void SPI_voidConfig (void)
{
	SPI->CR1 &= ~(0b111<<3);   // BR[2:0] = 000 = fPCLK/2, PCLK2 = 8MHz, SPI clk = 4MHz
	CLR_BIT(SPI->CR1,0);
    CLR_BIT(SPI->CR1,0); // CPOL=0, CPHA=0
	SPI->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex
	SPI->CR1 &= ~(1<<7);   // LSBFIRST = 0, MSB first
	SPI->CR1 |= (1<<2);  // MSTR=1, Master mode
	SPI->CR1 &= ~(1<<11);  // DFF=0, 8 bit data
	// software slave management must be selecetd, and then we can control the slave using any output pin
	SPI->CR1 |= (1<<9)| (1<<8);  // SSM = 1, SSI = 1
} 

void SPI_voidInterruptRXEnable(void)
{
	SPI->CR2 |= (1<<6);
}

void SPI_voidInterruptTXEnable(void)
{
	SPI->CR2 |= (1<<7);
}

void SPI_voidEnable (void)
{
	SPI->CR1 |= (1<<6);   // SPE=1, Peripheral enabled
}

void SPI_voidDisable (void)
{
	SPI->CR1 &= ~(1<<6);   // SPE=0, Peripheral Disabled
}

void SPI_voidTransmit (uint8* Copy_uint8DataBuffer, uint8 Copy_uint8Size)
{
	if(Copy_uint8Size!=1)
	{
		global_uint8flag=0;
		global_uint8datatotransmit=Copy_uint8DataBuffer[i];
		i++;
		SPI_voidEnable();
		while(i<Copy_uint8Size||global_uint8flag==1)
		{
			if(global_uint8flag==0)
			{
				continue;
			}
			else if(i>=Copy_uint8Size)
			{
				break;
			}
			else
			{
				global_uint8datatotransmit=Copy_uint8DataBuffer[i];
				global_uint8flag=0;
				i++;
			}
		}
	}
	else
	{
		global_uint8flag=0;
		global_uint8datatotransmit=*Copy_uint8DataBuffer;
		SPI_voidEnable();
	}
	
	while (global_uint8flag==0);
	if(READ_BIT(SPI->SR,0)==1)
	{
		(void)SPI->DR;
	}
	
}

void SPI_voidReceive (uint8* Copy_uint8DataBuffer, uint8 Copy_uint8Size)
{
	if (Copy_uint8Size!=1)
	{
		global_uint8flag=0;
		i=0;
		global_uint8datarecieved=Copy_uint8DataBuffer;
		i++;
		SPI_voidEnable();
		while(i<Copy_uint8Size||global_uint8flag==1)
		{
			if(global_uint8flag==0)
			{
				continue;
			}
			else if(i>=Copy_uint8Size)
			{
				break;
			}
			else
			{
				global_uint8datarecieved=Copy_uint8DataBuffer+i;
				i++;
				global_uint8flag=0;
			}
		}
	}
	else
	{
		global_uint8flag=0;
		global_uint8datarecieved=Copy_uint8DataBuffer;
		SPI_voidEnable();
	}
		while (global_uint8flag==0);

}

void SPI1_IRQHandler(void)
{
	SPI->DR=global_uint8datatotransmit;
	while (READ_BIT(SPI->SR,0)==1)
	{
		(void)SPI->DR;
	}
	global_uint8flag=1;
}

/*
void SPI1_IRQHandler(void)
{
	*(global_uint8datarecieved)=SPI->DR;
	global_uint8flag=1;
}
*/




