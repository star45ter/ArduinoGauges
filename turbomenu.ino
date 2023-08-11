
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


//array indicating if a circle is there or not
int allumage[7]= {0,0,0,0,0,0,0};

//angle of the center turbine
int16_t angleturbine = 0;

//pressure
float pression = 2.5;
float oldpressure = -1;

void setup() {
    tft.begin();
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000);

    //Draw the Turbo
    tft.drawCircle(120,120,60,0xffff);
    tft.fillRect(120,60,61,40,0x0000);
    tft.drawCircle(120,120,20,0xffff);
   
    tft.drawLine(120,60,185,60,0xffff);
    tft.drawLine(175,100,185,100,0xffff);
    tft.drawLine(185,60,185,100,0xffff);
    }


//draw the center Turbine with a certain angle
void drawTurbine(int16_t angle, int16_t color)
{
  tft.drawLine(120,120,120+cos((angle*PI)/180)*15,120+sin((angle*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+60)*PI)/180)*15,120+sin(((angle+60)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+120)*PI)/180)*15,120+sin(((angle+120)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+180)*PI)/180)*15,120+sin(((angle+180)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+240)*PI)/180)*15,120+sin(((angle+240)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+300)*PI)/180)*15,120+sin(((angle+300)*PI)/180)*15,color);
}



long t1 = 0;
long t2 = 0;
void loop() {

  //spin the turbine
  t1 = millis();
  drawTurbine(angleturbine,0x0000);
  t2 = millis();
  angleturbine+=(t2-t1)*0.6 ;
  drawTurbine(angleturbine,0xffff);

  delay(10);

  //change the pressure
  if(oldpressure!=pression)
  {

    tft.fillRect(70,218,125,-25,0x0000);
    tft.setFont(&FreeMonoBoldOblique12pt7b);
    tft.setTextSize(1);
    tft.setCursor(70,210);
    tft.setTextColor(0xffff);
    tft.print(String(pression)+" bar");
    oldpressure=pression;
  }


  if(digitalRead(6)==LOW)
  {
    if(pression<4)pression+=0.1;
  }
   if(digitalRead(4)==LOW)
  {
    if(pression>0)pression-=0.1;
    if(pression<0)pression=0;
  }


  //actualize the circles if needed
  if(pression>0 && allumage[0]!=1)
      {
         tft.drawCircle(120,120,25,0x1FE0);
         allumage[0]=1;

      }
      else if (pression<=0 && allumage[0]==1){
        tft.drawCircle(120,120,25,0x0000);
         allumage[0]=0;
      }
       if(pression>0.6 && allumage[1]!=1){
          tft.drawCircle(120,120,30,0x1FE0);
          allumage[1]=1;
          
        }
        else if (pression<=0.6 && allumage[1]==1){
         tft.drawCircle(120,120,30,0x0000);
         allumage[1]=0;
      }

if(pression>1.2 && allumage[2]!=1){
            tft.drawCircle(120,120,35,0xBFE0);
            allumage[2]=1;
              
          }
          else if (pression<=1.2 && allumage[2]==1){
         tft.drawCircle(120,120,35,0x0000);
         allumage[2]=0;
      }
if(pression>1.8 && allumage[3]!=1){
              tft.drawCircle(120,120,40,0xFFA0);
              allumage[3]=1;
               
              }
              else if (pression<=1.8 && allumage[3]==1){
         tft.drawCircle(120,120,40,0x0000);
         allumage[3]=0;
      }
               if(pression>2.4 && allumage[4]!=1){
                tft.drawCircle(120,120,45,0xFFA0);
                allumage[4]=1;
                   
                }
                else if (pression<=2.4 && allumage[4]==1){
         tft.drawCircle(120,120,45,0x0000);
         allumage[4]=0;
      }
                 if(pression>3 && allumage[5]!=1){
                    tft.drawCircle(120,120,50,0xFB80);
                    allumage[5]=1;
                   
                  }
                  else if (pression<=3 && allumage[5]==1){
         tft.drawCircle(120,120,50,0x0000);
         allumage[5]=0;
      }
                   if(pression>3.6 && allumage[6]!=1){
                    tft.drawCircle(120,120,55,0xF800);
                    allumage[6]=1;
                    }
                    else if (pression<=3.6 && allumage[6]==1){
         tft.drawCircle(120,120,55,0x0000);
         allumage[6]=0;
      }
}
