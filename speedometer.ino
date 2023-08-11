
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
int speed =0;
long t1 = 0;
long t2 = 0;

//show speed or not
boolean affich = false;

void setup() {
    tft.begin();
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000); 

    //draw the little line around the speedometer
    for(int i = 120; i<=360; i+=10){
      tft.drawLine(120, 120, 120+cos((i*PI)/180)*130, 120+sin((i*PI)/180)*130, 0xffff);
    } 
    for(int i = 300; i<=360; i+=10){
      tft.drawLine(120, 120, 120+cos((i*PI)/180)*130, 120+sin((i*PI)/180)*130, 0xF800);
    }
    tft.fillCircle(120, 120, 110, 0x0000);
    for(int i = 120; i<=360; i+=30){
      tft.drawLine(120, 120, 120+cos((i*PI)/180)*130, 120+sin((i*PI)/180)*130, 0xffff);
    } 
    for(int i = 300; i<=360; i+=30){
      tft.drawLine(120, 120, 120+cos((i*PI)/180)*130, 120+sin((i*PI)/180)*130, 0xf800);
    }
    tft.fillCircle(120, 120, 100, 0x0000);

    //spin the pointer for style
    init_gauge();
    }


//spin the pointer for style
void init_gauge(){
    
    while(speed<240)
    {
      t1 = millis();
      drawPointer(speed,0x0000);
      t2 = millis();
      speed+=(t2-t1)*0.72;
      drawPointer(speed,0xF800);
    }
    while(speed>0)
    {
      t1 = millis();
      drawPointer(speed,0x0000);
      t2 = millis();
      speed-=(t2-t1)*0.72;
      drawPointer(speed,0xF800);
    }
      drawPointer(speed,0x0000);
      speed=0;
      affich = true;
      drawPointer(speed,0xF800);
      
}

//draw the pointer for a certain speed with a certain color
void drawPointer(int16_t speed, int16_t color)
{
  tft.fillTriangle(120+cos((speed+120)*PI/180)*90,120+sin((speed+120)*PI/180)*90 , 120+cos((speed+120-90)*PI/180)*3, 120+sin((speed+120-90)*PI/180)*3, 120+cos((speed+120+90)*PI/180)*3, 120+sin((speed+120+90)*PI/180)*3, color);
  tft.fillCircle(120, 120, 3, color);
  tft.fillRect(110, 200, 115, -27, 0x0000);
  if(affich == true)
  {
  tft.setFont(&FreeMonoBoldOblique12pt7b);
  tft.setTextSize(1);
  tft.setCursor(110,190);
  tft.setTextColor(0xffff);
  tft.print(String(speed)+" km/h");
  }
}


//increase or decrease speed
void loop() {
  if(digitalRead(4)==LOW){
    drawPointer(speed,0x0000);
    speed+=1;
    drawPointer(speed,0xF800);
  }
  if(digitalRead(6)==LOW){
    drawPointer(speed,0x0000);
    speed-=1;
    drawPointer(speed,0xF800);
  }
}
