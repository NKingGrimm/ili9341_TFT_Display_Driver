/**
 ********************************************************************************
 * @file    ili9341_mcal.h
 * @author  ${user}
 * @date    ${date}
 * @brief
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
extern bool mcalInitialized;

/********************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 ********************************************************************************/
void mcal_init(void);
void mcal_delay_ms(uint16_t ms);
void mcal_spi_write(const uint8_t *data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_MCAL_H */
