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

/********************************************************************************
 * EXTERN VARIABLES
 ********************************************************************************/

/********************************************************************************
 * PRIVATE MACROS AND DEFINES
 ********************************************************************************/
#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 320
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

/********************************************************************************
 * GLOBAL FUNCTIONS
 ********************************************************************************/
void ili9341_init(void)
{
	hal_init();
	hal_hardware_reset();
	hal_software_reset();

	uint8_t newMADCTL = 0x00;
	hal_set_BGR_color_order(&newMADCTL);
	hal_set_memory_access_control(newMADCTL);

	hal_set_pixel_format_16bits();
	hal_sleep_out();
	hal_display_on();
}

uint8_t ili9341_set_drawing_area(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
	uint8_t error = ILI9341_NO_ERROR;

	if((x1 >= DISPLAY_WIDTH) ||
    (y1 >= DISPLAY_HEIGHT) ||
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

uint8_t ili9341_fill_screen(uint16_t color)
{
	uint8_t error = ILI9341_NO_ERROR;
	uint8_t screenAreaColored[2];

	error = ili9341_set_drawing_area(0, 239, 0, 319);

	hal_pack_color_16(color, screenAreaColored);
	hal_write_in_memory(screenAreaColored, 2);
	for(int i = 0; i < ((240U*320U) - 1); i++)
	{
		hal_continue_write_in_memory(screenAreaColored, 2);
	}

	return error;
}

uint8_t ili9341_draw_image(uint16_t *imageInRawBytes, uint8_t imageLen)
{
	uint8_t error = ILI9341_NO_ERROR;
	return error;
}
