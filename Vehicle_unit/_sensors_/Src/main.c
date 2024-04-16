/* Sensors */
/*
 * This MCU is for the sensors:
 * 1. MPU that works with I2C at PB6 & PB7
 * 2.
 * */


/* Libraries */
#include "STD_types.h"
#include "BIT_math.h"
#include "math.h"
/* MCAL */
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "I2C_interface.h"
#include "SYSTICK_interface.h"
#include "UART_interface.h"
/* HAL */
#include "MPU6050_interface.h"
#include "ULTRA_interface.h"



int main(void)
{
	uint8 MPU_flag = 0;
	uint16 Distance = 0;
	double MPU_oldArr[3];
	sint16 accel_buff[3];

	//Enable system clock
    RCC_u8InitSysClk();
    //Enable portA ,SPI1
    RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS, GPIOA_EN);
    RCC_u8EnablePeripheralClk(RCC_u8_APB2_BUS, SPI1EN);
    //define pin 7 of portA as output
    GPIO_vSetPinMode(GPIO_PORT_B, GPIO_PIN_9, GPIO_PIN_OUTPUT_SPD_50);
    GPIO_vSetPinConfig(GPIO_PORT_B, GPIO_PIN_9, GPIO_OUT_PUSHPULL);

   /* //Enable TIMER2
    RCC_u8EnablePeripheralClk(RCC_u8_APB1_BUS, TIM2EN);
    TIMER2->PSC = 800-1 ;	//prescaler = 800*/

    //Initialize I2C
    I2C_vInit();
    //initialize UART
    UART_vInit();
    //Initialize MPU6050 sensor
    MPU6050_vInit();

    _delay_ms(50);
    ULTRA_vInit();

    //Get initial readings
    MPU6050_vReadAccel_ALL(accel_buff);

    MPU_oldArr[0] = accel_buff[0]*9.8*2/32768;
    MPU_oldArr[1] = accel_buff[1]*9.8*2/32768;
    MPU_oldArr[2] = accel_buff[2]*9.8*2/32768;


    while(1)
    {
    	MPU_flag = MPU6050_vDetectChange(MPU_oldArr);
    	Distance = ULTRA_u16GetDistance();

    	if(MPU_flag == 1)
    	{
    		if(Distance <= 5)
    		{
    			UART_vSendData(UART_1, 'S');
    		}
    		else
    		{
    			UART_vSendData(UART_1, '0');
    		}

    	/*	GPIO_vSetPinValue(GPIO_PORT_A, 7, 1);
    		_delay_ms(1000);
    		GPIO_vSetPinValue(GPIO_PORT_A, 7, 0);*/
    	//	UART_vSendData(UART_1, '0');
    	}
    	_delay_ms(50);
    }

}
