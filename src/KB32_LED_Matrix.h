/*!
 * @file Adafruit_LEDBackpack.h
 *
 * Part of Adafruit's Arduino library for our I2C LED Backpacks:
 * ----> http://www.adafruit.com/products/
 * ----> http://www.adafruit.com/products/
 *
 * These displays use I2C to communicate, 2 pins are required to
 * interface. There are multiple selectable I2C addresses. For backpacks
 * with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
 * with 3 Address Select pins: 0x70 thru 0x77
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * MIT license, all text above must be included in any redistribution
 */

#ifndef __LED_MATTRIX_KB32_h__
#define __LED_MATTRIX_KB32_h__

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <utility/Adafruit_GFX_Library/Adafruit_GFX.h>

#define LED_ON 1  ///< GFX color of lit LED segments (single-color displays)
#define LED_OFF 0 ///< GFX color of unlit LED segments (single-color displays)

#define LED_RED 1    ///< GFX color for red LED segments (bi-color displays)
#define LED_YELLOW 2 ///< GFX color for yellow LED segments (bi-color displays)
#define LED_GREEN 3  ///< GFX color for green LED segments (bi-color displays)

#define HT16K33_BLINK_CMD 0x80       ///< I2C register for BLINK setting
#define HT16K33_BLINK_DISPLAYON 0x01 ///< I2C value for steady on
#define HT16K33_BLINK_OFF 0          ///< I2C value for steady off
#define HT16K33_BLINK_2HZ 1          ///< I2C value for 2 Hz blink
#define HT16K33_BLINK_1HZ 2          ///< I2C value for 1 Hz blink
#define HT16K33_BLINK_HALFHZ 3       ///< I2C value for 0.5 Hz blink

#define HT16K33_CMD_BRIGHTNESS 0xE0 ///< I2C register for BRIGHTNESS setting

#define SEVENSEG_DIGITS 5 ///< # Digits in 7-seg displays, plus NUL end

/*!
    @brief  Class for 8x16 pixel single-color matrices.
*/
class KB32_FT_Matrix : public Adafruit_GFX {

public:
  /*!
    @brief  Constructor for 8x16 pixel single-color matrices.
  */
  KB32_FT_Matrix(void);

  /*!
    @brief  Lowest-level pixel drawing function required by Adafruit_GFX.
            Does not have an immediate effect -- must call writeDisplay()
            after any drawing operations to refresh display contents.
    @param  x      Pixel column (horizontal).
    @param  y      Pixel row (vertical).
    @param  color  Pixel color (1 = pixel on, 0 = pixel off).
  */
  void drawPixel(int16_t x, int16_t y, uint16_t color);

  void setPixel_color(uint16_t color);
  void setPixel_color(uint8_t r, uint8_t g, uint8_t b);

  void setBlackground_color(uint16_t color);
  void setBlackground_color(uint8_t r, uint8_t g, uint8_t b);
  /*!
    @brief  Start I2C and initialize display state (blink off, full
            brightness).
    @param  _addr  I2C address.
  */
  void begin(uint8_t _addr);

  /*!
    @brief  Set display brightness.
    @param  b  Brightness: 0 (min) to 15 (max).
  */
  void setBrightness(uint8_t b);

  /*!
    @brief  Set display blink rate.
    @param  b  One of:
               HT16K33_BLINK_DISPLAYON = steady on
               HT16K33_BLINK_OFF       = steady off
               HT16K33_BLINK_2HZ       = 2 Hz blink
               HT16K33_BLINK_1HZ       = 1 Hz blink
               HT16K33_BLINK_HALFHZ    = 0.5 Hz blink
  */
  void blinkRate(uint8_t b);

  /*!
    @brief  Issue buffered data in RAM to display.
  */
  void writeDisplay(void);

  /*!
    @brief  Clear display.
  */
  void clear(void);

  uint16_t displaybuffer[8]; ///< Raw display data

protected:
  uint8_t i2c_addr; ///< Device I2C address

};


#define DEC 10 ///< Print value in decimal format (base 10)
#define HEX 16 ///< Print value in hexadecimal format (base 16)
#define OCT 8  ///< Print value in octal format (base 8)
#define BIN 2  ///< Print value in binary format (base 2)
#define BYTE 0 ///< Issue 7-segment data as raw bits


#endif // Adafruit_LEDBackpack_h
