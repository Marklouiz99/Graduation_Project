
/* Motor */
/*
 * This MCU is responsible for:
 * 1. Movement of the car (motor drive)
 * 2. control the car move with bluetooth module (UART2)
 * 3. communication with the other MCU (UART1)
 *
 * */

/* Libraries */
#include "STD_types.h"
/* MCAL */
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "SYSTICK_interface.h"
/* HAL */
#include "L298_interface.h"


/* Global Variables */
uint8 UART1_Receive = 0;
//uint8 UART2_Receive = 0;


/*******************************************************************************/
void UART1_ISR(void)
{
	UART1_Receive = UART_u8ReturnData(UART_1);
	if(UART1_Receive == 'S' || UART1_Receive == 's')
	{
		CAR_vStop(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5);
		GPIO_vSetPinValue(GPIO_PORT_A, 7, 1);
		_delay_ms(2000);
		GPIO_vSetPinValue(GPIO_PORT_A, 7, 0);
	}
	else
	{
		GPIO_vSetPinValue(GPIO_PORT_A, 7, 1);
		_delay_ms(100);
		GPIO_vSetPinValue(GPIO_PORT_A, 7, 0);
	}
}
/*******************************************************************************/


/*******************************************************************************/

int main(void)
{
	uint8 Motion;

	//Initialize System clock
    RCC_u8InitSysClk();
    RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS, GPIOA_EN);
    GPIO_vSetPinMode(GPIO_PORT_A, 7, GPIO_PIN_OUTPUT_SPD_50);
    GPIO_vSetPinConfig(GPIO_PORT_A, 7, GPIO_OUT_PUSHPULL);
    //Initialize Uart
    UART_vInit();
    //Initialize Driver (pins 0 , 1 , 4 , 5  from portA)
    L298_vInit(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1);
    L298_vInit(GPIO_PORT_A, GPIO_PIN_4, GPIO_PIN_5);
    //set callback for both UART1 & UART2
    UART_SetCallBack(UART_1, UART1_ISR);
   // UART_SetCallBack(UART_2, UART2_ISR);



    while(1)
    {
    	Motion = UART_u8ReceiveData(UART_2);
    	if(Motion == 'F')
    	{
    		CAR_vMoveForward(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5);
    	}
    	else if(Motion == 'B')
    	{
    		CAR_vMoveBackward(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5);
    	}
    	else if(Motion == 'L')
    	{
    		CAR_vMoveLeft(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5);
    	}
    	else if(Motion == 'R')
    	{
    		CAR_vMoveRight(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5);
    	}
    	else
    	{
    		CAR_vStop(GPIO_PORT_A, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_4, GPIO_PIN_5);
    	}

    }
}
