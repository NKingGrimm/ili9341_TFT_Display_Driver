/**
 ********************************************************************************
 * @file    ili9341_mcal_config.h
 * @author  ${user}
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

#ifndef ILI9341_MCAL_CONFIG_H
#define ILI9341_MCAL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * MACROS AND DEFINES
 ********************************************************************************/
/*
  List of microcontrollers and SoC supported:
    - NRF52840
*/
#define MICROCONTROLLER_USED NRF52840
/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#if MICROCONTROLLER_USED == NRF52840
#include "ili9341_nrf52840_mcal_config.h"
#else /* #if MICROCONTROLLER_USED == NRF52840 */
#error NO MICROCONTROLLER SELECTED
#endif /* #if MICROCONTROLLER_USED == NRF52840 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_MCAL_CONFIG_H */
