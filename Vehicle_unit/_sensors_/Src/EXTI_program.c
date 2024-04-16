/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 11/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"

// Global Pointer to Function to Hold EXTI ISR Address
void (*EXTI_EXTI0Function)(void) = NULL;
void (*EXTI_EXTI1Function)(void) = NULL;
void (*EXTI_EXTI2Function)(void) = NULL;
void (*EXTI_EXTI3Function)(void) = NULL;
void (*EXTI_EXTI4Function)(void) = NULL;
void (*EXTI_EXTI9_5Function)(void) = NULL;
void (*EXTI_EXTI15_10Function)(void) = NULL;

void MEXTI_voidEnableTriggerLine (uint8 Copy_uint8LineID, uint8 Copy_uint8Trigger)
{
	/* EnableInterrupt */
	EXTI->IMR |= (1 << Copy_uint8LineID);
	/* Set Trigger */
	switch(Copy_uint8Trigger)
	{
	case EXTI_FALLING_EDGE:
		EXTI->FTSR |= (1 << Copy_uint8LineID);
		EXTI->RTSR &= (0<< Copy_uint8LineID);
		break;
	case EXTI_RISING_EDGE:
		EXTI->RTSR |= (1 << Copy_uint8LineID);
		EXTI->FTSR &= (0<< Copy_uint8LineID);
		break;
	case EXTI_ON_CHANGE:
		EXTI->FTSR |= (1 << Copy_uint8LineID);
		EXTI->RTSR |= (1 << Copy_uint8LineID);
		break;
	default : //error
		break;
	}
}

void MEXTI_voidDisableLine (uint8 Copy_uint8LineID)
{
	/* DisableInterrupt */
	EXTI->IMR &= ~(1 << Copy_uint8LineID);
}

void MEXTI_voidSoftWareTrigger (uint8 Copy_uint8LineID)
{
	EXTI->SWIER |= (1 << Copy_uint8LineID);
}

void MEXTI_voidCallBack (uint8 Copy_uint8EXTIn, void (*EXTInFunction)(void))
{
	if(Copy_uint8EXTIn == EXTI_LINE0)
		EXTI_EXTI0Function = EXTInFunction;
	else if(Copy_uint8EXTIn == EXTI_LINE1)
		EXTI_EXTI1Function = EXTInFunction;
	else if(Copy_uint8EXTIn == EXTI_LINE2)
		EXTI_EXTI2Function = EXTInFunction;
	else if(Copy_uint8EXTIn == EXTI_LINE3)
		EXTI_EXTI3Function = EXTInFunction;
	else if(Copy_uint8EXTIn == EXTI_LINE4)
		EXTI_EXTI4Function = EXTInFunction;
	else if(Copy_uint8EXTIn <= EXTI_LINE9)
		EXTI_EXTI9_5Function = EXTInFunction;
	else if(Copy_uint8EXTIn <= EXTI_LINE15)
		EXTI_EXTI15_10Function = EXTInFunction;
}

/* ISR of EXTI0 */
void EXTI0_IRQHandler(void)
{
	if (EXTI_EXTI0Function != NULL)
		EXTI_EXTI0Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR , EXTI_LINE0); // Clear Flag
}
/* ISR of EXTI1 */
void EXTI1_IRQHandler(void)
{
	if (EXTI_EXTI1Function != NULL)
		EXTI_EXTI1Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR, EXTI_LINE1); // Clear Flag
}

/* ISR of EXTI2 */
void EXTI2_IRQHandler(void)
{
	if (EXTI_EXTI2Function != NULL)
		EXTI_EXTI2Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR, EXTI_LINE2); // Clear Flag
}

/* ISR of EXTI3 */
void EXTI3_IRQHandler(void)
{
	if (EXTI_EXTI3Function != NULL)
		EXTI_EXTI3Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR, EXTI_LINE3); // Clear Flag
}

/* ISR of EXTI4 */
void EXTI4_IRQHandler(void)
{
	if (EXTI_EXTI4Function != NULL)
		EXTI_EXTI4Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR, EXTI_LINE5); // Clear Flag
}

/* ISR of EXTI5:9 */
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_EXTI9_5Function != NULL)
	EXTI_EXTI9_5Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR , EXTI_LINE5); // Clear Flag
	SET_BIT(EXTI->PR , EXTI_LINE6);
	SET_BIT(EXTI->PR , EXTI_LINE7);
	SET_BIT(EXTI->PR , EXTI_LINE8);
	SET_BIT(EXTI->PR , EXTI_LINE9);
}

/* ISR of EXTI10:15 */
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_EXTI15_10Function != NULL)
	EXTI_EXTI15_10Function();

	else
	{
		/* Do Nothing */
	}
	SET_BIT(EXTI->PR , EXTI_LINE10); // Clear Flag
	SET_BIT(EXTI->PR , EXTI_LINE11);
	SET_BIT(EXTI->PR , EXTI_LINE12);
	SET_BIT(EXTI->PR , EXTI_LINE13);
	SET_BIT(EXTI->PR , EXTI_LINE14);
	SET_BIT(EXTI->PR , EXTI_LINE15);
}

