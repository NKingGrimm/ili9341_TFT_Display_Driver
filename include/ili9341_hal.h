/**
 ********************************************************************************
 * @file    ili9341_hal.h
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief   Hardware abstraction layer for ILI9341 command sequencing.
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
#include "ili9341_hal_config.h"

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
/**
 * @brief Initialize the HAL and underlying MCU layer.
 */
bool hal_init(void);

/** @brief Toggle the display reset pin using the MCU layer. */
void hal_hardware_reset(void);
/** @brief Issue a software reset command. */
void hal_software_reset(void);

/* TODO: 16-bit is mentioned here. Once the configuration to have an 18-bit
  RGB image is implemented, generalize this brief element */
/** @brief Configure 16-bit pixel format. */
void hal_set_pixel_format_16bits(void);
/** @brief Exit sleep mode. */
void hal_sleep_out(void);
/** @brief Enable display output. */
void hal_display_on(void);

/******************** MADCTL ****************************/
void hal_MADCTL_invert_row_write_order(void);
void hal_MADCTL_invert_column_write_order(void);
void hal_MADCTL_flip_horizontally(void);
void hal_MADCTL_invert_vertical_refresh_order(void);
void hal_MADCTL_invert_horizontal_refresh_order(void);
void hal_MADCTL_invert_RGB_BGR_color_order(void);
void hal_set_MADCTL(void);
/******************** MADCTL ****************************/

void hal_set_column_limits(uint16_t startColumn, uint16_t endColumn);
void hal_set_row_limits(uint16_t startRow, uint16_t endRow);
void hal_write_in_memory(uint8_t *data, uint32_t dataLen);
void hal_continue_write_in_memory(uint8_t *data, uint32_t dataLen);
void hal_pack_color_16(uint16_t color, uint8_t out[2]);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_HAL_H */
