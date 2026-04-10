/**
 ********************************************************************************
 * @file    ili9341_mcal.h
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief   MCU abstraction layer interface for GPIO, SPI, and delays.
 ********************************************************************************
 */

#ifndef ILI9341_MCAL_H
#define ILI9341_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "ili9341_mcal_config.h"

/********************************************************************************
 * MACROS AND DEFINES
 ********************************************************************************/
/* MCU-specific GPIO helpers to be provided by the application. */
void set_pin(uint32_t pin);
void pin_clr(uint32_t pin);

#define CHIP_SELECT()   pin_clr(LCD_CS_PIN)
#define CHIP_UNSELECT() set_pin(LCD_CS_PIN)
#define DC_CMD()        pin_clr(LCD_DC_PIN)	// low  = command
#define DC_DATA()       set_pin(LCD_DC_PIN)  // high = data
#define RST_LOW()       pin_clr(LCD_RST_PIN)
#define RST_HIGH()      set_pin(LCD_RST_PIN)

/********************************************************************************
 * TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * EXPORTED VARIABLES
 ********************************************************************************/

/********************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 ********************************************************************************/
/**
 * @brief Initialize MCU peripherals used by the ILI9341 driver.
 * @return true when the MCU-specific layer is ready.
 *
 * The application must implement this function for the selected target.
 */
bool mcal_init(void);

/**
 * @brief Busy-wait delay in milliseconds.
 *
 * The application must implement this function for the selected target.
 */
void mcal_delay_ms(uint16_t ms);

/**
 * @brief Write a byte buffer over the MCU's SPI peripheral.
 *
 * The application must implement this function for the selected target.
 */
void mcal_spi_write(const uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_MCAL_H */
