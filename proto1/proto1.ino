#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"

// Library only supports hardware SPI at this time
// Connect SCLK to UNO Digital #13 (Hardware SPI clock)
// Connect MISO to UNO Digital #12 (Hardware SPI MISO)
// Connect MOSI to UNO Digital #11 (Hardware SPI MOSI)

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

int sensorPin = A0;

uint16_t tx, ty;
int firstDigit;
int secondDigit;
int thirdDigit;

char string[15] = "The Power is: ";
int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int firstX = 100;
int firstY = 150;
int secondX = 150;
int secondY = 150;
int thirdX = 200;
int thirdY = 150;

 
void setup() 
{
  Serial.begin(9600);
  Serial.println("RA8875 start");
  
  /* Initialise the display using 'RA8875_480x272' or 'RA8875_800x480' */
  if (!tft.begin(RA8875_480x272)) {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.fillScreen(RA8875_WHITE);

  // Enter TextMode 
  tft.textMode();
  
  // set up text characteristics, write 'string'
  tft.textSetCursor(10, 10);
  tft.textEnlarge(3);
  tft.textTransparent(RA8875_RED);
  tft.textWrite(string);
  tft.textColor(RA8875_WHITE, RA8875_RED);  
}

void writeDigit(int digit, int numX, int numY){

  tft.textSetCursor(numX, numY);  
  tft.textEnlarge(4);
  tft.textColor(RA8875_RED, RA8875_WHITE);
 
  if (digit == nums[1])
    tft.textWrite("1");
  else if (digit == nums[2])
    tft.textWrite("2");
  else if (digit == nums[3])
    tft.textWrite("3");
  else if (digit == nums[4])
    tft.textWrite("4");
  else if (digit == nums[5])
    tft.textWrite("5");
  else if (digit == nums[6])
    tft.textWrite("6");
  else if (digit == nums[7])
    tft.textWrite("7");
  else if (digit == nums[8])
    tft.textWrite("8");
  else if (digit == nums[9])
    tft.textWrite("9");
  else
    tft.textWrite("0");  
    
}

void getPower(int digit1, int digit2, int digit3){
  
  // prepare to read voltage
  float temp1 = analogRead(sensorPin);
  Serial.println(temp1);
  float temp2 = temp1/5;
  int powerInput = (int) temp2;
 Serial.println(powerInput); 
  
  // get digits
  digit1 = powerInput / 100;
  digit2 = (powerInput % 100) / 10;
  digit3 = powerInput % 10;
  
  firstDigit = digit1;
  secondDigit = digit2;
  thirdDigit = digit3;
 
}

void loop(){
  
  getPower(firstDigit, secondDigit, thirdDigit);  
  writeDigit(firstDigit, firstX, firstY);
  writeDigit(secondDigit, secondX, secondY);
  writeDigit(thirdDigit, thirdX, thirdY);
  delay(500);  
  
}
