/*********************
   http://www.digole.com/forum   communicate with us and other user
   http://www.digole.com    buyer Digole module
   This sample sketch is used to test new functions in V3.0 firmware:
   setBgColor----set background color
   setDrawWindow----set the drawing window
   resetDrawWindow--reset the drawing window to default
 **********************/


//You have to change the following setting according to the Digole display

#define LCDWidth 240  //define screen width,height
#define LCDHeight 400
#define _Digole_Serial_I2C_  //To tell compiler compile the special communication only, 
//#define TOUCH_SCEEN   //if the module equipt with touch screen, use this, otherwise use // to disable it
//#define FLASH_CHIP    //if the module equipt with 2MB or 4MB flash chip, use it, otherwise  use // to disable it
#define Ver 34           //if the version of firmware on display is V3.3 and newer, use this
//all available are:_Digole_Serial_UART_, _Digole_Serial_I2C_ and _Digole_Serial_SPI_
//#define MONO  //if the screen panel is monochrome

//end changing

//define 8 bit color, see:https://en.wikipedia.org/wiki/8-bit_color  or https://jonasjacek.github.io/colors/
#define WHITE 0xFF
#define BLACK 0
#define RED 0xE0
#define GREEN 0x1C
#define BLUE 0x03
#define YELLOW 0xFE
#define ORANGE 0xEC
#define MAGENTA 0xEB
#define CYAN 0x1B
#define BROWN 0xAC
#define RAMECEK 0xFB
#define RELE 0x10
#define TOPENI 0x60


#define BGCOLOR 0


byte fonts_list[9] = {6, 10, 18, 51, 120 , 200, 201, 202, 203};

// barvy tlacitek
byte btn_c[13] = {0, RELE, RELE, RELE, RELE, TOPENI, TOPENI, TOPENI, TOPENI, GREEN, YELLOW, MAGENTA, CYAN}; 
// sloupec textu tlacitka
int* btn_x[13] = {0, 20, 120, 220, 320, 20, 120, 220, 320, 20, 120, 220, 320};
// radka textu tlacitka
int* btn_y[13] = {0, 15, 15, 15, 15, 3, 3, 3, 3, 5, 5, 5, 5};


#include <DigoleSerial.h>


//--------I2C setup
#if defined(_Digole_Serial_I2C_)
#include <Wire.h>
DigoleSerialDisp mydisp(&Wire, '\x27'); //I2C:Arduino UNO: SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5 on UNO and Duemilanove
#endif

// #include "Demo_Data.h" //include images and fonts

void delay1(void) //for demo use, reset display position and clean the demo line
{
  delay(1500); //delay 1.5 seconds
  mydisp.setColor(WHITE);
}
void setup() {
  
  mydisp.begin(); //initiate serial port  
  Serial.begin(9600);
  
  //mydisp.setSPIMode(0); //set SPI mode in V3.4, the available mode are 0,1,2,3
  //  mydisp.displayConfig(1);
  //  mydisp.enableCursor(); //disable cursor, enable cursore use: enableCursor();
  /*-----drawing functions  -----*/
  mydisp.setBgColor(0); //set another back ground color
  mydisp.setColor(WHITE); //set fore ground color, 8bit format, for 24bit color format, use:setTrueColor(R,G,B)
  mydisp.clearScreen(); //CLear screen
//display string, \n move cursor to next line,\r move cursor the beginning of current line
  //mydisp.print("Clear screen,\nNext Line.\r-Return-\n\rNew Line...");

/*
        for (int i = 0; i < 9; i++) {
                // mydisp.cleanDrawWindow();
                mydisp.setFont(fonts_list[i]);
                mydisp.print("setFont ");
                mydisp.print(fonts_list[i]);
                mydisp.print("\n\r");
                delay1();
        }
*/


  mydisp.cleanDrawWindow();   
  mydisp.backLightOn();
  mydisp.setRotation(1);

/*

  mydisp.setFont(120); //set font to internal font:18, available internal font: 6,10,18,51,120. 200,201,202 and 203 are user font
  mydisp.setMode('C'); 
  
  mydisp.setPrintPos(0, 0 ,0);
  mydisp.setTextPosOffset(20, 15);
  mydisp.print("A");

  mydisp.setPrintPos(0, 0 ,0);
  mydisp.setTextPosOffset(120, 15);
  mydisp.print("B");

  mydisp.setPrintPos(0, 0 ,0);
  mydisp.setTextPosOffset(120, 15);
  mydisp.setTextPosOffset(100, 0);
  mydisp.print("C"); 

  mydisp.setPrintPos(0, 0 ,0);
  mydisp.setTextPosOffset(120, 15);
  mydisp.setTextPosOffset(100, 0);
  mydisp.setTextPosOffset(100, 0);
  mydisp.print("D"); 
  
  delay(100000);

*/


  mydisp.setFont(18); //set font to internal font:18, available internal font: 6,10,18,51,120. 200,201,202 and 203 are user font
  mydisp.setMode('C');  //set pixels operation mode as "COPY"
  
  
  mydisp.drawStr(30, 11, "drawStr line 1");
  mydisp.drawStr(30, 12, "drawStr line 2");
  mydisp.drawStr(30, 13, "drawStr line 3");
  delay1();

  drawRamecek(0,0,98,71, RAMECEK, RELE);
  drawRamecek(100,0,98,71, RAMECEK, RELE);
  drawRamecek(200,0,98,71, RAMECEK, RELE);
  drawRamecek(300,0,98,71, RAMECEK, RELE);
  

  delay1();
  // mydisp.setPrintPos(30,70,0);

  textRamecek(1, "11.1");
  textRamecek(2, "22.2");
  textRamecek(3, "33.3");
  textRamecek(4, "44.4");

  delay1();
  
}

void loop()
{
    
}


 void drawRamecek(int pos_x, int pos_y, int pos_w, int pos_h, byte c, byte f){
        mydisp.setColor(RAMECEK);
        mydisp.drawFrame(pos_x, pos_y, pos_w, pos_h);
        mydisp.setColor(RELE);
        pos_x = pos_x + 1;
        pos_y = pos_y + 1;
        pos_w = pos_w - 2;
        pos_h = pos_h - 2;
        mydisp.drawBox(pos_x, pos_y, pos_w, pos_h);  
  } 


 void textRamecek(int btn, char* temperature){
        mydisp.setColor(WHITE);
        mydisp.setBgColor(btn_c[btn]);
        mydisp.setFont(120); //set font to internal font:18, available internal font: 6,10,18,51,120. 200,201,202 and 203 are user font
        mydisp.setMode('C');
        // mydisp.drawStr(btn_x[btn], btn_y[btn], temperature);  
        //mydisp.setPrintPos(btn_x[btn], btn_y[btn],0);
        setPos(btn);
        mydisp.print(temperature);
  }


  void setPos(int btn){
          mydisp.setPrintPos(0, 0 ,0);
          
          int pos_set = 0;
          while(btn_x[btn] > 0){
              
              pos_set = btn_x[btn] - 127;
              if(pos_set > 0){
                mydisp.setTextPosOffset(127, 0); 
                Serial.println(127);             
              }else{
                mydisp.setTextPosOffset(btn_x[btn], 0);
                Serial.println(pos_set);  
              }
              btn_x[btn] = pos_set;
              
            }

            
    }


