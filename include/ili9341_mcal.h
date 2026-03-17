/**
 ********************************************************************************
 * @file    ili9341_nrf52840.h
 * @author  ${user}
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

#ifndef ILI9341_HAL_H
#define ILI9341_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ili9341_config.h"

/********************************************************************************
 * MACROS AND DEFINES
 ********************************************************************************/
void set_pin_as_output(uint32_t port, uint32_t pin);
void set_pin(uint32_t port, uint32_t pin);
void pin_clr(uint32_t port, uint32_t pin);

#define CHIP_UNSELECT() pin_clr(LCD_CS_PORT, LCD_CS_PIN)
#define CHIP_SELECT()   set_pin(LCD_CS_PORT, LCD_CS_PIN)
#define DC_CMD()        pin_clr(LCD_DC_PORT, LCD_DC_PIN)	// low  = command
#define DC_DATA()       set_pin(LCD_DC_PORT, LCD_DC_PIN)  // high = data
#define RST_LOW()       pin_clr(LCD_RST_PORT, LCD_RST_PIN)
#define RST_HIGH()      set_pin(LCD_RST_PORT, LCD_RST_PIN)

/********************************************************************************
 * TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * EXPORTED VARIABLES
 ********************************************************************************/

/********************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 ********************************************************************************/
void spi_init(void);
void spi_write(const uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_HAL_H */
