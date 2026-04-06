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
#define HAL_DISPLAY_WIDTH  240 //pixels
#define HAL_DISPLAY_HEIGHT 320 //pixels

/* ================================= MADCLT =================================== */
#define HAL_MADCTL_ROW_WRITE_ORDER_INVERSION          FALSE
#define HAL_MADCTL_COLUMN_WRITE_ORDER_INVERSION       FALSE
#define HAL_MADCTL_HORIZONTALLY_FLIP                  FALSE
#define HAL_MADCTL_VERTICAL_REFRESH_ORDER_INVERSION   FALSE
#define HAL_MADCTL_HORIZONTAL_REFRESH_ORDER_INVERSION FALSE
#define HAL_MADCTL_RGB_BGR_INVERSION                  FALSE


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
