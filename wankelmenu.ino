#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>

// Screen Pin
#define TFT_CS   10
#define TFT_DC   7
#define TFT_RST  8

Adafruit_GC9A01A tft = Adafruit_GC9A01A(TFT_CS, TFT_DC, TFT_RST);

//menu content
String menu[5] = {"G-Force","Boost","Settings","Speed","Incline"};

//The rotor angle
int angle=0;

//the rotor center
int16_t centre_rotor_x =220;
int16_t centre_rotor_y =120;

//rotor size
int16_t rotor_size = 200;


//the different color the rotor can take
int colorrotor[5] = {0xF800,0xffff,0x001F,0x07E0,0x881F};


int color_rotor = 0;
int16_t menuselecteditem = 3;
int buttonState = 0;
int global_state=0;



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

//Actualize the menu with the new order
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

//go up in the menu
void menuUp(){
  String memo = menu[0];
  for(int i=0;i<5;i++)
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
//go down in the menu
void menuDown(){
  String memo = menu[4];
  for(int i=4;i>0;i--)
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


//Draw the reuleaux traingle (the rotor)
//A lot of shitty trigonometry don't touch if you don't know what it means
void drawReuleaux(int16_t centre_x,int16_t centre_y,int16_t size,int16_t angle, int16_t color){

  int16_t internaltriglenght = (size/2)*0.866;

  //rotor sommet
  int16_t x1=(cos(((90+angle)*PI)/180)*internaltriglenght)+centre_x;
  int16_t y1=(sin(((90+angle)*PI)/180)*internaltriglenght)+centre_y;
  int16_t x2=(cos(((-30+angle)*PI)/180)*internaltriglenght)+centre_x;
  int16_t y2=(sin(((-30+angle)*PI)/180)*internaltriglenght)+centre_y;
  int16_t x3=(cos(((210+angle)*PI)/180)*internaltriglenght)+centre_x;
  int16_t y3=(sin(((210+angle)*PI)/180)*internaltriglenght)+centre_y;

  //apex seels sommet

  int16_t ap_x1=(cos(((90+angle)*PI)/180)*(internaltriglenght/1.4))+centre_x;
  int16_t ap_y1=(sin(((90+angle)*PI)/180)*(internaltriglenght/1.4))+centre_y;
  int16_t ap_x2=(cos(((-30+angle)*PI)/180)*(internaltriglenght/1.4))+centre_x;
  int16_t ap_y2=(sin(((-30+angle)*PI)/180)*(internaltriglenght/1.4))+centre_y;
  int16_t ap_x3=(cos(((210+angle)*PI)/180)*(internaltriglenght/1.4))+centre_x;
  int16_t ap_y3=(sin(((210+angle)*PI)/180)*(internaltriglenght/1.4))+centre_y;

  tft.drawCircle(ap_x1, ap_y1, size/25, color);
  tft.drawCircle(ap_x2, ap_y2, size/25, color);
  tft.drawCircle(ap_x3, ap_y3, size/25, color);

  tft.drawLine(x1, y1, (cos(((55+angle)*PI)/180)*(size*3/4))+x3, (sin(((55+angle)*PI)/180)*(size*3/4))+y3, color);
  tft.drawLine((cos(((55+angle)*PI)/180)*(size*3/4))+x3, (sin(((55+angle)*PI)/180)*(size*3/4))+y3, (cos(((45+angle)*PI)/180)*(size*3/4))+x3, (sin(((45+angle)*PI)/180)*(size*3/4))+y3, color);
  tft.drawLine((cos(((45+angle)*PI)/180)*(size*3/4))+x3, (sin(((45+angle)*PI)/180)*(size*3/4))+y3, (cos(((35+angle)*PI)/180)*(size*3/4))+x3, (sin(((35+angle)*PI)/180)*(size*3/4))+y3, color);
  tft.drawLine((cos(((35+angle)*PI)/180)*(size*3/4))+x3, (sin(((35+angle)*PI)/180)*(size*3/4))+y3, (cos(((25+angle)*PI)/180)*(size*3/4))+x3, (sin(((25+angle)*PI)/180)*(size*3/4))+y3, color);
  tft.drawLine((cos(((25+angle)*PI)/180)*(size*3/4))+x3, (sin(((25+angle)*PI)/180)*(size*3/4))+y3, (cos(((15+angle)*PI)/180)*(size*3/4))+x3, (sin(((15+angle)*PI)/180)*(size*3/4))+y3, color);
  tft.drawLine((cos(((15+angle)*PI)/180)*(size*3/4))+x3, (sin(((15+angle)*PI)/180)*(size*3/4))+y3, x2,y2, color);

  tft.drawLine(x2, y2, (cos(((-75+angle)*PI)/180)*(size*3/4))+x1, (sin(((-75+angle)*PI)/180)*(size*3/4))+y1, color);
  tft.drawLine((cos(((-75+angle)*PI)/180)*(size*3/4))+x1, (sin(((-75+angle)*PI)/180)*(size*3/4))+y1, (cos(((-85+angle)*PI)/180)*(size*3/4))+x1, (sin(((-85+angle)*PI)/180)*(size*3/4))+y1, color);
  tft.drawLine((cos(((-85+angle)*PI)/180)*(size*3/4))+x1, (sin(((-85+angle)*PI)/180)*(size*3/4))+y1, (cos(((-95+angle)*PI)/180)*(size*3/4))+x1, (sin(((-95+angle)*PI)/180)*(size*3/4))+y1, color);
  tft.drawLine((cos(((-95+angle)*PI)/180)*(size*3/4))+x1, (sin(((-95+angle)*PI)/180)*(size*3/4))+y1, (cos(((-105+angle)*PI)/180)*(size*3/4))+x1, (sin(((-105+angle)*PI)/180)*(size*3/4))+y1, color);
  tft.drawLine((cos(((-105+angle)*PI)/180)*(size*3/4))+x1, (sin(((-105+angle)*PI)/180)*(size*3/4))+y1, x3,y3, color);
  
  tft.drawLine(x3, y3, (cos(((-195+angle)*PI)/180)*(size*3/4))+x2, (sin(((-195+angle)*PI)/180)*(size*3/4))+y2, color);
  tft.drawLine((cos(((-195+angle)*PI)/180)*(size*3/4))+x2, (sin(((-195+angle)*PI)/180)*(size*3/4))+y2, (cos(((-205+angle)*PI)/180)*(size*3/4))+x2, (sin(((-205+angle)*PI)/180)*(size*3/4))+y2, color);
  tft.drawLine((cos(((-205+angle)*PI)/180)*(size*3/4))+x2, (sin(((-205+angle)*PI)/180)*(size*3/4))+y2, (cos(((-215+angle)*PI)/180)*(size*3/4))+x2, (sin(((-215+angle)*PI)/180)*(size*3/4))+y2, color);
  tft.drawLine((cos(((-215+angle)*PI)/180)*(size*3/4))+x2, (sin(((-215+angle)*PI)/180)*(size*3/4))+y2, (cos(((-225+angle)*PI)/180)*(size*3/4))+x2, (sin(((-225+angle)*PI)/180)*(size*3/4))+y2, color);
  tft.drawLine((cos(((-225+angle)*PI)/180)*(size*3/4))+x2, (sin(((-225+angle)*PI)/180)*(size*3/4))+y2, x1,y1, color);
  
}

//change the color of the rotor
void changecolorotor(){
  color_rotor++;
    if(color_rotor>4)
  { 
  color_rotor=0;
  }

  tft.drawCircle(centre_rotor_x, centre_rotor_y, rotor_size/6, colorrotor[color_rotor]);
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

    }
    
  } 
  }
}