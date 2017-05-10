/*
  https://arduino-info.wikispaces.com/Ethernet

  AT prikazy: 
  https://www.arduinotech.cz/inpage/jak-jednoduse-na-gsm-ii-dil-at-prikazy/


  pocet prvku v poli zjistime: 

  String actualWeather[] = {"01d", "01n", "02d", "02n", "03d", "03n", "04d", "04n", "09d", "09n", "10d", "10n", "11d", "11n", "13d", "13n", "50d", "50n"};
  pocet_prvku_v_poli = ((sizeof(actualWeather)/sizeof(String)));
 


rele 1 - A0, A2, A4, A6
key 1  - A1, A3, A5, A7

rele 2 - A9, A11, A13, A15
key 2  - A8, A10, A12, A14

led 3  - 32, 34, 36, 38
key 3  - 33, 35, 37, 39

KeypadPin 1 - 41 - rezerva
KeypadPin 2 - 43 - frezerva

RecieverData   - 2
TransmiterData - 11, 12

OneWireData - 7

SIM - Serial1
SIM RST - 28
ALARM   - 29
BoardPin 1 - 30 - rezerva
BoardPin 2 - 31 - rezerva


*/


// #include "SPI.h"

// #include "Wire.h"
#include "OneWire.h"
#include "Ethernet.h"
#include "SoftwareSerial.h"
#include "DallasTemperature.h"
#include "AM2320.h"
#include "avr/wdt.h"



#define TOUCH_SCEEN   //if the module equipt with touch screen, use this, otherwise use // to disable it
#define FLASH_CHIP    //if the module equipt with 2MB or 4MB flash chip, use it, otherwise  use // to disable it
#define _Digole_Serial_I2C_  //To tell compiler compile the special communication only, 
#define Ver 34           //if the version of firmware on display is V3.3 and newer, use this

//end changing

//define 8 bit color, see:https://en.wikipedia.org/wiki/8-bit_color
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

String actualWeather[] = {"01d", "01n", "02d", "02n", "03d", "03n", "04d", "04n", "09d", "09n", "10d", "10n", "11d", "11n", "13d", "13n", "50d", "50n"};



#define BGCOLOR 0

#include "DigoleSerial.h"

#include "Wire.h"
DigoleSerialDisp mydisp(&Wire, '\x27'); //I2C:Arduino UNO: SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5 on UNO and Duemilanove

void displayInit(void);
void displayHomePage(void);
void display_Icons(void);
void showLog(void);
void display_Status(void);
void display_Weather(void);
void use_User_Font_Standard(void);
void use_User_Font_In_Flash_Chip(void);

void setRelay(void);
void delayWDT(void);
void showRooms(void);
void showRoomsTemp(void);
void showAlarm(void);



// definice cidla teplota a vlhkost
AM2320 th;

float teplota;
float vlhkost;

// font ukazujici teplotu
byte fontTemperature = 200; // 200
byte fontSystem = 0;

// display zapnuto
byte displayOn = 1;
byte led_pwrOn = 1;

// tlacitka vstupu
byte tlacitko_modul[9] = {99, A1, A3, A5, A7, A8, A10, A12, A14};
byte tlacitko_modul_b[5] = {99, 33, 35, 37, 39};
// pamet rele vystupu
byte rele_modul[9] = {99, A0, A2, A4, A6, A9, A11, A13, A15};
byte rele_set[9] = {99, 1, 1, 1, 1, 1, 1, 1, 1};

// pozice starus LED
int positionStatus_x[9] = {99, 0, 0, 0, 0, 0, 0, 0, 0};
int positionStatus_y[9] = {99, 0, 30, 60, 90, 120, 150, 180, 210};
int positionStatus_pos[9] = {99, 1, 2, 3, 0, 4, 0, 0, 0};

int positionTempIcon[] = {0, 0, 80, 160};


// detekce alarmu
byte SIM_reset = 28;
byte alarm = 29;
boolean is_alarm = false;
byte led_internet_error = 32;
byte led_alarm = 34;
byte led_fnc = 36;
byte led_pwr = 38;

int internetreadcount;
char sim_read;
String mobile_data_value;

int mobile_REG;
int mobile_SQ;
String mobile_OP;

