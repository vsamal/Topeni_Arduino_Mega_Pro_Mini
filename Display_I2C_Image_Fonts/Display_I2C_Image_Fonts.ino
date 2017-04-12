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


byte fonts_list[9] = {6, 10, 18, 51, 120 , 200, 201, 202, 203};


#include <DigoleSerial.h>


//--------I2C setup
#if defined(_Digole_Serial_I2C_)
#include <Wire.h>
DigoleSerialDisp mydisp(&Wire, '\x27'); //I2C:Arduino UNO: SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5 on UNO and Duemilanove
#endif

#include "Demo_Data.h" //include images and fonts

void display_8bit_Image(void);
void test_User_Font_Standard(void);
void use_User_Font_In_Flash_Chip(void);


void setup() {
  
  mydisp.begin(); //initiate serial port  
  Serial.begin(9600);
  

  mydisp.setBgColor(0); //set another back ground color
  mydisp.setColor(WHITE); //set fore ground color, 8bit format, for 24bit color format, use:setTrueColor(R,G,B)
  mydisp.clearScreen(); //CLear screen

  delay(700);
  
  mydisp.setRotation(1);

  

  // test_User_Font_Standard();
  // delay(17000);

  // use_User_Font_In_Flash_Chip(); 
  // delay(17000);

  /*
   
        for (int i = 0; i < 9; i++) {
                // mydisp.cleanDrawWindow();
                mydisp.setFont(fonts_list[i]);
                mydisp.print("setFont ");
                mydisp.print(fonts_list[i]);
                mydisp.print("\n\r");
                delay(1000);
        }

  */

  display_8bit_Image();

  mydisp.setFont(200);
  
  mydisp.setTextPosAbs(35, 22);  //set text position as pixels  
  mydisp.print("Kuchyn"); //dispear the last motion

  mydisp.setTextPosAbs(35, 52);  //set text position as pixels  
  mydisp.print("Obyvak"); //dispear the last motion

  mydisp.setTextPosAbs(35, 82);  //set text position as pixels  
  mydisp.print("Pokoj"); //dispear the last motion   

  mydisp.setTextPosAbs(35, 112);  //set text position as pixels  
  mydisp.print("Koupelna"); //dispear the last motion

  mydisp.setTextPosAbs(35, 142);  //set text position as pixels  
  mydisp.print("Puda"); //dispear the last motion

  mydisp.setTextPosAbs(35, 172);  //set text position as pixels  
  mydisp.print("Venku"); //dispear the last motion     



  mydisp.setColor(YELLOW);
  
  mydisp.setTextPosAbs(245, 22);  //set text position as pixels  
  mydisp.print("21.9C"); //dispear the last motion

  mydisp.setTextPosAbs(245, 52);  //set text position as pixels  
  mydisp.print("23.1C"); //dispear the last motion

  mydisp.setTextPosAbs(245, 82);  //set text position as pixels  
  mydisp.print("20.1C"); //dispear the last motion   

  mydisp.setTextPosAbs(245, 112);  //set text position as pixels  
  mydisp.print("21.4C"); //dispear the last motion

  mydisp.setTextPosAbs(245, 142);  //set text position as pixels  
  mydisp.print("21.1C"); //dispear the last motion

  mydisp.setTextPosAbs(245, 172);  //set text position as pixels  
  mydisp.print("15.9C"); //dispear the last motion     

  mydisp.setColor(CYAN);
  
  mydisp.setTextPosAbs(165, 52);  //set text position as pixels  
  mydisp.print("100%"); //dispear the last motion

  
}

void loop()
{
    
}

