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
	comms_init();
	hardware_reset();
	software_reset();

	write_cmd(0x3A);
	write_data(0x55, 1);

	write_cmd(0x11); // Sleep out
	delay_ms(120);
	write_cmd(0x29); // Display on
}

void ili9341_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	uint8_t startColumnData[2] = {x0 >> 8, x0 & 0x0F};
	uint8_t endColumnData[2]   = {x1 >> 8, x1 & 0x0F};
	uint8_t startRowData[2]    = {y0 >> 8, y0 & 0x0F};
	uint8_t endRowData[2]      = {y1 >> 8, y1 & 0x0F};

	write_cmd(0x2A); // Column address set
	write_data(startColumnData, 2);
	write_data(endColumnData, 2);

	write_cmd(0x2B); // Row address set
	write_data(startRowData, 2);
	write_data(endRowData, 2);

	write_cmd(0x2C); // Memory write
}

void ili9341_fill(uint16_t color)
{
	ili9341_set_window(0, 0, 239, 319);
	uint8_t hi = color >> 8, lo = color & 0x0F;
	DC_DATA();
	CHIP_SELECT();
	for (uint32_t i = 0; i < 240u * 320u; i++)
	{
		spi_write(&hi, 1);
		spi_write(&lo, 1);
	}
	CHIP_UNSELECT();
}

void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	uint8_t colorData[2] = {color >> 8, color & 0x0F};

	ili9341_set_window(x, y, x, y);
	write_data(colorData, 2);
}
