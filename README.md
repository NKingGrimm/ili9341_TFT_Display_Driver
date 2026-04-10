# ILI9341 Driver

A portable C driver for the ILI9341 TFT controller, organized into clean layers so the high-level API is hardware-agnostic while the MCU specifics live in a small MCAL shim.

## Layers

- **ILI9341 API**: Public drawing functions (`include/ili9341.h`).
- **HAL**: Command sequencing and display behavior (`include/ili9341_hal.h`, `src/ili9341_hal.c`).
- **MCAL**: MCU-specific GPIO/SPI/delay hooks (`include/ili9341_mcal.h`).

## Folder Structure

- `include/` Public headers.
- `src/` Driver and HAL implementations.
- `config/` Configuration headers for the HAL and the target-specific MCAL.
- `demo/` Example MCAL implementation for a specific target.

## Quick Start

1. Add the driver sources to your build:
   - Compile all files in `src/`.
   - Provide one MCU-specific C file that implements the MCAL hooks.
2. Include paths:
   - Add `include/` and `config/` to your compiler include search paths.
3. Configure the HAL:
   - Edit `config/ili9341_hal_config.h` for display size and MADCTL options.
4. Configure the MCAL:
   - Set `MICROCONTROLLER_USED` in `config/ili9341_mcal_config.h` to a supported
     target macro.
   TODO: The corresponding target config header might not be in config/ it's a dependency at the moment
   - Ensure the corresponding target config header is available in `config/`.
5. Implement the MCAL interface:
   - Implement `mcal_init`, `mcal_delay_ms`, `mcal_spi_write`, `set_pin`, and `pin_clr`.
6. Use the API:
   - Call `ili9341_init()` once, then use the drawing functions.

## API Summary

- `ili9341_init()`
- `ili9341_set_drawing_area(...)`
- `ili9341_draw_image(...)`
- `ili9341_fill_screen(...)`

## Notes

- The MCAL functions are required for your target; the library does not provide default implementations.
- All timing, GPIO control, and SPI transfers are delegated to the MCAL.
