int wethr = 0;
String weather[] = {"01d", "01n", "02d", "02n", "03d", "03n", "04d", "04n"};
int wethr_pocet;

String myString = "01d:23.9:polojasno";

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  wethr_pocet = (sizeof(weather)/sizeof(String));


  String val_icon = getValue(myString, ':', 0);
  String val_tepmerature = getValue(myString, ':', 1);
  String val_pocasi = getValue(myString, ':', 2);
    
  Serial.println("icon: " + val_icon);
  Serial.println("tepmerature: " + val_tepmerature);
  Serial.println("pocasi:  " + val_pocasi);

  delay(10000);
  
}

// the loop function runs over and over again forever
void loop() {
 
  Serial.print("Data "); 
  Serial.print(weather[wethr]); 
  Serial.print(" SizeOf weather "); 
  Serial.print(wethr); 
  Serial.print(" / "); 
  Serial.println(wethr_pocet);   
  
  display_Weather(weather[wethr]);
  
  wethr++;
  if(wethr >= wethr_pocet){
    wethr = 0;
    }

 
 

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
 
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
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




// ikonky pocasi
void display_Weather(String weather)
{

        Serial.print("Function "); 
        Serial.print(weather);
        Serial.print(" set "); 
  
      
          if(weather ==  "01d"){
            Serial.println("i01d256");
           }    
      
          else if(weather ==  "01n"){
            Serial.println("i01n256");
           }

          else if(weather ==  "02d"){
            Serial.println("i02d256");
           }    
      
          else if(weather ==  "02n"){
            Serial.println("i02n256");
           }

          else if(weather ==  "03d"){
            Serial.println("i03d256");
           }    
      
          else if(weather ==  "03n"){
            Serial.println("i03n256");
           }

          else if(weather ==  "04d"){
            Serial.println("i04d256");
           }    
      
          else if(weather ==  "04n"){
            Serial.println("i04n256");
           }
                                          
           else{
            Serial.println("i01d256");
           }


            Serial.println(" "); 
  
}
