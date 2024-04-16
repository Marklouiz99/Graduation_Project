/*************************************************************/
/******Name    : Mark George Louiz ***************************/
/******Date    : 2/12/2022 ***********************************/
/******Version : 1.0 *****************************************/
/******SWC     : SPI *****************************************/
/*************************************************************/


#ifndef SPI_PRIVATE_h
#define SPI_PRIVATE_h

#define SPI_uint32_BASE_ADDRESS   0x40013000

typedef struct{
	volatile uint32 CR1;
	volatile uint32 CR2;
	volatile uint32 SR;
	volatile uint32 DR;
	volatile uint32 CRCPR;
	volatile uint32 RXCRCR;
	volatile uint32 TXCRCR;
}SPI_RegDef_t;

#define SPI            ((SPI_RegDef_t*)SPI_uint32_BASE_ADDRESS)


#endif 
