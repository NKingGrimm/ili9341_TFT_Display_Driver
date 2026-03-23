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
#include <stdint.h>
#include <stdbool.h>

/********************************************************************************
 * MACROS AND DEFINES
 ********************************************************************************/

/********************************************************************************
 * TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * EXPORTED VARIABLES
 ********************************************************************************/

/********************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 ********************************************************************************/
void hal_init(void);

void hal_hardware_reset(void);
void hal_software_reset(void);

void hal_delay_ms(uint16_t ms);
void hal_comms_init(void);

void hal_set_pixel_format_16bits(void);
void hal_sleep_out(void);
void hal_display_on(void);
void hal_set_column_limits(uint16_t startColumn, uint16_t endColumn);
void hal_set_row_limits(uint16_t startRow, uint16_t endRow);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_HAL_H */
