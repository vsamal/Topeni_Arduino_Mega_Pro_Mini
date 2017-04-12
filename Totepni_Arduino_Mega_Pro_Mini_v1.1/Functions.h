void showRooms(void)
{

  mydisp.setFont(200);
  
  mydisp.setTextPosAbs(35, 22);
  mydisp.print("Kuchyn");

  mydisp.setTextPosAbs(35, 52); 
  mydisp.print("Obyvak");

  mydisp.setTextPosAbs(35, 82);
  mydisp.print("Pokoj");

  mydisp.setTextPosAbs(35, 112);
  mydisp.print("Koupelna");

  mydisp.setTextPosAbs(35, 142);
  mydisp.print("Puda");

  mydisp.setTextPosAbs(35, 172);
  mydisp.print("Venku");
  
}

void showRoomsTemp(void)
{

  mydisp.setFont(200);

  mydisp.setColor(YELLOW);
  
  mydisp.setTextPosAbs(245, 22);
  mydisp.print(senzoryDS.getTempCByIndex(0), 1);
  mydisp.print("C");

  mydisp.setTextPosAbs(245, 52);
  mydisp.print(teplota, 1);
  mydisp.print("C");

  mydisp.setTextPosAbs(245, 82);
  mydisp.print(senzoryDS.getTempCByIndex(0), 1);
  mydisp.print("C");

  mydisp.setTextPosAbs(245, 112);
  mydisp.print(senzoryDS.getTempCByIndex(0), 1);
  mydisp.print("C");

  mydisp.setTextPosAbs(245, 142);
  mydisp.print(senzoryDS.getTempCByIndex(0), 1);
  mydisp.print("C");

  mydisp.setTextPosAbs(245, 172);
  mydisp.print(senzoryDS.getTempCByIndex(0), 1);
  mydisp.print("C");

  mydisp.setColor(CYAN);
  
  mydisp.setTextPosAbs(165, 52);
  mydisp.print(vlhkost, 1);
  mydisp.print("%");
  
}

void showAlarm(String callnumber)
{

  mydisp.setTextPosAbs(0, 221);
  
  if(callnumber){
            
            mydisp.setFont(0);
            mydisp.setColor(RED);                          
            mydisp.print("*** Alarm ***");              
            mydisp.print("Volam cislo: ");
            mydisp.print(callnumber);            
                
    }else{
      
            mydisp.print("                                    ");
    }
  
}



void display_Icons(void)
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


void use_User_Font_Standard(void)
{
  mydisp.setFont(0);

  mydisp.setTextPosAbs(10, 11);  //set text position as pixels  
  mydisp.setFont(0);
  mydisp.print("Upload Font 1"); //dispear the last motion
  
  mydisp.downloadUserFont(sizeof(mujfont3), mujfont3, 0); //download a user font: (font length, font address, #userfont), one time download needed
  mydisp.setFont(200);  //user #1 user font, there are 4 user fonts can be used:200 ~ 203
  
  mydisp.setTextPosAbs(10, 47);  //set text position as pixels  
  mydisp.print("Ahoj, jak se vede? 200"); //dispear the last motion
  
  mydisp.setFont(0);
  
  mydisp.setTextPosAbs(197, 11);  //set text position as pixels  
  mydisp.print("Upload Font 2"); //dispear the last motion
  
  mydisp.downloadUserFont(sizeof(mujfont), mujfont, 1); //download a user font: (font length, font address, #userfont), one time download needed
  mydisp.setFont(201);  //user #1 user font, there are 4 user fonts can be used:200 ~ 203
  
  mydisp.setTextPosAbs(10, 77);  //set text position as pixels  
  mydisp.print("Ahoj, jak se vede? 201"); //dispear the last motion

  
  mydisp.setTextPosAbs(10, 107);  //set text position as pixels  
  mydisp.setFont(0);
  mydisp.print("Upload Font 3"); //dispear the last motion
  
  mydisp.downloadUserFont(sizeof(mujfont2), mujfont2, 2); //download a user font: (font length, font address, #userfont), one time download needed
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
