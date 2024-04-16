/*
 * nRF_programe.c
 *
 *  Created on: Jun 27, 2023
 *      Author: Mark
 */

#include "STD_types.h"
#include "BIT_math.h"
#include "RCC_interface.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"
#include "SYSTICK_private.h"
#include "SYSTICK_interface.h"
#include"SPI_Interface.h"
#include"nRF24_config.h"
#include"nRF24_interface.h"
#include"EXTI_interface.h"
#include"AFIO_interface.h"


void nRF_voidGPIOConfig(void)
{
	GPIO_vSetPinMode(GPIO_PORT_A,GPIO_PIN_6,GPIO_PIN_INPUT);
	GPIO_vSetPinConfig(GPIO_PORT_A,GPIO_PIN_6,GPIO_IN_FLOATING);
	GPIO_vSetPinMode(GPIO_PORT_A,nRF_GPIO_PIN_IRQ,GPIO_PIN_INPUT);
	GPIO_vSetPinConfig(GPIO_PORT_A,nRF_GPIO_PIN_IRQ,GPIO_IN_PULL);
	GPIO_vSetPinMode(GPIO_PORT_A,GPIO_PIN_7,GPIO_PIN_OUTPUT_SPD_50);
	GPIO_vSetPinConfig(GPIO_PORT_A,GPIO_PIN_7,AFIO_PUSHPULL);
	GPIO_vSetPinMode(GPIO_PORT_A,GPIO_PIN_5,GPIO_PIN_OUTPUT_SPD_50);
	GPIO_vSetPinConfig(GPIO_PORT_A,GPIO_PIN_5,AFIO_PUSHPULL);
	GPIO_vSetPinMode(GPIO_PORT_A,nRF_GPIO_PIN_SS,GPIO_PIN_OUTPUT_SPD_50);
	GPIO_vSetPinConfig(GPIO_PORT_A,nRF_GPIO_PIN_SS,GPIO_OUT_PUSHPULL);
	GPIO_vSetPinMode(GPIO_PORT_A,nRF_GPIO_PIN_CE,GPIO_PIN_OUTPUT_SPD_50);
	GPIO_vSetPinConfig(GPIO_PORT_A,nRF_GPIO_PIN_CE,GPIO_OUT_PUSHPULL);
}


void nRF_voidEXTIConfig(void)
{
	RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS,AFIOEN);

	MAFIO_voidEXTIConfiguration(AFIO_LINE8,AFIO_PortA);

	MEXTI_voidEnableTriggerLine(EXTI_LINE8,EXTI_FALLING_EDGE);

	NVIC_vEnableInterrupt(23);

}


void nRF_voidSetCSS(void)
{
	GPIO_vSetPinValue(GPIO_PORT_A,nRF_GPIO_PIN_SS,HIGH);
}
void nRF_voidClearCSS(void)
{
	GPIO_vSetPinValue(GPIO_PORT_A,nRF_GPIO_PIN_SS,LOW);
}
void nRF_voidSetCE(void)
{
	GPIO_vSetPinValue(GPIO_PORT_A,nRF_GPIO_PIN_CE,HIGH);
}

void nRF_voidClearCE(void)
{
	GPIO_vSetPinValue(GPIO_PORT_A,nRF_GPIO_PIN_CE,LOW);
}



void nRF_voidWriteReg(uint8 Copy_uint8Copy_uint8Reg,uint8 Copy_uint8Data)
{
	uint8 buf[2];
	buf[0] = Copy_uint8Copy_uint8Reg|1<<5;
	buf[1] = Copy_uint8Data;
	// Pull the CS Pin LOW to select the device
	nRF_voidClearCSS();

	SPI_voidTransmit(buf,2);
    // Pull the CS HIGH to release the device
	nRF_voidSetCSS();
}


void nRF_voidWriteMultiReg (uint8 Copy_uint8Reg, uint8 *Copy_uint8Data, uint8 Copy_uint8Size)
{
	uint8 local_uint8Regaddress[2];
	local_uint8Regaddress[0]=(Copy_uint8Reg|1<<5);


	// Pull the CS Pin LOW to select the device
	nRF_voidClearCSS();

	SPI_voidTransmit(local_uint8Regaddress,1);
	SPI_voidTransmit(Copy_uint8Data,Copy_uint8Size);

	// Pull the CS HIGH to release the device
	nRF_voidSetCSS();
}

void nRF_voidSendCmd(uint8 Copy_uint8Cmd)
{
	// Pull the CS Pin LOW to select the device
	nRF_voidClearCSS();
	SPI_voidTransmit(&Copy_uint8Cmd,1);
	// Pull the CS HIGH to release the device
	nRF_voidSetCSS();
}

uint8 nRF_uint8ReadReg (uint8 Copy_uint8Reg)
{
	uint8 local_uint8data=0;

	// Pull the CS Pin LOW to select the device
	nRF_voidClearCSS();

	SPI_voidTransmit(&Copy_uint8Reg,1);
	SPI_voidReceive(&local_uint8data,1);

	// Pull the CS HIGH to release the device
	nRF_voidSetCSS();

	return local_uint8data;
}


/* Read multiple bytes from the register */
void nRF_voidReadRegMulti (uint8 Copy_uint8Reg, uint8 *Copy_uint8Data, uint8 Copy_uint8Size)
{
	// Pull the CS Pin LOW to select the device
	nRF_voidClearCSS();

	SPI_voidTransmit(&Copy_uint8Reg, 1);
	SPI_voidReceive(Copy_uint8Data, Copy_uint8Size);

	// Pull the CS HIGH to release the device
	nRF_voidSetCSS();
}

void nRF_voidInit(void)
{
	nRF_voidClearCE();

	nRF_voidWriteReg(SETUP_AW,0x03); // 5 bytes address width

	nRF_voidWriteReg(RF_SETUP,0x0E); // power=0dbm , data rate =2Mbps

	nRF_voidWriteReg(CONFIG, 0);  // will be configured later

	nRF_voidWriteReg(EN_AA, 0);  // No Auto ACK

    nRF_voidWriteReg(EN_RXADDR, 0); // Not enabling any data pipe

    nRF_voidWriteReg(SETUP_RETR, 0);   // No retransmission

    nRF_voidWriteReg(RF_CH, 0);  // will be setup during Tx or RX

    nRF_voidSetCE();

}


void nRF_voidPTXMode(uint8* Copy_uint8Address, uint8 Copy_uint8ChannelNumber)
{
	nRF_voidClearCE();

	nRF_voidWriteReg(RF_CH,Copy_uint8ChannelNumber);

	uint8 local_uint8config;

	local_uint8config=nRF_uint8ReadReg(CONFIG);

	local_uint8config &= 0x00;

	local_uint8config |= (1<<1);

	nRF_voidWriteReg(CONFIG, local_uint8config);

	nRF_voidSetCE();

}


uint8 nRF_uint8TransmittMode(uint8* Copy_uint8Data)
{

}
