/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 11/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/* Line options */
#define EXTI_LINE0                   0
#define EXTI_LINE1                   1
#define EXTI_LINE2                   2
#define EXTI_LINE3                   3
#define EXTI_LINE4                   4
#define EXTI_LINE5                   5
#define EXTI_LINE6                   6
#define EXTI_LINE7                   7
#define EXTI_LINE8                   8
#define EXTI_LINE9                   9
#define EXTI_LINE10                  10
#define EXTI_LINE11                  11
#define EXTI_LINE12                  12
#define EXTI_LINE13                  13
#define EXTI_LINE14                  14
#define EXTI_LINE15                  15

/* Sense Mode */
#define EXTI_FALLING_EDGE                     1
#define EXTI_RISING_EDGE                      2
#define EXTI_ON_CHANGE                        3

void MEXTI_voidEnableTriggerLine (uint8 Copy_uint8LineID, uint8 Copy_uint8Trigger);
void MEXTI_voidDisableLine (uint8 Copy_uint8LineID);
/**********************/
/* For Software Tests */
/**********************/
void MEXTI_voidSoftWareTrigger (uint8 Copy_uint8LineID);

/** ********** Call Back Function ********** **/
void MEXTI_voidCallBack (uint8 Copy_uint8EXTIn, void (*EXTInFunction)(void));

#endif
