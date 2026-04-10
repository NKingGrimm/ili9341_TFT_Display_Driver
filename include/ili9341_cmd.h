/**
 ********************************************************************************
 * @file    ili9341_cmd.h
 * @author  Leonardo Oseguera T.
 * @date    ${date}
 * @brief
 ********************************************************************************
 */
#ifndef ILI9341_CMD_H
#define ILI9341_CMD_H

#ifdef __cplusplus
extern "C" {
#endif
/* ==========================================================================
 * ILI9341 Command Definitions
 * Source: ILI9341 Datasheet V1.11, Section 8 (Command List)
 * ==========================================================================
 *
 * Usage with nRF52840 bare-metal SPI driver:
 *   - Pull D/CX LOW  before sending a command byte
 *   - Pull D/CX HIGH before sending parameter/data bytes
 *   - EXTC pin must be tied HIGH (VDDI) for Level 2 / Extended commands
 *     to be accepted; otherwise they are treated as NOP.
 * ========================================================================== */


/* --------------------------------------------------------------------------
 * LEVEL 1 COMMANDS  (Regulative Command Set)
 * Safe to use any time during normal operation.
 * -------------------------------------------------------------------------- */

/* --- System control --- */
#define NO_OPERATION                        0x00
#define SOFTWARE_RESET                      0x01

/* --- Read commands --- */
#define READ_DISPLAY_IDENTIFICATION         0x04
#define READ_DISPLAY_STATUS                 0x09
#define READ_DISPLAY_POWER_MODE             0x0A
#define READ_DISPLAY_MEMORY_ACCESS_CONTROL  0x0B
#define READ_DISPLAY_PIXEL_FORMAT           0x0C
#define READ_DISPLAY_IMAGE_FORMAT           0x0D
#define READ_DISPLAY_SIGNAL_MODE            0x0E
#define READ_DISPLAY_SELF_DIAGNOSTIC        0x0F

/* --- Power / sleep --- */
#define ENTER_SLEEP_MODE                    0x10
#define SLEEP_OUT                           0x11
#define PARTIAL_MODE_ON                     0x12
#define NORMAL_DISPLAY_MODE_ON              0x13

/* --- Display inversion --- */
#define DISPLAY_INVERSION_OFF               0x20
#define DISPLAY_INVERSION_ON                0x21

/* --- Gamma --- */
#define GAMMA_CURVE_SELECT                  0x26  /* Parameter: 0x01/0x02/0x04/0x08 */

/* --- Display on/off --- */
#define DISPLAY_OFF                         0x28
#define DISPLAY_ON                          0x29

/* --- Window address / memory --- */
#define COLUMN_ADDRESS_SET                  0x2A  /* Parameters: SC[15:8] SC[7:0] EC[15:8] EC[7:0] */
#define PAGE_ADDRESS_SET                    0x2B  /* Parameters: SP[15:8] SP[7:0] EP[15:8] EP[7:0] */
#define MEMORY_WRITE                        0x2C
#define COLOR_SET                           0x2D  /* Load custom color lookup table for 12-bit mode */
#define MEMORY_READ                         0x2E

/* --- Partial area / scrolling --- */
#define PARTIAL_AREA                        0x30  /* Parameters: SR[15:8] SR[7:0] ER[15:8] ER[7:0] */
#define VERTICAL_SCROLLING_DEFINITION       0x33
#define TEARING_EFFECT_LINE_OFF             0x34
#define TEARING_EFFECT_LINE_ON              0x35

/* --- Memory access / pixel format --- */
#define MEMORY_ACCESS_CONTROL               0x36  /* Controls rotation, color order — see bit flags below */
#define VERTICAL_SCROLLING_START_ADDRESS    0x37
#define IDLE_MODE_OFF                       0x38
#define IDLE_MODE_ON                        0x39
#define PIXEL_FORMAT_SET                    0x3A

/* --- Continuous memory access --- */
#define MEMORY_WRITE_CONTINUE               0x3C
#define MEMORY_READ_CONTINUE                0x3E

/* --- Tearing scanline --- */
#define SET_TEAR_SCANLINE                   0x44
#define GET_SCANLINE                        0x45

/* --- Brightness / content adaptive brightness control --- */
#define WRITE_DISPLAY_BRIGHTNESS            0x51
#define READ_DISPLAY_BRIGHTNESS             0x52
#define WRITE_CONTROL_DISPLAY               0x53
#define READ_CONTROL_DISPLAY                0x54
#define WRITE_CONTENT_ADAPTIVE_BRIGHTNESS   0x55
#define READ_CONTENT_ADAPTIVE_BRIGHTNESS    0x56
#define WRITE_CABC_MINIMUM_BRIGHTNESS       0x5E
#define READ_CABC_MINIMUM_BRIGHTNESS        0x5F

/* --- ID read --- */
#define READ_ID1_MANUFACTURER               0xDA
#define READ_ID2_MODULE_VERSION             0xDB
#define READ_ID3_MODULE_ID                  0xDC


/* --------------------------------------------------------------------------
 * LEVEL 2 COMMANDS  (Extended Command Set)
 * Configure internal analog hardware (frame rate, power, VCOM, gamma).
 * Require EXTC pin = HIGH to be accepted; otherwise treated as NOP.
 * Typically sent once during the init sequence with fixed values
 * tuned for the specific LCD panel glass on your module.
 * -------------------------------------------------------------------------- */

/* --- Interface / RGB --- */
#define RGB_INTERFACE_SIGNAL_CONTROL        0xB0

/* --- Frame rate control --- */
#define FRAME_RATE_CONTROL_NORMAL_MODE      0xB1
#define FRAME_RATE_CONTROL_IDLE_MODE        0xB2
#define FRAME_RATE_CONTROL_PARTIAL_MODE     0xB3

/* --- Display --- */
#define DISPLAY_INVERSION_CONTROL           0xB4
#define BLANKING_PORCH_CONTROL              0xB5
#define DISPLAY_FUNCTION_CONTROL            0xB6
#define ENTRY_MODE_SET                      0xB7

/* --- Backlight control --- */
#define BACKLIGHT_CONTROL_1                 0xB8
#define BACKLIGHT_CONTROL_2                 0xB9
#define BACKLIGHT_CONTROL_3                 0xBA
#define BACKLIGHT_CONTROL_4                 0xBB
#define BACKLIGHT_CONTROL_5                 0xBC
#define BACKLIGHT_CONTROL_7                 0xBE
#define BACKLIGHT_CONTROL_8                 0xBF

/* --- Power control --- */
#define POWER_CONTROL_1                     0xC0  /* Sets reference voltage for grayscale */
#define POWER_CONTROL_2                     0xC1  /* Sets charge pump step-up ratio */
#define VCOM_CONTROL_1                      0xC5  /* Sets high and low VCOM voltages */
#define VCOM_CONTROL_2                      0xC7  /* Sets VCOM offset voltage */

/* --- Non-volatile memory --- */
#define NON_VOLATILE_MEMORY_WRITE           0xD0
#define NON_VOLATILE_MEMORY_PROTECTION_KEY  0xD1
#define NON_VOLATILE_MEMORY_STATUS_READ     0xD2
#define READ_ID4                            0xD3

/* --- Gamma correction curves --- */
#define POSITIVE_GAMMA_CORRECTION           0xE0  /* 15 control points for positive gamma curve */
#define NEGATIVE_GAMMA_CORRECTION           0xE1  /* 15 control points for negative gamma curve */
#define DIGITAL_GAMMA_CONTROL_1             0xE2
#define DIGITAL_GAMMA_CONTROL_2             0xE3

/* --- Interface control --- */
#define INTERFACE_CONTROL                   0xF6


/* --------------------------------------------------------------------------
 * EXTENDED REGISTER COMMANDS  (Section 8.4)
 * Factory/init-only commands. Require EXTC = HIGH.
 * Values are typically hardcoded per-panel and never changed at runtime.
 * -------------------------------------------------------------------------- */

#define POWER_CONTROL_A                         0xCB
#define POWER_CONTROL_B                         0xCF
#define DRIVER_TIMING_CONTROL_A_INTERNAL_CLOCK  0xE8
#define DRIVER_TIMING_CONTROL_A_EXTERNAL_CLOCK  0xE9
#define DRIVER_TIMING_CONTROL_B                 0xEA
#define POWER_ON_SEQUENCE_CONTROL               0xED
#define ENABLE_3_GAMMA_CONTROL                  0xF2
#define PUMP_RATIO_CONTROL                      0xF7  /* Sets boosted voltage: DDVDH = 2x or 3x VCI */


/* --------------------------------------------------------------------------
 * MEMORY ACCESS CONTROL bit flags  (used with MEMORY_ACCESS_CONTROL 0x36)
 * OR these together to set display orientation and color order.
 *
 * Example — 90 degree rotation:
 *   send_cmd(MEMORY_ACCESS_CONTROL);
 *   send_data(FLIP_COLUMNS | SWAP_ROW_COLUMN_ORDER);
 * -------------------------------------------------------------------------- */

#define FLIP_ROWS                           0x80  /* Flip row address order (vertical mirror)      */
#define FLIP_COLUMNS                        0x40  /* Flip column address order (horizontal mirror) */
#define SWAP_ROW_COLUMN_ORDER               0x20  /* Exchange row/column axes (used for rotation)  */
#define REFRESH_BOTTOM_TO_TOP               0x10  /* Vertical refresh direction: bottom to top     */
#define COLOR_ORDER_BGR                     0x08  /* Use BGR subpixel order instead of RGB         */
#define REFRESH_RIGHT_TO_LEFT               0x04  /* Horizontal refresh direction: right to left   */

/* Convenience rotation presets */
#define ROTATION_PORTRAIT_0                 (0)
#define ROTATION_LANDSCAPE_90               (FLIP_COLUMNS | SWAP_ROW_COLUMN_ORDER)
#define ROTATION_PORTRAIT_180               (FLIP_COLUMNS | FLIP_ROWS)
#define ROTATION_LANDSCAPE_270              (FLIP_ROWS    | SWAP_ROW_COLUMN_ORDER)


/* --------------------------------------------------------------------------
 * PIXEL FORMAT values  (used with PIXEL_FORMAT_SET 0x3A)
 * -------------------------------------------------------------------------- */

#define PIXEL_FORMAT_16_BIT                 0x55  /* RGB565 — 2 bytes per pixel, most common for SPI */
#define PIXEL_FORMAT_18_BIT                 0x66  /* RGB666 — 3 bytes per pixel                      */

#ifdef __cplusplus
}
#endif

#endif /* ILI9341_CMD_H */