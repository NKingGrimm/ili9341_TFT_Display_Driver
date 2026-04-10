# Porting Guide

This guide explains how to integrate the ILI9341 driver with a new target MCU by implementing the MCAL hooks and configuring the project.

## 1. Provide a Target MCAL Config Header

Create a header with your pin mappings and any MCU-specific constants. For example:

```c
#define SPI_MOSI_PIN  ...
#define SPI_MISO_PIN  ...
#define SPI_SCK_PIN   ...
#define LCD_CS_PIN    ...
#define LCD_DC_PIN    ...
#define LCD_RST_PIN   ...
```

Then update `config/ili9341_mcal_config.h` to select your target:

```c
#define MICROCONTROLLER_USED YOUR_TARGET_MACRO
```
TODO: The corresponding target config header might not be in config/ it's a dependency at the moment
Also ensure the corresponding target config header is available in `config/`.

## 2. Implement the MCAL Hooks

Implement the MCU-dependent functions declared in `include/ili9341_mcal.h`:

- `bool mcal_init(void)`
- `void mcal_delay_ms(uint16_t ms)`
- `void mcal_spi_write(const uint8_t *data, uint32_t len)`
- `void set_pin(uint32_t pin)`
- `void pin_clr(uint32_t pin)`

These functions handle GPIO direction/output, SPI transfers, and delays.

## 3. Configure the HAL

Edit `config/ili9341_hal_config.h` to match your display geometry and MADCTL options.

## 4. Build Integration

- Compile all files in `src/`.
- Compile your MCU-specific MCAL implementation file.
- Add `include/` and `config/` to your include paths.

## 5. Basic Usage

```c
#include "ili9341.h"

int main(void)
{
    ili9341_init();
    ili9341_fill_screen(0x001F); /* Blue */
    while (1) {}
}
```
