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
#define RELE 0x2C
#define TOPENI 0xE0


#define BGCOLOR 0



#include <DigoleSerial.h>


//--------I2C setup
#if defined(_Digole_Serial_I2C_)
#include <Wire.h>
DigoleSerialDisp mydisp(&Wire, '\x27'); //I2C:Arduino UNO: SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5 on UNO and Duemilanove
#endif


void setup() {
  
  mydisp.begin(); //initiate serial port  
  Serial.begin(9600);
 


  mydisp.setBgColor(0); //set another back ground color
  mydisp.setColor(WHITE); //set fore ground color, 8bit format, for 24bit color format, use:setTrueColor(R,G,B)
  mydisp.clearScreen(); //CLear screen

  mydisp.cleanDrawWindow();   
  mydisp.backLightOn();
  mydisp.setRotation(1);



  mydisp.setFont(51); //set font to internal font:18, available internal font: 6,10,18,51,120. 200,201,202 and 203 are user font
  mydisp.setMode('C');  //set pixels operation mode as "COPY"
  
  
  mydisp.drawStr(0, 0, "Kuchyn: ");
  mydisp.drawStr(0, 1, "Obyvak: ");
  mydisp.drawStr(0, 2, "Pokoj: ");
  mydisp.drawStr(0, 3, "Puda: ");
  mydisp.drawStr(0, 4, "Venku: ");
  mydisp.drawStr(0, 5, "Ovladani: ");


  mydisp.setColor(YELLOW); 

  mydisp.drawStr(21, 0, "21.3C");
  mydisp.drawStr(21, 1, "23.7C");
  mydisp.drawStr(21, 2, "22.7C");
  mydisp.drawStr(21, 3, "19.7C");
  mydisp.drawStr(21, 4, "17.3C");
  mydisp.drawStr(21, 5, "19,3C");

  
  
}

void loop()
{
    
}
