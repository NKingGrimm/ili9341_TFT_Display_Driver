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
#include <stdint.h>
#include "ili9341_mcal.h"
#if MICRCONTROLLER == NRF52840
#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#endif /* #if MICRCONTROLLER == NRF52840 */

/********************************************************************************
 * EXTERN VARIABLES
 ********************************************************************************/

/********************************************************************************
 * PRIVATE MACROS AND DEFINES
 ********************************************************************************/
inline void set_pin_as_output(uint32_t port, uint32_t pin)
{
#if MICRCONTROLLER == NRF52840
	if (port == 0)
		NRF_P0->DIRSET = (1u << pin);
	else if(port == 1)
		NRF_P1->DIRSET = (1u << pin);
#endif
}
inline void set_pin(uint32_t port, uint32_t pin)
{
#if MICRCONTROLLER == NRF52840
	if (port == 0)
		NRF_P0->OUTSET = (1u << pin);
	else if(port == 1)
		NRF_P1->OUTSET = (1u << pin);
#endif
}
inline void pin_clr(uint32_t port, uint32_t pin)
{
#if MICRCONTROLLER == NRF52840
	if (port == 0)
		NRF_P0->OUTCLR = (1u << pin);
	else if(port == 1)
		NRF_P1->OUTCLR = (1u << pin);
#endif
}
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
extern void delay_ms(uint32_t ms)
{
	for (volatile uint32_t i = 0; i < ms * 8000; i++)
		__NOP();
}

void spi_init(void)
{
	// Configure pins
	set_pin_as_output(SPI_MOSI_PORT, SPI_MOSI_PIN);
	set_pin_as_output(SPI_SCK_PORT, SPI_SCK_PIN);
	set_pin_as_output(LCD_CS_PORT, LCD_CS_PIN);
	set_pin_as_output(LCD_DC_PORT, LCD_DC_PIN);
	set_pin_as_output(LCD_RST_PORT, LCD_RST_PIN);
	CHIP_UNSELECT();

	// Use SPIM0
	NRF_SPIM0->PSEL.MOSI = (SPI_MOSI_PORT << 5u) | SPI_MOSI_PIN;
	NRF_SPIM0->PSEL.MISO = (SPI_MISO_PORT << 5u) | SPI_MISO_PIN;
	NRF_SPIM0->PSEL.SCK  = (SPI_SCK_PORT << 5u)  | SPI_SCK_PIN;
	NRF_SPIM0->FREQUENCY = SPIM_FREQUENCY_FREQUENCY_M8; // 8 MHz
	NRF_SPIM0->CONFIG = 0;															// CPOL=0, CPHA=0, MSB first
	NRF_SPIM0->ENABLE = SPIM_ENABLE_ENABLE_Enabled;
}

void spi_write(const uint8_t *data, uint32_t len)
{
	NRF_SPIM0->TXD.PTR = (uint32_t)data;
	NRF_SPIM0->TXD.MAXCNT = len;
	NRF_SPIM0->RXD.MAXCNT = 0;
	NRF_SPIM0->EVENTS_END = 0;
	NRF_SPIM0->TASKS_START = 1;
	while (!NRF_SPIM0->EVENTS_END)
		;
}