// nastavení čísla vstupního pinu
const int pinCidlaDS = 7;
// vytvoření instance oneWireDS z knihovny OneWire
OneWire oneWireDS(pinCidlaDS);
// vytvoření instance senzoryDS z knihovny DallasTemperature
DallasTemperature senzoryDS(&oneWireDS);



EthernetClient client;
// Ethernet PINs 10, 11, 12, 13
signed long next;
signed long next_led_pwr;
signed long next_led_fnc;
byte page_cnt; 
int data_read;
int set_val;
char read_buffer;
boolean nalez = false;
boolean nalez_data = false;
String nalez_data_value = "01d:23.9:polojasno";
String mobile_data;


// the dns server ip
// IPAddress dnServer(193, 85, 1, 12);
IPAddress dnServer(192, 168, 1, 1);
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

#include "Data.h" //include images and fonts
#include "Data_weather_icons.h" // include weather icons
#include "Functions.h" //include images and fonts


void setup()   {                

  showLog("setup");
  
  wdt_enable(WDTO_8S);
  
  Wire.begin();  
  Serial.begin(9600);
  Serial1.begin(9600); 

  // zapnutí komunikace knihovny s Dallas teplotním čidlem
  senzoryDS.begin();

  delayWDT(11);    

  
  mydisp.begin(); //initiate serial port  

  displayInit();


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
        digitalWrite(rele_modul[i], rele_set[i]);
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
  delay(200);
  digitalWrite(SIM_reset, HIGH);


  Ethernet.begin(mac, ip, dnServer, gateway, subnet);


  mydisp.setRotation(1);  

  // use_User_Font_Standard();  // upload fonts
  // use_User_Font_In_Flash_Chip // upload fonts to flash
  
  // zobrazi ikonky a popisky pokoju
  displayHomePage();


  // strankovac displeje
  page_cnt = 1;
  
  // info casovac dalsiho precteni dat z webu a ledky
  next = 0;
  next_led_pwr = 0;
  next_led_fnc = 0;

  
  
}


