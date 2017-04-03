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

//define 8 bit color, see:https://en.wikipedia.org/wiki/8-bit_color
#define WHITE 0xFF
#define BLACK 0
#define RED 0xE0
#define GREEN 0x1A
#define BLUE 0x03

#define BGCOLOR 0



#define basex 25
#define basey 25
#define R 20

#include <DigoleSerial.h>


//--------I2C setup
#if defined(_Digole_Serial_I2C_)
#include <Wire.h>
DigoleSerialDisp mydisp(&Wire, '\x27'); //I2C:Arduino UNO: SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5 on UNO and Duemilanove
#endif

#include "Demo_Data.h" //include images and fonts



void delay1(void) //for demo use, reset display position and clean the demo line
{
  delay(1500); //delay 1.5 seconds
  mydisp.setColor(WHITE);
}
void setup() {
  mydisp.begin(); //initiate serial port
  //mydisp.setSPIMode(0); //set SPI mode in V3.4, the available mode are 0,1,2,3
  //  mydisp.displayConfig(1);
  //  mydisp.enableCursor(); //disable cursor, enable cursore use: enableCursor();
  /*-----drawing functions  -----*/
  mydisp.setBgColor(0); //set another back ground color
  mydisp.setColor(WHITE); //set fore ground color, 8bit format, for 24bit color format, use:setTrueColor(R,G,B)
  mydisp.clearScreen(); //CLear screen
//display string, \n move cursor to next line,\r move cursor the beginning of current line
  mydisp.print("Clear screen,\nNext Line.\r-Return-\n\rNew Line...");


  delay1();
  mydisp.cleanDrawWindow();

    
  mydisp.backLightOn();
  mydisp.drawStr(0, 0, "Backlight is on now");
  delay1();
  //mydisp.cleanDrawWindow();

  mydisp.setRotation(1);
  mydisp.setFont(18); //set font to internal font:18, available internal font: 6,10,18,51,120. 200,201,202 and 203 are user font
  mydisp.setMode('C');  //set pixels operation mode as "COPY"
  
  mydisp.drawStr(0, 10, "Turn screen off");
  delay1();
}

void loop()
{
}

