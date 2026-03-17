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

	// Hardware reset
	//reset_hardware_display();
	RST_LOW();
	delay_ms(10);
	RST_HIGH();
	delay_ms(120);

	//reset_software_display();
	write_cmd(0x01); // Software reset
	delay_ms(150);

	write_cmd(0xCB); // Power control A
	{
		uint8_t d[] = {0x39, 0x2C, 0x00, 0x34, 0x02};
		write_data(d, 5);
	}

	write_cmd(0xCF); // Power control B
	{
		uint8_t d[] = {0x00, 0xC1, 0x30};
		write_data(d, 3);
	}

	write_cmd(0xE8); // Driver timing control A
	{
		uint8_t d[] = {0x85, 0x00, 0x78};
		write_data(d, 3);
	}

	write_cmd(0xEA); // Driver timing control B
	{
		uint8_t d[] = {0x00, 0x00};
		write_data(d, 2);
	}

	write_cmd(0xED); // Power on sequence control
	{
		uint8_t d[] = {0x64, 0x03, 0x12, 0x81};
		write_data(d, 4);
	}

	write_cmd(0xF7); // Pump ratio control
	write_byte(0x20);

	write_cmd(0xC0);
	write_byte(0x23); // Power control 1 — VRH
	write_cmd(0xC1);
	write_byte(0x10); // Power control 2 — SAP, BT

	write_cmd(0xC5); // VCOM control 1
	{
		uint8_t d[] = {0x3E, 0x28};
		write_data(d, 2);
	}
	write_cmd(0xC7);
	write_byte(0x86); // VCOM control 2

	write_cmd(0x36);
	write_byte(0x48); // Memory Access Control (portrait, BGR)
	write_cmd(0x3A);
	write_byte(0x55); // Pixel format: 16 bpp (RGB565)

	write_cmd(0xB1); // Frame rate (normal mode)
	{
		uint8_t d[] = {0x00, 0x18};
		write_data(d, 2);
	}

	write_cmd(0xB6); // Display function control
	{
		uint8_t d[] = {0x08, 0x82, 0x27};
		write_data(d, 3);
	}

	write_cmd(0xF2);
	write_byte(0x00); // 3-gamma disable

	write_cmd(0x26);
	write_byte(0x01); // Gamma curve 1

	write_cmd(0xE0); // Positive gamma
	{
		uint8_t d[] = {0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
									0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00};
		write_data(d, 15);
	}

	write_cmd(0xE1); // Negative gamma
	{
		uint8_t d[] = {0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
									0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F};
		write_data(d, 15);
	}

	write_cmd(0x11); // Sleep out
	delay_ms(120);
	write_cmd(0x29); // Display on
}

void ili9341_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	write_cmd(0x2A); // Column address set
	write_u16(x0);
	write_u16(x1);

	write_cmd(0x2B); // Row address set
	write_u16(y0);
	write_u16(y1);

	write_cmd(0x2C); // Memory write
}

void ili9341_fill(uint16_t color)
{
	ili9341_set_window(0, 0, 239, 319);
	uint8_t hi = color >> 8, lo = color & 0xFF;
	DC_DATA();
	CHIP_UNSELECT();
	for (uint32_t i = 0; i < 240u * 320u; i++)
	{
		spi_write(&hi, 1);
		spi_write(&lo, 1);
	}
	CHIP_SELECT();
}

void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
	ili9341_set_window(x, y, x, y);
	write_u16(color);
}
