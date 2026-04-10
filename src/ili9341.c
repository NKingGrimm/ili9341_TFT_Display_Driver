/**
 ********************************************************************************
 * @file    ili9341.c
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ili9341.h"
#include "ili9341_hal.h"
#include <string.h>

/********************************************************************************
 * EXTERN VARIABLES
 ********************************************************************************/

/********************************************************************************
 * PRIVATE MACROS AND DEFINES
 ********************************************************************************/
#define INIT_SCREEN_BLUE 0x001F
/********************************************************************************
 * PRIVATE TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * STATIC VARIABLES
 ********************************************************************************/
static bool driverInitialized = false;
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
uint8_t ili9341_init(void)
{
	uint8_t error = ILI9341_NO_ERROR;

	if(!driverInitialized)
	{
		bool halInitialized = hal_init();
		if(halInitialized)
		{
			driverInitialized = true;
		/*TODO: Implement screen initialization. The screen must completely turn blue
			and show a message vertically and another horizontally to show there is no
			mirrored image. */
			(void) ili9341_fill_screen(INIT_SCREEN_BLUE);
		}
	}
	else
	{
		error = ILI9341_MODULE_ALREADY_INIT;
	}
	return error;
}

uint8_t ili9341_set_drawing_area(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1)
{
	uint8_t error = ILI9341_NO_ERROR;

	if(driverInitialized)
	{
		if((x1 >= HAL_DISPLAY_WIDTH) ||
			(y1 >= HAL_DISPLAY_HEIGHT) ||
			(x0 > x1)||
			(y0 > y1))
		{
			// TODO: add error for incorrect values
		}
		else
		{
			hal_set_column_limits(x0, x1);
			hal_set_row_limits(y0, y1);
		}
	}
	else
	{
		error = ILI9341_MODULE_NOT_INIT;
	}

	return error;
}

uint8_t ili9341_fill_screen(uint16_t color)
{
	uint8_t error = ILI9341_NO_ERROR;

	if(driverInitialized)
	{
		uint8_t screenAreaColored[2];

		error = ili9341_set_drawing_area(0, 239, 0, 319);

		hal_pack_color_16(color, screenAreaColored);
		hal_write_in_memory(screenAreaColored, 2);
		for(int i = 0; i < ((240U*320U) - 2); i++)
		{
			hal_continue_write_in_memory(screenAreaColored, 2);
		}
	}
	else
	{
		error = ILI9341_MODULE_NOT_INIT;
	}

	return error;
}

uint8_t ili9341_draw_image(const uint8_t *imageInRawBytes,
	uint16_t xOrigin,
	uint16_t yOrigin,
	uint16_t imageWidth,
	uint16_t imageHeight)
{
	uint8_t error = ILI9341_NO_ERROR;

	if(driverInitialized)
	{
		enum { IMAGE_CHUNK_BYTES = 256 };
		uint8_t imageChunk[IMAGE_CHUNK_BYTES];

		uint16_t x1 = (uint16_t)(xOrigin + imageWidth - 1U);
		uint16_t y1 = (uint16_t)(yOrigin + imageHeight - 1U);
		uint32_t imageLen = (uint32_t)imageWidth * (uint32_t)imageHeight * 2U;

		error = ili9341_set_drawing_area(xOrigin, x1, yOrigin, y1);

		if(imageLen > 0U)
		{
			uint32_t offset = 0U;
			while(offset < imageLen)
			{
				uint32_t remaining = imageLen - offset;
				uint32_t chunkLen = (remaining > IMAGE_CHUNK_BYTES) ? IMAGE_CHUNK_BYTES : remaining;

				memcpy(imageChunk, &imageInRawBytes[offset], chunkLen);
				if(offset == 0U)
				{
					hal_write_in_memory(imageChunk, chunkLen);
				}
				else
				{
					hal_continue_write_in_memory(imageChunk, chunkLen);
				}
				offset += chunkLen;
			}
		}
	}
	else
	{
		error = ILI9341_MODULE_NOT_INIT;
	}
	return error;
}
