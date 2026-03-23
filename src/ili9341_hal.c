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
bool halInitialized = false;
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

/********************************************************************************
 * GLOBAL FUNCTIONS
 ********************************************************************************/
void hal_init(void)
{
	mcal_init();
	if(mcalInitialized)
	{
		halInitialized = true;
	}
}

void hal_delay_ms(uint16_t ms)
{
	if(halInitialized)
	{
		mcal_delay_ms(ms);
	}
}

void hal_hardware_reset(void)
{
	if(halInitialized)
	{
		// Hardware reset
		//reset_hardware_display();
		RST_LOW();
		mcal_delay_ms(10);
		RST_HIGH();
		mcal_delay_ms(120);
	}
}

void hal_software_reset(void)
{
	if(halInitialized)
	{
		//reset_software_display();
		write_cmd(0x01); // Software reset
		mcal_delay_ms(150);
	}
}

void hal_set_pixel_format_16bits()
{
	if(halInitialized)
	{
		write_cmd(PIXEL_FORMAT_SET);
		uint8_t pixelFormat[] = {0x55};
		write_data(pixelFormat, 1);
	}
}

void hal_sleep_out()
{
	if(halInitialized)
	{
		write_cmd(SLEEP_OUT); // Sleep out
		mcal_delay_ms(120);
	}
}

void hal_display_on()
{
	if(halInitialized)
	{
		write_cmd(DISPLAY_ON);
	}
}

void hal_set_column_limits(uint16_t startColumn, uint16_t endColumn)
{
	if(halInitialized)
	{
		uint8_t startColumnData[2] = {startColumn >> 8, startColumn & 0x0F};
		uint8_t endColumnData[2]   = {endColumn >> 8, endColumn & 0x0F};

		write_cmd(COLUMN_ADDRESS_SET);
		write_data(startColumnData, 2);
		write_data(endColumnData, 2);
	}
}

void hal_set_row_limits(uint16_t startRow, uint16_t endRow)
{
	if(halInitialized)
	{
		uint8_t startRowData[2] = {startRow >> 8, startRow & 0x0F};
		uint8_t endRowData[2]   = {endRow >> 8, endRow & 0x0F};

		write_cmd(PAGE_ADDRESS_SET);
		write_data(startRowData, 2);
		write_data(endRowData, 2);
	}
}