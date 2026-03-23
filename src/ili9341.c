/**
 ********************************************************************************
 * @file    ili9341.c
 * @author  ${user}
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ili9341.h"
#include "ili9341_hal.h"
//TODO: Delete this library and abstract the crossed references
#include "ili9341_mcal.h"

/********************************************************************************
 * EXTERN VARIABLES
 ********************************************************************************/

/********************************************************************************
 * PRIVATE MACROS AND DEFINES
 ********************************************************************************/
#define DISPLAY_WIDTH  239
#define DISPLAY_HEIGHT 319
/********************************************************************************
 * PRIVATE TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * STATIC VARIABLES
 ********************************************************************************/

/********************************************************************************
 * GLOBAL VARIABLES
 ********************************************************************************/

/********************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ********************************************************************************/

/********************************************************************************
 * STATIC FUNCTIONS
 ********************************************************************************/
uint8_t ili9341_set_drawing_area(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	uint8_t error = ILI9341_NO_ERROR;

	if((x1 > DISPLAY_WIDTH) ||
    (y1 > DISPLAY_HEIGHT) ||
    (x0 > x1)||
    (y0 > y1))
	{
		error = ILI9341_ERROR;
	}
	else
	{
		hal_set_column_limits(x0, x1);
		hal_set_row_limits(y0, y1);
	}

	return error;
}

uint8_t ili9341_draw_image(uint8_t *drawingRawBytes, uint8_t len)
{
	uint8_t error = ILI9341_NO_ERROR;
	return error;
}

/********************************************************************************
 * GLOBAL FUNCTIONS
 ********************************************************************************/
void ili9341_init(void)
{
	hal_init();
	hal_hardware_reset();
	hal_software_reset();

	hal_set_pixel_format_16bits();
	hal_sleep_out();
	hal_display_on();
}

// void ili9341_fill_screen(uint16_t color)
// {
// 	ili9341_set_window(0, 0, 239, 319);
// 	uint8_t hi = color >> 8, lo = color & 0x0F;
// 	hal_write_cmd(0x2C); // Memory write
// 	DC_DATA();
// 	CHIP_SELECT();
// 	for (uint32_t i = 0; i < 240u * 320u; i++)
// 	{
// 		spi_write(&hi, 1);
// 		spi_write(&lo, 1);
// 	}
// 	CHIP_UNSELECT();
// }

// void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
// {
// 	uint8_t colorData[2] = {color >> 8, color & 0x0F};

// 	ili9341_set_window(x, y, x, y);
// 	hal_write_data(colorData, 2);
// }