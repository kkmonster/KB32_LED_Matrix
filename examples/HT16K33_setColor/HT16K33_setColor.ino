/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

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

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif


KB32_FT_Matrix matrix = KB32_FT_Matrix();

uint8_t counter = 0;

uint8_t red = 31;
uint8_t green = 0;
uint8_t blue = 0;
uint8_t state = 0;

uint16_t color = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("HT16K33 test");
  matrix.begin(0x70);  // pass in the address
}

void loop() {

  for (uint8_t i = 0; i < 8; i++) {
    // draw a diagonal row of pixels
    matrix.displaybuffer[i] = _BV((counter + i) % 16) | _BV((counter + i + 8) % 16)  ;
  }
  // write the changes we just made to the display
  matrix.writeDisplay();

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
  //  matrix.setPixel_color(255,255,255); //OR, R,G,B
  
  //  matrix.setBlackground_color(color);
  //  matrix.setBlackground_color(255,255,255); //OR, R,G,B
  
  delay(40);
  counter++;
  if (counter >= 16) counter = 0;
}
