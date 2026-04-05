/**
 ********************************************************************************
 * @file    ili9341_nrf52840.c
 * @author  ${user}
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ili9341_hal.h"
#include "ili9341_mcal.h"
#include "ili9341_cmd.h"

/********************************************************************************
 * EXTERN VARIABLES
 ********************************************************************************/
bool halLayerInitialized = false;
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
static void write_cmd(uint8_t cmd)
{
	DC_CMD();
	CHIP_SELECT();
	mcal_spi_write(&cmd, 1);
	CHIP_UNSELECT();
}

static void write_data(const uint8_t *data, uint32_t len)
{
	DC_DATA();
	CHIP_SELECT();
	mcal_spi_write(data, len);
	CHIP_UNSELECT();
}

static void pack_u16_be(uint16_t v, uint8_t out[2])
{
	out[0] = (uint8_t)(v >> 8);
	out[1] = (uint8_t)(v & 0xFFu);
}

/********************************************************************************
 * GLOBAL FUNCTIONS
 ********************************************************************************/
bool hal_init(void)
{
	if(!halLayerInitialized)
	{
		bool mcalInitialized = mcal_init();
		if(mcalInitialized)
		{
			halLayerInitialized = true;
		}
	}

	return halLayerInitialized;
}

void hal_hardware_reset(void)
{
	if(halLayerInitialized)
	{
		RST_LOW();
		mcal_delay_ms(10);
		RST_HIGH();
		mcal_delay_ms(120);
	}
}

void hal_software_reset(void)
{
	if(halLayerInitialized)
	{
		write_cmd(0x01); // Software reset
		mcal_delay_ms(150);
	}
}

void hal_set_pixel_format_16bits()
{
	if(halLayerInitialized)
	{
		write_cmd(PIXEL_FORMAT_SET);
		uint8_t pixelFormat[] = {0x55};
		write_data(pixelFormat, 1);
	}
}

void hal_sleep_out()
{
	if(halLayerInitialized)
	{
		write_cmd(SLEEP_OUT); // Sleep out
		mcal_delay_ms(120);
	}
}

void hal_display_on()
{
	if(halLayerInitialized)
	{
		write_cmd(DISPLAY_ON);
	}
}

void hal_invert_row_write_order(uint8_t *currentMADCTL)
{}
void hal_invert_column_write_order(uint8_t *currentMADCTL)
{}
void hal_flip_horizontally(uint8_t *currentMADCTL)
{}
void hal_invert_vertical_refresh_order(uint8_t *currentMADCTL)
{}
void hal_invert_horizontal_refresh_order(uint8_t *currentMADCTL)
{}

void hal_set_RGB_color_order(uint8_t *currentMADCTL)
{
	*currentMADCTL &= 0xF7; // Clear out BGR bit, leaving it as RGB
}

void hal_set_BGR_color_order(uint8_t *currentMADCTL)
{
	*currentMADCTL |= 0x08; // Set BGR bit
}

void hal_set_MADCTL(uint8_t MADCTL)
{
  write_cmd(MEMORY_ACCESS_CONTROL);
	write_data(&MADCTL, 1);
}

void hal_set_column_limits(uint16_t startColumn, uint16_t endColumn)
{
	if(halLayerInitialized)
	{
		uint8_t columnData[4];
		pack_u16_be(startColumn, &columnData[0]);
		pack_u16_be(endColumn, &columnData[2]);

		write_cmd(COLUMN_ADDRESS_SET);
		write_data(columnData, 4);
	}
}

void hal_set_row_limits(uint16_t startRow, uint16_t endRow)
{
	if(halLayerInitialized)
	{
		uint8_t rowData[4];
		pack_u16_be(startRow, &rowData[0]);
		pack_u16_be(endRow, &rowData[2]);

		write_cmd(PAGE_ADDRESS_SET);
		write_data(rowData, 4);
	}
}

void hal_pack_color_16(uint16_t color, uint8_t out[2])
{
	pack_u16_be(color, &out[0]);
}

void hal_write_in_memory(uint8_t *data, uint32_t dataLen)
{
	if(halLayerInitialized)
	{
		write_cmd(0x2C);
		write_data(data, dataLen);
	}
}

void hal_continue_write_in_memory(uint8_t *data, uint32_t dataLen)
{
	if(halLayerInitialized)
	{
		write_cmd(0x3C);
		write_data(data, dataLen);
	}
}
