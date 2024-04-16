/***************************************************************************/
/* Author  : MERNA */
/* Version : 01    */
/***************************************************************************/

#ifndef _AFIO_PRIVATE_H
#define _AFIO_PRIVATE_H

#define AFIO_BASE_ADDRESS      0x40010000

typedef struct
{
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR[4];
	volatile uint32 Reserved;
	volatile uint32 MAPR2;

}AFIO_t;

#define AFIO               ((volatile AFIO_t*)AFIO_BASE_ADDRESS)


#endif
