
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>

// Paramètres de l'écran
#define TFT_CS   10
#define TFT_DC   7
#define TFT_RST  8

Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);


int xdecal =0;

int distance=0;

void setup() {
    tft.begin();
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000);
    tft.drawLine(0 , 120, 240, 120, 0xFD00);

    //a Commented out sun if you find it pretty

    /*
    tft.fillCircle(120,110,60,0xF81A);
    tft.fillRect(59,120,122,60,0x0000);
    tft.fillRect(59,110,122,-15,0x0000);
    tft.fillRect(59,85,122,-12,0x0000);
    tft.fillRect(59,65,122,-10,0x0000);
    */

    //draw the distance
    tft.setFont(&FreeMonoBoldOblique12pt7b);
    tft.setTextSize(4);
    tft.setCursor(90 ,95);
    tft.setTextColor(0xffff);
    tft.print(String(distance));
    tft.setTextSize(1);
    tft.setFont(&FreeSerif9pt7b);
    tft.setCursor(155 ,95);
    tft.setTextColor(0x738E);
    tft.print("Km");

    //draw the converging lines
    for(int i=20;i<180;i+=20)
    {
    tft.drawLine(120 , 120, 120+cos((i*PI)/180)*130, 120+sin((i*PI)/180)*130, 0xFD00);
    }
    
}


void loop() {

    //draw the horizontal lines and increase xdecal
    for(int i=120;i<240;i+=20)
    {
    tft.drawLine(0 , i+xdecal, 240, i+xdecal, 0x0000);
    }
    xdecal++;
    if(xdecal>20){
      xdecal=0;
    }
    for(int i=120;i<240;i+=20)
    {
    tft.drawLine(0 , i+xdecal, 240, i+xdecal, 0xFD00);
    }
    for(int i=20;i<180;i+=20)
    {
    tft.drawLine(120 , 120, 120+cos((i*PI)/180)*130, 120+sin((i*PI)/180)*130, 0xFD00);
    }
    tft.drawLine(0 , 120, 240, 120, 0xFD00);
  

}
