/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 11/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_private.h"

void MAFIO_voidEXTIConfiguration(uint8 Copy_uint8EXTIn , uint8 Copy_uint8Port)
{
	if(Copy_uint8EXTIn <= 3)
	{
		AFIO->EXTICR[0] &= ~ (0b1111 << (Copy_uint8EXTIn * 4));
		AFIO->EXTICR[0] |= (Copy_uint8Port << (Copy_uint8EXTIn * 4));
	}
	else if(Copy_uint8EXTIn <= 7)
	{
		AFIO->EXTICR[0] &= ~ (0b1111 << ((Copy_uint8EXTIn-4) * 4));
		AFIO->EXTICR[0] |= (Copy_uint8Port << ((Copy_uint8EXTIn-4) * 4));
	}
	else if(Copy_uint8EXTIn <= 11)
	{
		AFIO->EXTICR[0] &= ~ (0b1111 << ((Copy_uint8EXTIn-8) * 4));
		AFIO->EXTICR[0] |= (Copy_uint8Port << ((Copy_uint8EXTIn-8) * 4));
	}
	else if(Copy_uint8EXTIn <= 15)
	{
		AFIO->EXTICR[0] &= ~ (0b1111 << ((Copy_uint8EXTIn-12) * 4));
		AFIO->EXTICR[0] |= (Copy_uint8Port << ((Copy_uint8EXTIn-12) * 4));
	}
}