void display_8bit_Image(void)
{
  // mydisp.drawStr(0, 0, "Draw 256 color image");
  //draw image function have:drawBitmap() for 1bit image,drawBitmap256() for 8bit image,drawBitmap262K() for 18bit image
  //use our image convert tool to convert, www.digole.com/tools
  mydisp.drawBitmap256(330, 0, 64, 64, weather_sun_256);
  mydisp.drawBitmap256(330, 80, 64, 64, temphmeter_a_256);
  mydisp.drawBitmap256(330, 160, 64, 64, home_icon_3_256  ); 
  mydisp.drawBitmap256(0, 0, 24, 24, switch_on_r_256);
  mydisp.drawBitmap256(0, 30, 24, 24, switch_on_r_256);
  mydisp.drawBitmap256(0, 60, 24, 24, switch_on_g_256);
  mydisp.drawBitmap256(0, 90, 24, 24, switch_on_r_256);
  mydisp.drawBitmap256(0, 120, 24, 24, switch_on_bw_256);
  mydisp.drawBitmap256(0, 150, 24, 24, switch_on_g_256);  
  
}


void test_User_Font_Standard(void)
{
  mydisp.setFont(0);

  mydisp.setTextPosAbs(10, 11);  //set text position as pixels  
  mydisp.setFont(0);
  mydisp.print("Upload Font 1"); //dispear the last motion
  
  // mydisp.downloadUserFont(sizeof(mujfont3), mujfont3, 0); //download a user font: (font length, font address, #userfont), one time download needed
  mydisp.setFont(200);  //user #1 user font, there are 4 user fonts can be used:200 ~ 203
  
  mydisp.setTextPosAbs(10, 47);  //set text position as pixels  
  mydisp.print("Ahoj, jak se vede? 200"); //dispear the last motion
  
  mydisp.setFont(0);
  
  mydisp.setTextPosAbs(197, 11);  //set text position as pixels  
  mydisp.print("Upload Font 2"); //dispear the last motion
  
  // mydisp.downloadUserFont(sizeof(mujfont), mujfont, 1); //download a user font: (font length, font address, #userfont), one time download needed
  mydisp.setFont(201);  //user #1 user font, there are 4 user fonts can be used:200 ~ 203
  
  mydisp.setTextPosAbs(10, 77);  //set text position as pixels  
  mydisp.print("Ahoj, jak se vede? 201"); //dispear the last motion

  
  mydisp.setTextPosAbs(10, 107);  //set text position as pixels  
  mydisp.setFont(0);
  mydisp.print("Upload Font 3"); //dispear the last motion
  
  // mydisp.downloadUserFont(sizeof(mujfont2), mujfont2, 2); //download a user font: (font length, font address, #userfont), one time download needed
  mydisp.setFont(202);  //user #1 user font, there are 4 user fonts can be used:200 ~ 203
  
  mydisp.setTextPosAbs(10, 147);  //set text position as pixels  
  mydisp.print("Ahoj, jak se vede?"); //dispear the last motion


  mydisp.setFont(0);
  
  // mydisp.setFont(0);
  // mydisp.setTextPosAbs(170, 11);  //set text position as pixels  
  // mydisp.print("Done :)"); //dispear the last motion
    
}


void use_User_Font_In_Flash_Chip(void)
{
  mydisp.setFont(0);
  mydisp.setTextPosAbs(10, 157);  //set text position as pixels  
  mydisp.print("Download user font in flash chip and use it");
  
  
  
  //mydisp.flashErase(600000, sizeof(mujfont3)); //erase 8588 bytes in flash to store font data, this function will use screen memory to buffer the 4096 erase block
  //delay(400);
  //mydisp.flashWrite(600000, sizeof(mujfont3), mujfont3);  //write array d to flash memory start at 0, length=8588

  // u8g_font_fur20r, u8g_font_fub25r, u8g_font_fur20c
  
  
  
  
  mydisp.setFlashFont(600000);  //use user font in flash chip from any address
  mydisp.setTextPosAbs(10, 177);  //set text position as pixels  
  mydisp.print("Ahoj, jak se vede?"); //dispear the last motion
  mydisp.setFont(0);
  
}