void loop() {


  // ----------- tlacitka a alarm a Internet ----------


   // zkontrolujeme alarm 
  // Serial.println("Test alarm");  
  
  showLog("alarm");
  
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

    clr_wdt();






    showLog("keys A");
    
    // projedeme si stisknuta tlacitka
    for(int i = 1; i <= 8; i++){
          if(digitalRead(tlacitko_modul[i]) == LOW){
            // Serial.println(i); //vypise stisknute tlacitko
            setRelayFromKey(i);
          }
          delay(1);
    }


    clr_wdt();


    showLog("keys B");
    
    // projedeme si stisknuta tlacitka B
    for(int i = 1; i <= 4; i++){
          if(digitalRead(tlacitko_modul_b[i]) == LOW){            
            setKey(i);
          }
          delay(1);
    }
  

    clr_wdt();


  showLog("PWR led");
  
  // obcas blikneme pover led  
  if (((signed long)(millis() - next_led_pwr)) > 0 && led_pwrOn == 0){
    
              digitalWrite(led_pwr, LOW); 
              led_pwrOn = 1;
    
    }
  
  if (((signed long)(millis() - next_led_pwr)) > 300){
    
        digitalWrite(led_pwr, HIGH);
        next_led_pwr = millis() + 1100;  
        led_pwrOn = 0;
        
    }



    clr_wdt();


  showLog("teplomery start");
  
  // obcas precteme nastaveni z internetu
  // Serial.println("Test internet");  
  if (((signed long)(millis() - next)) > 0){
      
      
      // --------- tepomery ----------
      senzoryDS.requestTemperatures();
      readTemp();
        
      clr_wdt();
        
        
      Serial.println("Read internet ready");  
      next = millis() + 11000;        


      clr_wdt();
      read_data_topeni(0); // precteme data z intenetu
      clr_wdt();

      
      


        // pokud zobrazujeme teplotu
        if(page_cnt == 1){
            
                    showLog("teplomery write");
                    
                    showRoomsTemp(); 
        
                    // precteme aktualni pocasi a zobrazime ikonku a hodnoty
                    String val_icon = getValue(nalez_data_value, ':', 0);
                    String val_tepmerature = getValue(nalez_data_value, ':', 1);
                    String val_pocasi = getValue(nalez_data_value, ':', 2);
                    String val_vlhkost = getValue(nalez_data_value, ':', 3);
                    String val_tepmerature_min = getValue(nalez_data_value, ':', 4);
                    String val_tepmerature_max = getValue(nalez_data_value, ':', 5);
                    String val_misto = getValue(nalez_data_value, ':', 6);

                    String val_icon_zitra = getValue(nalez_data_value, ':', 7);
                    String val_tepmerature_zitra = getValue(nalez_data_value, ':', 8);
                    String val_tepmerature_min_zitra = getValue(nalez_data_value, ':', 9);
                    String val_tepmerature_max_zitra = getValue(nalez_data_value, ':', 10);
                    
                    String val_icon_pozitri = getValue(nalez_data_value, ':', 11);
                    String val_tepmerature_pozitri = getValue(nalez_data_value, ':', 12);
                    String val_tepmerature_min_pozitri = getValue(nalez_data_value, ':', 13);
                    String val_tepmerature_max_pozitri = getValue(nalez_data_value, ':', 14);
                      
                    /*                    
                    Serial.println("icon: " + val_icon);
                    Serial.println("tepmerature: " + val_tepmerature);
                    Serial.println("pocasi:  " + val_pocasi);
                    Serial.println("min: " + val_tepmerature_min);
                    Serial.println("max: " + val_tepmerature_max); 
                    */
              
                    clr_wdt();
                                                                        
                    mydisp.setFont(0);
                    
                    mydisp.setColor(WHITE);
                    mydisp.setTextPosAbs(0, 237);
                  
                    mydisp.print(val_misto);
                    mydisp.print(" ");                    
                    
                    mydisp.setColor(CYAN);
                    mydisp.print(val_tepmerature); 
                    mydisp.print(val_pocasi);

                    mydisp.setColor(WHITE);
                    mydisp.print(" vlhkost: ");
                    mydisp.setColor(CYAN);
                    mydisp.print(val_vlhkost);
                    
                    mydisp.setColor(WHITE);
                    
                    
                    
                    // 0, 80, 160
                    
                    mydisp.setTextPosAbs(330, 77);
                    mydisp.print(val_tepmerature_min + "C-");
                    mydisp.print(val_tepmerature_max + "C ");                                     

                    mydisp.setTextPosAbs(330, 157);
                    mydisp.print(val_tepmerature_min_zitra + "C-");
                    mydisp.print(val_tepmerature_max_zitra + "C ");                                     

                    mydisp.setTextPosAbs(330, 240);
                    mydisp.print(val_tepmerature_min_pozitri + "C-");
                    mydisp.print(val_tepmerature_max_pozitri + "C ");

                  
                    // zobrazime ikonky pocasi
                    display_Weather(val_icon, 1);
                    display_Weather(val_icon_zitra, 2);
                    display_Weather(val_icon_pozitri, 3);  
              
                    clr_wdt();
              
                    mydisp.setTextPosAbs(0, 221);
                    
                    mydisp.setFont(fontSystem);
                    mydisp.setColor(WHITE);
              
                    showLog("mobile status");
                    
                    getMobileStatus();
                           
                    if(mobile_REG == 1){
                         mydisp.print(mobile_OP); 
                         mydisp.print(" signal: ");
                         mydisp.print(mobile_SQ);  
                                
                    }else{
                         mydisp.print("nedostupny...");                    
                    }
              
                    mydisp.print("         "); 


                    //system log
                    mydisp.setColor(MAGENTA);                    
                    mydisp.setTextPosAbs(0, 203);
                    
                    mydisp.print("(");
                    mydisp.print(internetreadcount );
                    mydisp.print(") ");

                    mydisp.setColor(WHITE);

      }

      // eof zobrazeni teploty



       
      mydisp.setFont(fontTemperature);

      clr_wdt();

      setRelay();
        
  }
  // Serial.println("Test internet OK");  



           

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



void read_data_topeni(int send_relay) {

      
      showLog("internet 1"); 
      
      clr_wdt();

      digitalWrite(led_internet_error, LOW);

      Serial.print("Connect to ");
      Serial.println(server);

      
      if (client.connect(server,80)){

          showLog("internet 2"); 
          
          Serial.println("Connected");

          // digitalWrite(, LOW);
          clr_wdt();
          
          String myURL = "GET /topeni/topeni.php?relay=";
          client.print(myURL);
          client.print(send_relay);
          client.print("&status=");
                  
                if (rele_set[send_relay] == 0){client.print(0);}
                if (rele_set[send_relay] == 1){client.print(1);}               
          
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
          client.print(senzoryDS.getTempCByIndex(3));
          client.print("&temp[6]=");
          client.print(senzoryDS.getTempCByIndex(4));

          client.print("&mobile_REG=");
          client.print(mobile_REG);
          client.print("&mobile_SQ=");
          client.print(mobile_SQ);
          client.print("&mobile_OP=");
          client.print(mobile_OP);                    
          
          client.println(" HTTP/1.0");
          client.print("Host: ");
          client.println(server);
          client.println("Connection: close");
          client.println();

          Serial.print(myURL);
          Serial.print(send_relay);
          Serial.print("&status=");
          Serial.println(rele_set[send_relay]);

          nalez = false;
          nalez_data = false;
          byte relec = 1;        
          delay(1);
          nalez_data_value = "";

          // precteni dat z internetu
                    
          internetreadcount = 0;
          
          showLog("internet 3"); 
          
          while(client.connected()) {
            if(client.available()) {
                char read_buffer = client.read();
     
                
                if (read_buffer == '>'){nalez = false;}
                if (read_buffer == ']'){nalez_data = false;}
                 
                if (nalez){

                  digitalWrite(led_internet_error, HIGH);
                  // Serial.print(read_buffer); //vypise prijata data
                  // na tohle mozna udelame funkci  
                  if (read_buffer == '0'){rele_set[relec] = 0;}
                  if (read_buffer == '1'){rele_set[relec] = 1;}
                  relec++;                  

                }else if (nalez_data){

                  nalez_data_value += read_buffer;
                  
                }
  
                if (read_buffer == '<'){nalez = true;}
                if (read_buffer == '['){nalez_data = true;}

                clr_wdt();
                         
            }

            // mozna povolit i tady chce otestovat aby na tom nevysel
            if(internetreadcount < 30000){
                clr_wdt();
            }

            internetreadcount++;
            
          }
        
          showLog("internet end");
          
         //Serial.println();
         //Serial.println("Odpojuji.");
         delay(1);
         client.flush();
         delay(1);
         //Serial.println();
         client.stop();   

         showLog("internet fin");
         
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
            Serial.println(rele_set[tlac_press]);            

            // na tohle mozna udelame funkci  
            // rele nastavime
            rele_set[tlac_press] = !rele_set[tlac_press];

            
            Serial.print("Tlacitko ");
            Serial.print(tlac_press);
            Serial.print(" stlaceno, rele vstup ");
            Serial.print(rele_modul[tlac_press]);
            Serial.println(" nastaveno");
            
            read_data_topeni(tlac_press);

            setRelay();
            
            // delay(1000);
            clr_wdt();
}






// alarm zavola na mobil
void setAlarm(){
            
            showLog("alarm start"); 
            
            Serial.println("Alarm"); 

            digitalWrite(led_alarm, LOW);
            
            //makeCall("604833891");
            //makeCall("605906254");
            makeCall("737226659");
            //sendSMS("737226659");
            //makeCall("737226659");

            digitalWrite(led_alarm, HIGH);

            showLog("alarm end");
            
}



void makeCall(String callnumber){

            showAlarm(callnumber);

            clr_wdt();

            showLog("alarm call");
            
            Serial1.print("ATD");
            Serial1.print(callnumber);
            Serial1.println(";");
            delay(100);            
             
            if(Serial1.available()){
                  mydisp.print(" vytacim...");
                  while (Serial1.available()){
                  sim_read = Serial1.read();
                    Serial.print(sim_read);
                  }
            }else{
                  mydisp.print(" nedostupny...");                    
            }
        
            delayWDT(29);
                       
            Serial1.println("ATH"); 
            
            showLog("alarm hang off");
                                 
            delay (1000);
            void showAlarm();
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

