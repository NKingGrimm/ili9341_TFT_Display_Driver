/**
 ********************************************************************************
 * @file    ili9341_hal_config.h
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief   HAL configuration options for display geometry and MADCTL behavior.
 ********************************************************************************
 */

#ifndef ILI9341_HAL_CONFIG_H
#define ILI9341_HAL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * MACROS AND DEFINES
 ********************************************************************************/
#define HAL_DISPLAY_WIDTH  240 //pixels
#define HAL_DISPLAY_HEIGHT 320 //pixels

/* ================================= MADCLT =================================== */
#define HAL_MADCTL_VERTICAL_FLIP                      true
#define HAL_MADCTL_HORIZONTAL_FLIP                    false
#define HAL_MADCTL_LANDSCAPE_MODE                     false
#define HAL_MADCTL_VERTICAL_REFRESH_ORDER_INVERSION   false
#define HAL_MADCTL_HORIZONTAL_REFRESH_ORDER_INVERSION false
#define HAL_MADCTL_RGB_BGR_INVERSION                  true


/* TODO: The ILI9341 supports multiple interfaces (MCU, RGB, VSYNC). Extend this
 * file to select the desired interface and related settings. */
/********************************************************************************
 * INCLUDES
 ********************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_HAL_CONFIG_H */
