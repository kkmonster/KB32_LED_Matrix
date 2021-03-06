/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit 16x8 LED Matrix backpacks
  ----> http://www.adafruit.com/products/2035
  ----> http://www.adafruit.com/products/2036
  ----> http://www.adafruit.com/products/2037
  ----> http://www.adafruit.com/products/2038
  ----> http://www.adafruit.com/products/2039
  ----> http://www.adafruit.com/products/2040
  ----> http://www.adafruit.com/products/2041
  ----> http://www.adafruit.com/products/2042
  ----> http://www.adafruit.com/products/2043
  ----> http://www.adafruit.com/products/2044
  ----> http://www.adafruit.com/products/2052

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
//#include <Adafruit_GFX.h>
#include "KB32_LED_Matrix.h"

KB32_FT_Matrix matrix = KB32_FT_Matrix();
void rainbow_color();

void setup() {
  Serial.begin(115200);
  Serial.println("16x8 LED Matrix Test");
  matrix.begin(0x70);  // pass in the address
}

static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

void loop() {
  //  matrix.clear();
  //  matrix.drawPixel(0, 0, LED_ON);
  //  matrix.drawLine(0, 0, 15, 7, LED_ON);
  //  matrix.writeDisplay();  // write the changes we just made to the display
  //  delay(500);
  //
  //  matrix.clear();
  //  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  //  matrix.writeDisplay();
  //  delay(500);
  //
  //  matrix.clear();
  //  matrix.drawBitmap(8, 0, neutral_bmp, 8, 8, LED_ON);
  //  matrix.writeDisplay();
  //  delay(500);
  //
  //  matrix.clear();
  //  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
  //  matrix.writeDisplay();
  //  delay(500);
  //
  //
  //  matrix.drawPixel(0, 0, LED_ON);
  //  matrix.writeDisplay();  // write the changes we just made to the display
  //  delay(500);
  //
  //  matrix.clear();
  //  matrix.drawLine(0, 0, 15, 7, LED_ON);
  //  matrix.writeDisplay();  // write the changes we just made to the display
  //  delay(500);
  //
  //  matrix.clear();
  //  matrix.drawRect(0, 0, 16, 8, LED_ON);
  //  matrix.fillRect(2, 2, 12, 4, LED_ON);
  //  matrix.writeDisplay();  // write the changes we just made to the display
  //  delay(500);
  //
  //  matrix.clear();
  //  matrix.drawCircle(8, 3, 3, LED_ON);
  //  matrix.writeDisplay();  // write the changes we just made to the display
  //  delay(500);
  //
  //  matrix.setTextSize(2);
  //  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  //  matrix.setTextColor(LED_ON);
  //  matrix.setRotation(1);
  //  for (int8_t x = 0; x >= -64; x--) {
  //    matrix.clear();
  //    matrix.setCursor(x, 0);
  //    matrix.print("Hello");
  //    matrix.writeDisplay();
  //    delay(100);
  //  }

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(0);

  while (1) {

    for (int8_t x = 7; x >= -40; x--) {
      matrix.clear();
      matrix.setCursor(x, 0);
      matrix.print("KB32-FT KB32-FT");
      matrix.writeDisplay();
      rainbow_color();
      delay(100);
    }

  }


}

void rainbow_color() {
  static uint8_t state, green, red, blue;
  static uint16_t color;
  switch (state) {
    case 0:
      green += 2;
      if (green >= 64) {
        green = 63;
        state = 1;
      }
      break;
    case 1:
      red--;
      if (red == 255) {
        red = 0;
        state = 2;
      }
      break;
    case 2:
      blue ++;
      if (blue == 32) {
        blue = 31;
        state = 3;
      }
      break;
    case 3:
      green -= 2;
      if (green == 255) {
        green = 0;
        state = 4;
      }
      break;
    case 4:
      red ++;
      if (red == 32) {
        red = 31;
        state = 5;
      }
      break;
    case 5:
      blue --;
      if (blue == 255) {
        blue = 0;
        state = 0;
      }
      break;
  }
  color = red << 11 | green << 5 | blue;

  matrix.setPixel_color(color);
}
