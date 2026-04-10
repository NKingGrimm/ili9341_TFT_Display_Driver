/**
 ********************************************************************************
 * @file    ili9341.h
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief   Public API for the ILI9341 display driver.
 ********************************************************************************
 */

#ifndef ILI9341_H
#define ILI9341_H

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
#define ILI9341_NO_ERROR            0x0U
#define ILI9341_MODULE_ALREADY_INIT 0x1U
#define ILI9341_MODULE_NOT_INIT     0x2U
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
 * @brief Initialize the ILI9341 driver stack.
 * @return ILI9341_NO_ERROR on success or an error code.
 */
uint8_t ili9341_init(void);

/**
 * @brief Configure the active drawing window.
 */
uint8_t ili9341_set_drawing_area(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1);

/**
 * TODO: 16-bit is mentioned here. Once the configuration to have an 18-bit
 * RGB image is implemented, generalize this brief element
 * @brief Draw a raw 16-bit RGB image at the provided origin.
 */
uint8_t ili9341_draw_image(const uint8_t *imageInRawBytes,
	uint16_t xOrigin,
	uint16_t yOrigin,
	uint16_t imageWidth,
	uint16_t imageHeight);

/**
 * TODO: 16-bit is mentioned here. Once the configuration to have an 18-bit
 * RGB image is implemented, generalize this brief element
 * @brief Fill the entire screen with a 16-bit RGB color.
 */
uint8_t ili9341_fill_screen(uint16_t color);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_H */
