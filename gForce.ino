
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

float x_gforce = 0;
float y_gforce = 0;


void setup() {
    tft.begin();
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000); 
    drawGindicator(x_gforce,y_gforce,0xF800);
}

void drawGindicator(float x_gforce,float y_gforce,int color){
tft.drawCircle(120, 120, 50, 0xffff);
tft.drawCircle(120, 120, 100, 0xffff);
tft.fillCircle(120+50*x_gforce,120+50*y_gforce,10,color);

}

void loop() {

}
