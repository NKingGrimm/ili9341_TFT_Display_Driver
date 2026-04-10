/**
 ********************************************************************************
 * @file    ili9341_hal.c
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief   HAL implementation for ILI9341 command sequencing.
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
#define HAL_MADCTL_ROW_ADDR_ORDER_BIT           (1U << 7)
#define HAL_MADCTL_COLUMN_ADDR_ORDER_BIT        (1U << 6)
#define HAL_MADCTL_ROW_COLUMN_EXCHANGE_BIT      (1U << 5)
#define HAL_MADCTL_VERTICAL_REFRESH_ORDER_BIT   (1U << 4)
#define HAL_MADCTL_RBG_BGR_BIT                  (1U << 3)
#define HAL_MADCTL_HORIZONTAL_REFRESH_ORDER_BIT (1U << 2)

/********************************************************************************
 * PRIVATE TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * STATIC VARIABLES
 ********************************************************************************/
static uint8_t halCurrentMADCTL = 0x00;

/********************************************************************************
 * GLOBAL VARIABLES
 ********************************************************************************/

/********************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ********************************************************************************/
static void write_cmd(uint8_t cmd);
static void write_data(const uint8_t *data, uint32_t len);
static void pack_u16_be(uint16_t v, uint8_t out[2]);
static void _initialize_MADCTL();
/********************************************************************************
 * STATIC FUNCTIONS
 ********************************************************************************/
void write_cmd(uint8_t cmd)
{
	DC_CMD();
	CHIP_SELECT();
	mcal_spi_write(&cmd, 1);
	CHIP_UNSELECT();
}

void write_data(const uint8_t *data, uint32_t len)
{
	DC_DATA();
	CHIP_SELECT();
	mcal_spi_write(data, len);
	CHIP_UNSELECT();
}

void pack_u16_be(uint16_t v, uint8_t out[2])
{
	out[0] = (uint8_t)(v >> 8);
	out[1] = (uint8_t)(v & 0xFFu);
}

void _initialize_MADCTL()
{
#if HAL_MADCTL_VERTICAL_FLIP
			hal_MADCTL_invert_row_write_order();
#endif /* #if HAL_MADCTL_VERTICAL_FLIP == TRUE */

#if HAL_MADCTL_HORIZONTAL_FLIP
			hal_MADCTL_invert_column_write_order();
#endif /* #if HAL_MADCTL_HORIZONTAL_FLIP == TRUE */

#if HAL_MADCTL_LANDSCAPE_MODE
			hal_MADCTL_flip_horizontally();
#endif /* #if HAL_MADCTL_LANDSCAPE_MODE == TRUE */

#if HAL_MADCTL_VERTICAL_REFRESH_ORDER_INVERSION
			hal_MADCTL_invert_vertical_refresh_order();
#endif /* #if HAL_MADCTL_VERTICAL_REFRESH_ORDER_INVERSION == TRUE */

#if HAL_MADCTL_HORIZONTAL_REFRESH_ORDER_INVERSION
			hal_MADCTL_invert_horizontal_refresh_order();
#endif /* #if HAL_MADCTL_HORIZONTAL_REFRESH_ORDER_INVERSION == TRUE */

#if HAL_MADCTL_RGB_BGR_INVERSION
			hal_MADCTL_invert_RGB_BGR_color_order();
#endif /* #if HAL_MADCTL_RGB_BGR_INVERSION == TRUE */
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
			/* TODO: Create an internal function to init HAL and move this variable at the
			end of this function */
			halLayerInitialized = true;

			hal_hardware_reset();
			hal_software_reset();

			_initialize_MADCTL();
			hal_set_MADCTL();

			hal_set_pixel_format_16bits();
			hal_sleep_out();
			hal_display_on();
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

/* =================================== MADCTL =================================== */
void hal_MADCTL_invert_row_write_order()
{
	halCurrentMADCTL ^= HAL_MADCTL_ROW_ADDR_ORDER_BIT;
}

void hal_MADCTL_invert_column_write_order()
{
	halCurrentMADCTL ^= HAL_MADCTL_COLUMN_ADDR_ORDER_BIT;
}

void hal_MADCTL_flip_horizontally()
{
	halCurrentMADCTL ^= HAL_MADCTL_ROW_COLUMN_EXCHANGE_BIT;
}

void hal_MADCTL_invert_vertical_refresh_order()
{
	halCurrentMADCTL ^= HAL_MADCTL_VERTICAL_REFRESH_ORDER_BIT;
}

void hal_MADCTL_invert_horizontal_refresh_order()
{
	halCurrentMADCTL ^= HAL_MADCTL_HORIZONTAL_REFRESH_ORDER_BIT;
}

void hal_MADCTL_invert_RGB_BGR_color_order()
{
	halCurrentMADCTL ^= HAL_MADCTL_RBG_BGR_BIT;
}

void hal_set_MADCTL()
{
  write_cmd(MEMORY_ACCESS_CONTROL);
	write_data(&halCurrentMADCTL, 1);
}
/* ============================================================================== */

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
