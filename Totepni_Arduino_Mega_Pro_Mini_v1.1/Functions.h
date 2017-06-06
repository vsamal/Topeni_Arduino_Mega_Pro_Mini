void displayInit(void)
{
  mydisp.setBgColor(0); //set another back ground color
  mydisp.setColor(WHITE); //set fore ground color, 8bit format, for 24bit color format, use:setTrueColor(R,G,B)
  mydisp.clearScreen(); //CLear screen    
}

void displayHomePage(void)
{
  mydisp.setFont(fontTemperature);
  display_Icons();
  showRooms();
  showRoomsTemp();
}

void showLog(int showlog, int fontSet = 0)
{


                   
                   if(fontSet == 99){                    
  
                        // log_reset = EEPROM.read(logAddr);
                        delay(1);
                        
                        // mydisp.setFont(0);
                        // mydisp.setColor(MAGENTA);                    
                        // mydisp.setTextPosAbs(97, 203);
                        
                        // mydisp.print("[ ");
                        // mydisp.print(log_reset);
                        // mydisp.print(" ]       ");
    
                        // mydisp.setFont(fontSet);
                        // mydisp.setColor(WHITE);

                   }else{

                        // EEPROM.write(logAddr, showlog);
                        delay(1);
                    
                   }
  
}


void showRooms(void)
{

  mydisp.setFont(fontTemperature);

  mydisp.setColor(WHITE);
  
  mydisp.setTextPosAbs(35, 22);
  mydisp.print("Kuchyn");

  mydisp.setTextPosAbs(35, 52); 
  mydisp.print("Puda");

  mydisp.setTextPosAbs(35, 82);
  mydisp.print("Obyvak");

  mydisp.setTextPosAbs(35, 112);
  mydisp.print("Loznice");

  mydisp.setTextPosAbs(35, 142);
  mydisp.print("Koupelna");

  mydisp.setTextPosAbs(35, 172);
  mydisp.print("Venku");
  
}

void mydispSetColorTemp(float teplota)
{
    if(teplota < -81){
      
       mydisp.setColor(BLUE);
       // mydisp.print(" -    ");
       
    }else if(teplota > 81){
      
       mydisp.setColor(RED);
       // mydisp.print(" -    ");
              
    }else if(teplota < 19){
      
       mydisp.setColor(CYAN);
       mydisp.print(teplota, 1);
       mydisp.print("C ");
              
    }else if(teplota < 26){
      
       mydisp.setColor(GREEN);
       mydisp.print(teplota, 1);
       mydisp.print("C ");
              
    }else{
      
       mydisp.setColor(ORANGE);
       mydisp.print(teplota, 1);
       mydisp.print("C ");       
    }

}

void showRoomsTemp()
{

  mydisp.setFont(fontTemperature);


  mydisp.setTextPosAbs(245, 22);
  mydispSetColorTemp(senzoryDS.getTempC(sensor_kuchyn));  
  
  mydisp.setTextPosAbs(245, 52);
  mydispSetColorTemp(senzoryDS.getTempC(sensor_puda));

  mydisp.setTextPosAbs(245, 82);
  mydispSetColorTemp(teplota);

  mydisp.setTextPosAbs(245, 112);
  mydispSetColorTemp(senzoryDS.getTempC(sensor_pokoj));  

  mydisp.setTextPosAbs(245, 142);
  mydispSetColorTemp(senzoryDS.getTempC(sensor_koupelna)); 
  
  mydisp.setTextPosAbs(245, 172);
  mydispSetColorTemp(senzoryDS.getTempC(sensor_venku));
  

  mydisp.setColor(YELLOW);
  
  mydisp.setTextPosAbs(165, 82);
  mydisp.print(vlhkost, 1);
  mydisp.print("%");
  
}




//explode string

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}




void readMobileStatus(String atCommand)
{
 

         mobile_data_value = "";

         Serial1.println(atCommand);
         delay(100);

         if (Serial1.available()>0)
        
          {
                while (Serial1.available()){
                                
                                sim_read = Serial1.read();
                                mobile_data_value = mobile_data_value + sim_read;
                                                                                            
                        }
                  
          }

          // Serial.print("Readed data: ");
          // Serial.println(mobile_data_value);
          
}


void getMobileStatus(void)
{
     
     readMobileStatus("AT+CREG?");
     mobile_REG = getValue(mobile_data_value, ',', 1).toInt();
     
     readMobileStatus("AT+CSQ");     
     mobile_SQ = getValue(mobile_data_value, ':', 1).toInt();
     
     readMobileStatus("AT+COPS?");
     mobile_OP = getValue(mobile_data_value, '"', 1); 
     

          
     /*          
     Serial.print("Registrace v siti: ");
     Serial.println(mobile_REG);
     Serial.print("Sila signalu: ");
     Serial.println(mobile_SQ);
     Serial.print("Operator: ");
     Serial.println(mobile_OP);             
     */
     
  
}







