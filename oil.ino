
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


int affichage[7] = {0,0,0,0,0,0,0};

float pression = 0;
float old_pression =-1;

void setup() {
    tft.begin();
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000); 
    tft.drawRect(80,100,80,40,0xffff);
    tft.drawRect(115,80,10,20,0xffff);
    tft.drawRect(100,80,40,5,0xffff);
    tft.drawTriangle(210, 100, 160, 139, 160, 110, 0xffff);
    tft.drawLine(80, 100, 50, 90, 0xffff);
    tft.drawLine(80, 110, 50, 100, 0xffff);
    tft.drawLine(50, 90, 50, 100, 0xffff);
    tft.fillRect(116,81,8,20,0x0000);
    tft.fillRect(101,81,38,3,0x0000);
    tft.fillRect(81,111,80,28,0x0000);
    
    }

void drawGoutte(int16_t color)
{
  tft.fillCircle(210, 120, 3, color);
  tft.fillTriangle(207, 120, 213, 120, 210, 110, color);
}


void loop() {

    if(digitalRead(6)==LOW){
      pression+=0.10;
    }
    if(digitalRead(4)==LOW){
      pression-=0.10;
      if(pression<0)pression=0;
    }
    if(pression!=old_pression)
    {
    tft.fillRect(70, 205, 140, -27, 0x0000);  
    tft.setFont(&FreeMonoBoldOblique12pt7b);
    tft.setTextSize(1);
    tft.setCursor(70,200);
    tft.setTextColor(0xffff);
    tft.print(String(pression)+" bar");

    old_pression = pression;
    if(pression<=0 && affichage[0]!=1)
    {
      drawGoutte(0xffff);
      affichage[0]=1;
    }
    else if(pression>0 && affichage[0]!=0)
    {
      drawGoutte(0x0000);
      affichage[0]=0;
    }

    if(pression>=0.86 && affichage[1]!=1)
    {
      tft.fillRect(84, 129, 74, 7, 0x07E0);
      tft.fillTriangle(158,129,158,135,167,129,0x07E0);
      affichage[1]=1;
    }
    else if(pression<0.86 && affichage[1]!=0)
    {
      tft.fillRect(84, 129, 74, 7, 0x0000);
      tft.fillTriangle(158,129,158,135,167,129,0x0000);
      affichage[1]=0;
    }


    if(pression>=1.72 && affichage[2]!=1)
    {
      tft.fillRect(84, 120, 86, 7, 0x07E0);
      tft.fillTriangle(170,120,170,126,179,120,0x07E0);
      affichage[2]=1;
    }
    else if(pression<1.72 && affichage[2]!=0)
    {
      tft.fillRect(84, 120, 86, 7, 0x0000);
      tft.fillTriangle(170,120,170,126,179,120,0x0000);
      affichage[2]=0;
    }

    if(pression>=2.58 && affichage[3]!=1)
    {
      tft.fillRect(84, 111, 97, 7, 0x07E0);
      tft.fillTriangle(181, 111, 181, 117, 190, 111, 0x07E0);
      affichage[3]=1;
    }
    else if(pression<2.58 && affichage[3]!=0)
    {
      tft.fillRect(84, 111, 97, 7, 0x0000);
      tft.fillTriangle(181, 111, 181, 117, 190, 111, 0x0000);
      affichage[3]=0;
    }

    if(pression>=3.44 && affichage[4]!=1)
    {
      tft.fillRect(84, 103, 73, 6, 0xFFE0);
      tft.fillTriangle(182, 108, 192, 108, 198, 105, 0xFFE0);
      affichage[4]=1;
    }
    else if(pression<3.44 && affichage[4]!=0)
    {
      tft.fillRect(84, 103, 73, 6, 0x000);
      tft.fillTriangle(182, 108, 192, 108, 198, 105, 0x0000);
      
      affichage[4]=0;
    }

    if(pression>=4.3 && affichage[5]!=1)
    {
      tft.fillRect(118, 95, 4, 6, 0xFB20);  
      affichage[5]=1;
    }
    else if(pression<4.3 && affichage[5]!=0)
    {
      tft.fillRect(118, 95, 4, 6, 0x0000);  
      affichage[5]=0;
    }

    if(pression>=5.16 && affichage[6]!=1)
    {
      tft.fillRect(118, 86, 4, 7, 0xF800);  
      affichage[6]=1;
    }
    else if(pression<5.16 && affichage[6]!=0)
    {
      tft.fillRect(118, 86, 4, 7, 0x0000);  
      affichage[6]=0;
    }

    if(pression>=6.02 && affichage[7]!=1)
    {
      tft.drawLine(105,82,135,82,0xF800);
      tft.fillTriangle(180, 40, 160, 70, 200, 70, 0xf800);  
      tft.drawTriangle(180, 40, 160, 70, 200, 70, 0xffff);
      tft.drawLine(180, 45, 180, 60, 0xffff);
      tft.fillCircle(180, 65, 1, 0xffff);  
      affichage[7]=1;
    }
    else if(pression<6.02 && affichage[7]!=0)
    {
      tft.fillTriangle(180, 39, 159, 71, 201, 71, 0x0000);
      tft.drawLine(105,82,135,82,0x0000);  
      affichage[7]=0;
    }
    }


}
