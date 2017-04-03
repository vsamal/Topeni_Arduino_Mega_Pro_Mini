/*
  https://arduino-info.wikispaces.com/Ethernet

rele 1 - A0, A2, A4, A6
key 1  - A1, A3, A5, A7

rele 2 - A9, A11, A13, A15
key 2  - A8, A10, A12, A14

led 3  - 32, 34, 36, 38
key 3  - 33, 35, 37, 39

KeypadPin 1 - 41
KeypadPin 2 - 43

RecieverData   - 2
TransmiterData - 11, 12

OneWireData - 7

SIM - Serial1
SIM RST - 28
ALARM   - 29
BoardPin 1 - 30
BoardPin 2 - 31


*/


// #include "SPI.h"

// #include "Wire.h"
#include "OneWire.h"
#include "Ethernet.h"
#include "LiquidCrystal_I2C.h"
#include "SoftwareSerial.h"
#include "DallasTemperature.h"
#include "AM2320.h"
//#include "avr/wdt.h"


#define LCDWidth 240  //define screen width,height
#define LCDHeight 400
#define _Digole_Serial_I2C_  //To tell compiler compile the special communication only, 
#define TOUCH_SCEEN   //if the module equipt with touch screen, use this, otherwise use // to disable it
#define FLASH_CHIP    //if the module equipt with 2MB or 4MB flash chip, use it, otherwise  use // to disable it
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
//define draw window
#define DW_X 5
#define DW_Y 8
#define DW_W (LCDWidth - 10)
#define DW_H (LCDHeight - 15)
#ifdef MONO
#define COLORRG 2
#define BGCOLOR 1
#else
#define BGCOLOR 256
#define COLORRG 256
#endif

#define basex 25
#define basey 25
#define R 20

#include "DigoleSerial.h"

#include "Wire.h"
DigoleSerialDisp mydisp(&Wire, '\x27'); //I2C:Arduino UNO: SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5 on UNO and Duemilanove

#include "Demo_Data.h" //include images and fonts


// definice cidla teplota a vlhkost
AM2320 th;

float teplota;
float vlhkost;


// tlacitka vstupu
byte tlacitko_modul[9] = {99, A1, A3, A5, A7, A8, A10, A12, A14};
byte tlacitko_modul_b[5] = {99, 33, 35, 37, 39};
// pamet rele vystupu
byte rele_modul[9] = {99, A0, A2, A4, A6, A9, A11, A13, A15};

// detekce alarmu
byte SIM_reset = 28;
byte alarm = 29;
boolean is_alarm = false;
byte led_alarm = 34;
byte led_internet_error = 32;
byte led_pwr = 36;
byte led_fnc = 38;

char sim_read;

// nastavení čísla vstupního pinu
const int pinCidlaDS = 7;
// vytvoření instance oneWireDS z knihovny OneWire
OneWire oneWireDS(pinCidlaDS);
// vytvoření instance senzoryDS z knihovny DallasTemperature
DallasTemperature senzoryDS(&oneWireDS);



EthernetClient client;
// Ethernet PINs 10, 11, 12, 13
signed long next;
byte page_cnt;
int next_sd;  
int next_wd;
int data_read;
int set_val;
char read_buffer;
boolean nalez = false;

