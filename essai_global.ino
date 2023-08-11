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
String menu[5] = {"G-Force","Boost","Settings","Speed","Incline"};
int angle=0;
int16_t centre_rotor_x =220;
int16_t centre_rotor_y =120;
int16_t rotor_size = 200;
int8_t menuselecteditem = 3;
int8_t buttonState = 0;
int colorrotor[5] = {0xF800,0xffff,0x001F,0x07E0,0x881F};
int8_t color_rotor = 0;
int8_t allumage[7]= {0,0,0,0,0,0,0};
int16_t angleturbine = 0;
float pression = 2.5;
float oldpressure = -1;
int8_t global_state=0;
int16_t speed =0;
long t1 = 0;
long t2 = 0;

boolean affich = false;

void setup() {
    tft.begin();
    tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000);  // Fill screen with black background
    pinMode(6, INPUT);
    pinMode(4, INPUT);
    pinMode(2, OUTPUT);
    digitalWrite(2,HIGH);
    menuActu();
}

void menuActu(){
  tft.fillRect(10, 130, 120, -25, 0x0000);
  tft.fillRect(20, 95, 120, -25, 0x0000);
  tft.fillRect(20, 165, 120, -25, 0x0000);
  tft.fillRect(40, 60, 120, -25, 0x0000);
  tft.fillRect(40, 200, 120, -25, 0x0000);

  tft.setFont(&FreeMonoBoldOblique12pt7b);
    tft.setTextSize(1);

    tft.setTextColor(0xffff);
    tft.setCursor(10, 120);
    tft.print(menu[2]);

    tft.setTextColor(0xAD55);
    tft.setCursor(25, 85);
    tft.print(menu[1]);
    tft.setCursor(25, 155);
    tft.print(menu[3]);
    
    tft.setTextColor(0x39C7);
    tft.setCursor(40, 50);
    tft.print(menu[0]);
    tft.setCursor(40, 190);
    tft.print(menu[4]);
    tft.drawCircle(centre_rotor_x, centre_rotor_y, rotor_size/6, colorrotor[color_rotor]);
}


void menuUp(){
  String memo = menu[0];
  for(int8_t i=0;i<5;i++)
  {
    menu[i]=menu[i+1];
  }
  menu[4]=memo;
  menuActu();
  menuselecteditem++;
  if(menuselecteditem>5)
  {
    menuselecteditem=1;
  }
}

void menuDown(){
  String memo = menu[4];
  for(int8_t i=4;i>0;i--)
  {
    menu[i]=menu[i-1];
  }
  menu[0]=memo;
  menuActu();
  if(menuselecteditem<1)
  {
    menuselecteditem=5;
  }
}

void drawReuleaux(int16_t centre_x,int16_t centre_y,int16_t size,int16_t angle, int16_t color){

  int16_t internaltriglenght = (size/2)*0.866;

  tft.drawCircle((cos(((90+angle)*PI)/180)*(internaltriglenght/1.4))+centre_x, (sin(((90+angle)*PI)/180)*(internaltriglenght/1.4))+centre_y, size/25, color);
  tft.drawCircle((cos(((-30+angle)*PI)/180)*(internaltriglenght/1.4))+centre_x, (sin(((-30+angle)*PI)/180)*(internaltriglenght/1.4))+centre_y, size/25, color);
  tft.drawCircle((cos(((210+angle)*PI)/180)*(internaltriglenght/1.4))+centre_x, (sin(((210+angle)*PI)/180)*(internaltriglenght/1.4))+centre_y, size/25, color);

  tft.drawLine((cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((55+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((55+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((55+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((55+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((45+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((45+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((45+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((45+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((35+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((35+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((35+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((35+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((25+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((25+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((25+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((25+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((15+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((15+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((15+angle)*PI)/180)*(size*3/4))+(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((15+angle)*PI)/180)*(size*3/4))+(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x,(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, color);

  tft.drawLine((cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-75+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-75+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-75+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-75+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-85+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-85+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-85+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-85+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-95+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-95+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-95+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-95+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-105+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-105+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-105+angle)*PI)/180)*(size*3/4))+(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-105+angle)*PI)/180)*(size*3/4))+(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x,(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  
  tft.drawLine((cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-195+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-195+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-195+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-195+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-205+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-205+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-205+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-205+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-215+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-215+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-215+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-215+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((-225+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-225+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  tft.drawLine((cos(((-225+angle)*PI)/180)*(size*3/4))+(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x, (sin(((-225+angle)*PI)/180)*(size*3/4))+(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y, (cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x,(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y, color);
  
}


void changecolorotor(){
  color_rotor++;
    if(color_rotor>4)
  { 
  color_rotor=0;
  }

  tft.drawCircle(centre_rotor_x, centre_rotor_y, rotor_size/6, colorrotor[color_rotor]);
}

void launchTurbo(){
  global_state=1;
  tft.setRotation(1);  // Adjust rotation if needed
    tft.fillScreen(0x0000);
    tft.drawCircle(120,120,60,0xffff);
    tft.fillRect(120,60,61,40,0x0000);
    tft.drawCircle(120,120,20,0xffff);
   
    tft.drawLine(120,60,185,60,0xffff);
    tft.drawLine(175,100,185,100,0xffff);
    tft.drawLine(185,60,185,100,0xffff);
}

void launchSpeedometer()
{
  global_state=2;
tft.fillScreen(0x0000); 
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
    init_gauge();

}


void loop() {
  if(global_state==0)
  {

 drawReuleaux(centre_rotor_x,centre_rotor_y,rotor_size,angle,0x0000);
 angle+=2;
 drawReuleaux(centre_rotor_x,centre_rotor_y,rotor_size,angle,colorrotor[color_rotor]);
 
  buttonState = digitalRead(6);

  if (buttonState == LOW) {
    menuUp();
  } 
  if (digitalRead(4) == LOW) {
    switch(menuselecteditem){

      case 3:
        changecolorotor();
        while(digitalRead(4) == LOW) {
        }
      break;
      case 2:
        launchTurbo();
      break;
      case 4:
        launchSpeedometer();
      break;
    }
    
  } 
  }
  else if(global_state==1)
  {
    tft.fillCircle(120,120,17,0x0000);
  angleturbine+=4;
  if(angleturbine>60)
  {
    angleturbine=1;
  }
  drawTurbine(angleturbine,0xffff);
  delay(10);

  if(oldpressure!=pression)
  {
    angleturbine+=4;
  if(angleturbine>60)
  {
    angleturbine=1;
  }
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
  else if(global_state==2)
  {
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
}


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

void drawTurbine(int16_t angle, int16_t color)
{
  tft.drawLine(120,120,120+cos((angle*PI)/180)*15,120+sin((angle*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+60)*PI)/180)*15,120+sin(((angle+60)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+120)*PI)/180)*15,120+sin(((angle+120)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+180)*PI)/180)*15,120+sin(((angle+180)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+240)*PI)/180)*15,120+sin(((angle+240)*PI)/180)*15,color);
  tft.drawLine(120,120,120+cos(((angle+300)*PI)/180)*15,120+sin(((angle+300)*PI)/180)*15,color);
}