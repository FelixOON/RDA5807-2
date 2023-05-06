/*
   Test and validation of RDA5807 on ATtiny85 device.
   It is a FM receiver with mini OLED and and two push buttons  
   
   ATtiny85 and RDA5807 wireup  

    | RDA5807 pin      | Attiny85 REF pin | Physical pin  | 
    | ----------------| -----------------| ------------- | 
    | SEEK_UP         |     PB1          |     6         | 
    | SEEK_DOWN       |     PB4          |     3         |
    | SDIO / SDA      |     SDA          |     5         |
    | SCLK / CLK      |     SCL          |     7         |
   

   By Ricardo Lima Caratti, 2020.
*/

#include <RDA5807.h>
#include <Tiny4kOLED.h>

#define SEEK_UP   PB1     
#define SEEK_DOWN PB4    

RDA5807 rx;

void setup()
{
  pinMode(SEEK_UP, INPUT_PULLUP);
  pinMode(SEEK_DOWN, INPUT_PULLUP);

  oled.begin();
  oled.clear();
  oled.on();
  oled.setFont(FONT8X16);
  oled.setCursor(0, 0);
  oled.print("RDA5807-Attiny85");
  oled.setCursor(0, 2);
  oled.print("   By PU2CLR   ");
  delay(3000);
  oled.clear();

  rx.setup();
  // rx.setVolume(8);   // Use it if necessary.
  rx.setFrequency(10390); 
  showStatus();
 
}

void showStatus() {
  char faux[7];
  oled.setCursor(0, 0);
  oled.print("FM ");
  oled.setCursor(38, 0);
  oled.print("      ");
  oled.setCursor(38, 0);
  oled.print(rx.formatFrequency(rx.getFrequency(), faux, ','));
  oled.setCursor(95, 0);
  oled.print("MHz");
}

void loop()
{
  if (digitalRead(SEEK_UP) == LOW ) {
    rx.seek(RDA_SEEK_WRAP,RDA_SEEK_UP);
    showStatus();
  }
  if (digitalRead(SEEK_DOWN) == LOW ) {
    rx.seek(RDA_SEEK_WRAP,RDA_SEEK_DOWN);
    showStatus();
  }
  delay(100);
}