void showAlarm(String callnumber)
{

  mydisp.setTextPosAbs(0, 221);
  
  if(callnumber){
            
            mydisp.setFont(fontSystem);
            mydisp.setColor(RED);                          
            mydisp.print("* Alarm *");              
            mydisp.print("vytacim: ");
            mydisp.print(callnumber);            
                
    }else{
      
            mydisp.print("                                    ");
    }
  
}



// ikonky pocasi
void display_Weather(String weather, int showDay)
{

        /*
        mydisp.setColor(WHITE);
        mydisp.setTextPosAbs(0, 202);
        mydisp.print("P: ");
        mydisp.print(weather);
        mydisp.print("      ");
        */
  
  
      
          if(weather == "01d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i01d256);
           }    
      
          else if(weather == "01n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i01n256);
           }

          else if(weather == "02d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i02d256);
           }    
      
          else if(weather == "02n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i02n256);
           }

          else if(weather == "03d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i03d256);
           }    
      
          else if(weather == "03n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i03n256);
           }

          else if(weather == "04d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i04d256);
           }    
      
          else if(weather == "04n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i04n256);
           }
                        
          else if(weather == "09d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i09d256);
           }    
      
          else if(weather == "09n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i09n256);
           }

          else if(weather == "10d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i10d256);
           }    
      
          else if(weather == "10n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i10n256);
           }

          else if(weather == "11d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i11d256);
           }    
      
          else if(weather == "11n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i11n256);
           }

          else if(weather == "13d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i13d256);
           }    
      
          else if(weather == "13n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i13n256);
           }

          else if(weather == "50d"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i50d256);
           }    
      
          else if(weather == "50n"){
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i50n256);
           }
          
          else{
            mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, i01d256);
           }
 
}



void display_Icons()
{
  // mydisp.drawStr(0, 0, "Draw 256 color image");
  //draw image function have:drawBitmap() for 1bit image,drawBitmap256() for 8bit image,drawBitmap262K() for 18bit image
  //use our image convert tool to convert, www.digole.com/tools
  // mydisp.drawBitmap256(330, positionTempIcon[showDay], 64, 64, weather_sun_256);
  display_Weather("01d", 1);
  mydisp.drawBitmap256(330, 80, 64, 64, temphmeter_a_256);
  mydisp.drawBitmap256(330, 160, 64, 64, home_icon_3_256); 
  
  /*
  mydisp.drawBitmap256(0, 0, 24, 24, switch_on_r_256);
  mydisp.drawBitmap256(0, 30, 24, 24, switch_on_r_256);
  mydisp.drawBitmap256(0, 60, 24, 24, switch_on_g_256);
  mydisp.drawBitmap256(0, 90, 24, 24, switch_on_r_256);
  mydisp.drawBitmap256(0, 120, 24, 24, switch_on_bw_256);
  mydisp.drawBitmap256(0, 150, 24, 24, switch_on_g_256);  
  */
  
}




void display_Status(int sensor, byte stav)
{

  if(stav != 99){

        switch(stav) {
      
          case 0:
            mydisp.drawBitmap256(positionStatus_x[sensor], positionStatus_y[sensor], 24, 24, switch_on_bw_256);
            break;    
      
          case 1:
            mydisp.drawBitmap256(positionStatus_x[sensor], positionStatus_y[sensor], 24, 24, switch_on_g_256);
            break;
      
          default:
            mydisp.drawBitmap256(positionStatus_x[sensor], positionStatus_y[sensor], 24, 24, switch_on_r_256);
            break;
        }

  }
  
}



void setRelay(void){

      // nastavime relatka dle stavu
      set_val = 0;
      for(int i = 1; i <= 8; i++){
             digitalWrite(rele_modul[i], !rele_set[i]);
             display_Status(i, rele_set[positionStatus_pos[i]]);
      }     
  
  }


void blikLed(byte blikLed, int led_Delay = 1000){

      digitalWrite(blikLed, LOW);
      delay(led_Delay);
      digitalWrite(blikLed, HIGH);    
      delay(100);
  
  }


void setKey(int keyPress){

      switch(keyPress) {
      
          case 1:
            blikLed(led_internet_error);
            break;    
      
          case 2:
            blikLed(led_alarm);
            break;

          case 3:
            blikLed(led_fnc);
            break;    

          case 4:
            blikLed(led_pwr);
            displayOn = !displayOn;
            mydisp.screenOnOff(displayOn);            
            break;                
      
          default:
            blikLed(led_pwr);
            break;
        }     
  
  }


void clr_wdt() {

      wdt_reset();
  
}

void delayWDT(int delaysec = 30){
            clr_wdt();
       
            int waiting_call = 0;
            while(waiting_call <= delaysec){
                delay (1000);
                clr_wdt();
                waiting_call += 1;
            }            
            clr_wdt();
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