// the dns server ip
IPAddress dnServer(193, 85, 1, 12);
// the router's gateway address:
IPAddress gateway(192, 168, 1, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
//the IP address is dependent on your network
IPAddress ip(192, 168, 1, 15);

/*
// --- Dneboh ---
// the dns server ip
IPAddress dnServer(10, 20, 30, 1);
// the router's gateway address:
IPAddress gateway(10, 20, 30, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
//the IP address is dependent on your network
IPAddress ip(10, 20, 30, 21);
*/


// byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05}; 
char server[] = "www.ipf.cz"; //server, kam se pripojujeme




void setup()   {                

  // wdt_enable(WDTO_8S);
  
  Wire.begin();  
  Serial.begin(9600);
  Serial1.begin(9600); 

  // zapnutí komunikace knihovny s Dallas teplotním čidlem
  senzoryDS.begin();

  
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor ( 0, 0 );
  lcd.print("Hello, world!");  

  // tlacitka relatek jako vstupy s pull up odporem na vstupu
  for(int i = 1; i <= 8; i++){
        pinMode(tlacitko_modul[i], INPUT_PULLUP);
  }

  // tlacitka funkcí jako vstupy s pull up odporem na vstupu
  for(int i = 1; i <= 4; i++){
        pinMode(tlacitko_modul_b[i], INPUT_PULLUP);
  }

  // rele jako vstupy na nastavime HIGH jako vypnute vstupy
  for(int i = 1; i <= 8; i++){
        pinMode(rele_modul[i], OUTPUT);
        digitalWrite(rele_modul[i], HIGH);
  }

  // vstup z alarmu    
  pinMode(alarm, INPUT_PULLUP);

  // kontrolka ze nejede internet
  pinMode(led_internet_error, OUTPUT);
  digitalWrite(led_internet_error, HIGH);

  // kontrolka ze je alarb
  pinMode(led_alarm, OUTPUT);
  digitalWrite(led_alarm, HIGH);

  // kontrolka power
  pinMode(led_pwr, OUTPUT);
  digitalWrite(led_pwr, LOW);

  // kontrolka fnc
  pinMode(led_fnc, OUTPUT);
  digitalWrite(led_fnc, HIGH);


  // reset SIM
  pinMode(SIM_reset, OUTPUT);
  digitalWrite(SIM_reset, LOW);
  delay(200)
  digitalWrite(SIM_reset, HIGH);


  Ethernet.begin(mac, ip, dnServer, gateway, subnet);


  // MCP23016 I/O expander configure
  Wire.begin(); // connect the Arduino as a master 
  Wire.beginTransmission(0x20); // setup out direction registers 
  Wire.write(0x06); // pointer  
  Wire.write(0x00); // DDR Port0 all output 
  Wire.write(0x00); // DDR Port1 all input 0xFF = B11111111   
  Wire.endTransmission();     


  // strankovac displeje
  page_cnt = 1;
  
  // info casovac dalsiho precteni dat z webu
  next = 0;

  

}


void loop() {
  
  // --------- tepomery ----------
  senzoryDS.requestTemperatures();
  readTemp();
  // read_data_topeni();


  /*
  showtext("Kuchyn + K", "teplota", 16);
  showtext("Pokoj puda", "teplota", 20);
  showtext("Obyvak", "teplota", 22);
  showtext("Loznice", "teplota", 24);
  showtext("Venku", "teplota", 22);
  */


 
  next_sd++;
  
  if (next_sd > 5){  

        next_sd = 0;
  
        if(page_cnt == 1){
                  
                  lcd.clear();
                  lcd.setCursor ( 0, 0 );
                  lcd.print("Kuchyn + Koup.");
                  lcd.setCursor ( 16, 0 );  
                  lcd.print(teplota, 1);
                  // lcd.print(vlhkost);    
                
                  lcd.setCursor ( 0, 1 );
                  lcd.print("Pokoj puda ");
                  lcd.setCursor ( 16, 1 ); 
                  lcd.print(senzoryDS.getTempCByIndex(0), 1);
          
                  lcd.setCursor ( 0, 2 );
                  lcd.print("Obyvak ");  
                  lcd.setCursor ( 16, 2 );
                  lcd.print(senzoryDS.getTempCByIndex(1), 1);
          
                  lcd.setCursor ( 0, 3 );
                  lcd.print("Loznice ");
                  lcd.setCursor ( 16, 3 ); 
                  lcd.print(senzoryDS.getTempCByIndex(2), 1);
          
                  // lcd.setCursor ( 0, 4 );
                  // lcd.print("Venku: ");  
                  // lcd.print(senzoryDS.getTempCByIndex(1));
          
                  page_cnt++;
                  
        }else if(page_cnt == 2){

                  lcd.clear();
                  lcd.setCursor ( 0, 0 );
                  lcd.print("Kuchyn + Koupelna");
                  lcd.setCursor ( 0, 1 );
                  lcd.print("Vlhkost ");                  
                  lcd.setCursor ( 14, 1 );  
                  lcd.print(vlhkost); 
                  lcd.print("%");   
                
                  lcd.setCursor ( 0, 3 );
                  lcd.print("Teplota venku");
                  lcd.setCursor ( 16, 3 ); 
                  lcd.print(senzoryDS.getTempCByIndex(2), 1);
                    
                  page_cnt = 1;
          
        }
              
        delay(100);
        
        clr_wdt();
        
  }


  // ----------- tlacitka a alarm a Internet ----------


   // zkontrolujeme alarm 
  // Serial.println("Test alarm");  
  if(digitalRead(alarm) == LOW){
             delay(300);
             if(digitalRead(alarm) == LOW){
                if(is_alarm == false){
                        digitalWrite(led_alarm, LOW);
                        setAlarm();
                  }
                is_alarm = true;
             }else{
                is_alarm = false;
             }
        }else{
             is_alarm = false;
        }  
    // Serial.println("OK");  






    // projedeme si stisknuta tlacitka
    // Serial.println("Test key");  
    for(int i = 1; i <= 8; i++){
          if(digitalRead(tlacitko_modul[i]) == LOW){
            Serial.println(i); //vypise stisknute tlacitko
            next_sd = 999;
            setRelayFromKey(i);
          }
          delay(1);
    }
    // Serial.println("OK");  



  // obcas precteme nastaveni z internetu
  // Serial.println("Test internet");  
  if (((signed long)(millis() - next)) > 0){
      
        Serial.println("Read internet ready");  
        next = millis() + 11000;        

        read_data_topeni(0); // precteme data z intenetu
        
  }
  // Serial.println("Test internet OK");  



  // nastavime relatka dle stavu
    set_val = 0;
    for(int i = 1; i <= 8; i++){
           digitalWrite(rele_modul[i], tlacitko_modul[i]);
    } 
               

}









void readTemp() {
  switch(th.Read()) {
    case 2:
      teplota = 99;
      break;
    case 1:
      teplota = -99;
      break;
    case 0:
      vlhkost = th.h;
      teplota = th.t;
      break;
  }

  delay(10); // 200
  clr_wdt();
}


void clr_wdt() {

      // wdt_reset();
  
}


void read_data_topeni(int send_relay) {

      
      clr_wdt();

      digitalWrite(led_internet_error, LOW);

      Serial.print("Connect to ");
      Serial.println(server);

      
      if (client.connect(server,80)){

          Serial.println("Connected");

          // digitalWrite(, LOW);
          clr_wdt();
          
          String myURL = "GET /topeni/topeni.php?relay=";
          client.print(myURL);
          client.print(send_relay);
          client.print("&status=");
                  
                if (rele_modul[send_relay] == 0){client.print(0);}
                if (rele_modul[send_relay] == 1){client.print(1);}               
          
          client.print("&temp[1]=");
          client.print(teplota);
          client.print("&humid[1]=");
          client.print(vlhkost);
          client.print("&temp[2]=");
          client.print(senzoryDS.getTempCByIndex(0));
          client.print("&temp[3]=");
          client.print(senzoryDS.getTempCByIndex(1));
          client.print("&temp[4]=");
          client.print(senzoryDS.getTempCByIndex(2));
          client.print("&temp[5]=");
          client.print(senzoryDS.getTempCByIndex(1));
          
          client.println(" HTTP/1.0");
          client.print("Host: ");
          client.println(server);
          client.println("Connection: close");
          client.println();

          Serial.print(myURL);
          Serial.print(send_relay);
          Serial.print("&status=");
          Serial.println(rele_modul[send_relay]);

          nalez = false;
          byte relec = 1;        
          delay(1);
          

          // precteni dat z internetu
                    
          while(client.connected()) {
            if(client.available()) {
                char read_buffer = client.read();
     
                
                if (read_buffer == '>'){nalez = false;}
                 
                if (nalez){

                  digitalWrite(led_internet_error, HIGH);
                  // Serial.print(read_buffer); //vypise prijata data
                  // na tohle mozna udelame funkci  
                  if (read_buffer == '0'){rele_modul[relec] = 0;}
                  if (read_buffer == '1'){rele_modul[relec] = 1;}
                  relec++;                  

                }
  
                if (read_buffer == '<'){nalez = true;}
                         
            }
          }
        
    
         //Serial.println();
         //Serial.println("Odpojuji.");
         delay(1);
         client.flush();
         delay(1);
         //Serial.println();
         client.stop();   
         
       }else{
        
        //Serial.println("Connect failed");

        digitalWrite(led_internet_error, LOW);

        clr_wdt();

       }
 
    Serial.println("Internet OK");  
    clr_wdt();
}









// nastavi rele a zapise na internet
void setRelayFromKey(int tlac_press){

            Serial.print("Ctu stav rele ");
            Serial.print(tlac_press);
            Serial.print(" ten je nastaven na ");
            Serial.println(rele_modul[tlac_press]);            

            // na tohle mozna udelame funkci  
            // rele nastavime
            rele_modul[tlac_press] = !rele_modul[tlac_press];

            
            Serial.print("Tlacitko ");
            Serial.print(tlac_press);
            Serial.print(" stlaceno, rele vstup ");
            Serial.print(rele_modul[tlac_press]);
            Serial.println(" nastaveno");
            
            read_data_topeni(tlac_press);
            
            // delay(1000);
            clr_wdt();
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



// alarm zavola na mobil
void setAlarm(){
            Serial.println("Alarm");                   
            
            //makeCall("604833891");
            //makeCall("605906254");
            makeCall("737226659");
            //sendSMS("737226659");
            //makeCall("737226659");

            digitalWrite(led_alarm, HIGH);
            
}



void makeCall(String callnumber){

            lcd.clear();
            lcd.setCursor ( 3, 0 );
            lcd.print("*** Alarm ***");
            lcd.setCursor ( 4, 1 );  
            lcd.print("Volam cislo:");
            lcd.setCursor ( 6, 2 );
            lcd.print(callnumber);            

            clr_wdt();
            
            Serial1.print("ATD");
            Serial1.print(callnumber);
            Serial1.println(";");
            delay(100);            
             
            if(Serial1.available()){
                  lcd.setCursor ( 5, 3 );
                  lcd.print("vytacim...");
                  while (Serial1.available()){
                  sim_read = Serial1.read();
                    Serial.print(sim_read);
                  }
            }else{
                  lcd.setCursor ( 3, 3 );
                  lcd.print("nedostupny...");                    
            }
        
            delayWDT(29);
                       
            Serial1.println("ATH");                      
            delay (1000);
            clr_wdt();
}


/*


void sendSMS(char smsnumber[]){
          Serial1.println("AT+CMGF=1");  // AT command na odeslani SMS zpravy
          delay(100);
          Serial1.print("AT+CMGS=\"");  // cislo prijemce
          Serial1.print(smsnumber);  // cislo prijemce
          Serial1.println("\"");  // cislo prijemce
          delay(100);
          Serial1.println("Alarm send.");  // zprava k odeslani
          Serial1.print("Status: ");  // zprava k odeslani
          Serial1.print(rele_modul[1]);  // zprava k odeslani
          Serial1.print(rele_modul[2]);  // zprava k odeslani
          Serial1.print(rele_modul[3]);  // zprava k odeslani
          Serial1.println(rele_modul[4]);  // zprava k odeslani
          Serial1.print(" is set.");  // zprava k odeslani
          delay(100);
          Serial1.println((char)26);  //  AT command znak a ^Z, ASCII code 26 pro konec SMS zpravy
          delay(100); 
          Serial1.println();
          delayWDT(11);  // pokej na odesln SMS
          //Serial1power();  // vypni GSM module
          clr_wdt();
        }

*/

