/*************************************************************/
/******Name    : Mark George Louiz ***************************/
/******Date    : 2/12/2022 ***********************************/
/******Version : 1.0 *****************************************/
/******SWC     : SPI *****************************************/
/*************************************************************/


#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void SPI_voidConfig (void);

void SPI_voidInterruptRXEnable(void);

void SPI_voidInterruptTXEnable(void);

void SPI_voidEnable (void);

void SPI_voidDisable (void);

void SPI_voidTransmit (uint8* Copy_uint8DataBuffer, uint8 Copy_uint8Size);

void SPI_voidReceive (uint8* Copy_uint8DataBuffer, uint8 Copy_uint8Size);

#endif
