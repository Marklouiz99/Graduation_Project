/*
 * nRF24_config.h
 *
 *  Created on: Jun 27, 2023
 *      Author: Mark
 */

#ifndef NRF24_CONFIG_H_
#define NRF24_CONFIG_H_


/* MISO PA6
 * MOSI PA7
 * SCK PA5
 * NSS PA2
 * CE PA3
 */


#define nRF_GPIO_PORT    GPIO_PORT_A

#define nRF_GPIO_PIN_CE   GPIO_PIN_1

#define nRF_GPIO_PIN_SS   GPIO_PIN_0

#define nRF_GPIO_PIN_IRQ  GPIO_PIN_8


#endif /* NRF24_CONFIG_H_ */
