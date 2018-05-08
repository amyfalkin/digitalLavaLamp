//Amy Falkin Final Project
//5/3/18
// DHT example Written by Ladyada, public domain
//I also used some of the scrolling text RGB example from Adafruit but changed it completely.


#include "DHT.h"
#define DHTPIN 11     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr
#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

const char str[] PROGMEM = "Adafruit 16x32 RGB LED Matrix";
// Initial X,Y pos & velocity for 3 bouncy balls
int8_t ball[5][4] = {
  {  3,  0,  1,  0 },
  { -17, 15,  1, 0 },
  { 27,  4, -1,  0 },
  {12, 10,   1,    0},
  { -22, 2,   1,    0}
};

void setup() {
  Serial.begin(9600);
  //begin the RGB LED matrix
  matrix.begin();
  //begin the DHT22 temp sensor
  dht.begin();
  //pinMode(DHTPIN, INPUT);
}

//Draw the scene with the background defined by RGB colors and the 5 balls in different colors
void drawLava(int backR, int backG, int backB, uint16_t ballcolor[5]) {
  // Clear background
  //matrix.begin();
  matrix.fillScreen(matrix.Color333(backR, backG, backB));
  byte i;
  // Bounce three balls around
  for (i = 0; i < 5; i++) {
    // Draw 'ball'
    matrix.fillCircle(ball[i][0], ball[i][1], 9, ballcolor[i]);
    // Update X, Y position
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
    // Bounce off edges
    if ((ball[i][0] == 0) || (ball[i][0] == (matrix.width() - 1)))
      ball[i][2] *= -1;
    if ((ball[i][1] == 0) || (ball[i][1] == (matrix.height() - 1)))
      ball[i][3] *= -1;
  }
  // Update display
  matrix.swapBuffers(false);
}

void coldestColors() {
  //sets the colors of the 5 balls for the temperature range from 0 - 30
  uint16_t coldestColors[5] = {
    0x0085ff,
    0x0085ff,
    0x0085ff,
    0x0085ff,
    0x0085ff
  };
  //draws the scene incorporating the background colors
  drawLava(255, 255, 255, coldestColors);
}

void coldColors() {
  //sets the colors of the 5 balls for the temperature range from 31 - 45
  uint16_t coldColors[5] = {
    0x17B8,
    0xAE7E,
    0x17B8,
    0xAE7E,
    0xAE7E
  };
  drawLava(0, 0, 255, coldColors);
}

void warmColors() {
  //sets the colors of the 5 balls for the temperature range from 46 - 65
  uint16_t warmColors[5] = {
    0xFFED,
    0xFFED,
    0xFFED,
    0xFFED,
    0xFFED
  };
  drawLava(0, 255, 0, warmColors);
}


void warmerColors() {
  //sets the colors of the 5 balls for the temperature range from 66 - 75
  uint16_t warmerColors[5] = {
    0xFF20, // Yellow
    0xFF20, // Yellow
    0xFFC0,  // Yellow
    0xFFC0,
    0xFFC0 //other
  };
  drawLava(7, 3, 0, warmerColors);
}


void hotColors() {
  //sets the colors of the 5 balls for the temperature range from 75 - 100
  uint16_t hotColors[5] = {
    0xFBE0,
    0xFB40,
    0xFB40,
    0xFB40,
    0xFBE0
  };
  drawLava(7, 0, 0, hotColors);
}


void loop() {
  // Wait a 2 seconds between measurements.
  //delay(2000);
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //assign temperature to f value
  double f = dht.readTemperature(true);
  //print the temperature value in Serial
  Serial.print(f);
  Serial.print(" *F\t");

  //if temperature is above 65, show warmColors() function
  if (f > 65) {
    warmerColors();
  }
  //  if (f < 30 && f > 0) {
  //    Serial.println("Freezing!");
  //  coldestColors();
  // //    show blue and white matrix
  // } else if (f > 31 && f < 45) {
  //  Serial.println("Cold");
  //    coldColors();
  //    // show light blue and dark blue matrix
  //} else if (f > 46 && f < 65) {
  //    Serial.println("Cool!");
  //    // show dark green and light yellow matrix
  //    warmColors();
  //  } else if (f > 66 && f < 75) {
  //    Serial.println("Warm!");
  //    warmerColors();
  //    // show orange and yellow matrix
  //  } else if (f > 76 && f < 100) {
  //   Serial.println("Hot!");
  //    hotColors();
  //    //show red and orange matrix
  // }
  //



}
