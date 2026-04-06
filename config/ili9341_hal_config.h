/**
 ********************************************************************************
 * @file    ili9341_hal_config.h
 * @author  ${user}
 * @date    ${date}
 * @brief
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
#define DISPLAY_WIDTH  240 //pixels
#define DISPLAY_HEIGHT 320 //pixels

/* TODO: ILI9341 has different interfaces to work on (MCU, RGB or VSYNC). Here
the user will have the possibility to select between those possible interfaces
and some other configurations */
/********************************************************************************
 * INCLUDES
 ********************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ILI9341_HAL_CONFIG_H */
