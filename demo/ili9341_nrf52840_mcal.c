/**
 ********************************************************************************
 * @file    ili9341_nrf52840_mcal.c
 * @author  ${user}
 * @date    ${date}
 * @brief
 ********************************************************************************
 */

/********************************************************************************
 * INCLUDES
 ********************************************************************************/
#include "ili9341_mcal.h"
#include "nrf52840.h"
#include "nrf52840_bitfields.h"

/********************************************************************************
 * EXTERN VARIABLES
 ********************************************************************************/

/********************************************************************************
 * PRIVATE MACROS AND DEFINES
 ********************************************************************************/
static inline void set_pin_as_output(uint32_t pin)
{
	if (pin < 32)
		NRF_P0->DIRSET = (1u << pin);
	else
		NRF_P1->DIRSET = (1u << (pin - 32u));
}
inline void set_pin(uint32_t pin)
{
	if (pin < 32)
		NRF_P0->OUTSET = (1u << pin);
	else
		NRF_P1->OUTSET = (1u << (pin - 32u));
}
inline void pin_clr(uint32_t pin)
{
	if (pin < 32)
		NRF_P0->OUTCLR = (1u << pin);
	else
		NRF_P1->OUTCLR = (1u << (pin - 32u));
}
/********************************************************************************
 * PRIVATE TYPEDEFS
 ********************************************************************************/

/********************************************************************************
 * STATIC VARIABLES
 ********************************************************************************/
static bool mcalLayerInitialized = false;

/********************************************************************************
 * GLOBAL VARIABLES
 ********************************************************************************/

/********************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ********************************************************************************/

/********************************************************************************
 * STATIC FUNCTIONS
 ********************************************************************************/
static void delay_timer_init()
{
	NRF_TIMER1->TASKS_STOP = 1;
	NRF_TIMER1->TASKS_CLEAR = 1;
	NRF_TIMER1->MODE = TIMER_MODE_MODE_Timer;
	NRF_TIMER1->BITMODE = TIMER_BITMODE_BITMODE_32Bit;
	NRF_TIMER1->PRESCALER = 4; // 16 MHz / 2^4 = 1 MHz
	NRF_TIMER1->SHORTS = 0;
	NRF_TIMER1->CC[0] = 0;
}

static void spi_init()
{
	// Configure pins
	set_pin_as_output(SPI_MOSI_PIN);
	set_pin_as_output(SPI_SCK_PIN);
	set_pin_as_output(LCD_CS_PIN);
	set_pin_as_output(LCD_DC_PIN);
	set_pin_as_output(LCD_RST_PIN);
	CHIP_UNSELECT();

	// Use SPIM0
	NRF_SPIM0->PSEL.MOSI = SPI_MOSI_PIN;
	NRF_SPIM0->PSEL.MISO = SPI_MISO_PIN;
	NRF_SPIM0->PSEL.SCK  = SPI_SCK_PIN;
	NRF_SPIM0->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_M8; // 8 MHz
	NRF_SPIM0->CONFIG = 0;															// CPOL=0, CPHA=0, MSB first
	NRF_SPIM0->ENABLE = SPIM_ENABLE_ENABLE_Enabled;
}

/********************************************************************************
 * GLOBAL FUNCTIONS
 ********************************************************************************/
bool mcal_init(void)
{
	if(mcalLayerInitialized == false)
	{
		delay_timer_init();
		spi_init();

		mcalLayerInitialized = true;
	}
	else{}
	return mcalLayerInitialized;
}

void mcal_delay_ms(uint16_t ms)
{
	if(mcalLayerInitialized == true)
	{
		if (ms != 0)
		{
			uint32_t ticks = (uint32_t)ms * 1000u; // 1 MHz timer => 1000 ticks per ms
			NRF_TIMER1->TASKS_STOP = 1;
			NRF_TIMER1->TASKS_CLEAR = 1;
			NRF_TIMER1->EVENTS_COMPARE[0] = 0;
			NRF_TIMER1->CC[0] = ticks;
			NRF_TIMER1->TASKS_START = 1;
			while (NRF_TIMER1->EVENTS_COMPARE[0] == 0);
			NRF_TIMER1->TASKS_STOP = 1;
		}
	}
	else{}
}

void mcal_spi_write(const uint8_t *data, uint32_t len)
{
	if(mcalLayerInitialized == true)
	{
		NRF_SPIM0->TXD.PTR = (uint32_t)data;
		NRF_SPIM0->TXD.MAXCNT = len;
		NRF_SPIM0->RXD.MAXCNT = 0;
		NRF_SPIM0->EVENTS_END = 0;
		NRF_SPIM0->TASKS_START = 1;
		while (!NRF_SPIM0->EVENTS_END);
	}
	else{}
}
