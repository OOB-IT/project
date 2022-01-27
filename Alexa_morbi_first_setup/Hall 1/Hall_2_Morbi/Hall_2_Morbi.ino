// Edited by Vijay-Thumar (https://github.com/thumar-vijay/IOT_Codes) --- GOTO Aelexa_Controlling_W_O_Internet

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#define R1 D0
#define R2 D1
#define R3 D2
#define R4 D3
#define R5 D4


// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
void fifthLightChanged(uint8_t brightness);



// Change this!!

// WiFi Credentials
const char* ssid = "Ayaan";
const char* password = "210318@ayaan";

//const char* ssid = "smarthome";
//const char* password = "password@#1";

// device names as per node mcu default is 8 pin
String Device_1_Name = "device1";
String Device_2_Name = "device2";
String Device_3_Name = "device3";
String Device_4_Name = "device4";
String Device_5_Name = "device5";


boolean wifiConnected = false;

Espalexa espalexa;

const int a = D0;
const int b = D1;
const int c = D2;
const int d = D3;
const int e = D4;


void setup()
{
  Serial.begin(9600); 
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);



  
digitalWrite(D0, HIGH);
digitalWrite(D1, HIGH);
digitalWrite(D2, HIGH);
digitalWrite(D3, HIGH);
digitalWrite(D4, HIGH);
digitalWrite(D5, HIGH);


  // Initialise wifi connection
                                                //        Timer and count down start
                                                int dtime=10; //Seconds
                                                while (dtime !=0) {
                                                
                                                            for (dtime; dtime>0; dtime--) {
                                                              Serial.print("Countdown: ");
                                                                Serial.println(dtime);
                                                
                                                                if(dtime <=1) {
                                                                    Serial.print("Action ");
                                                                      wifiConnected = connectWifi();
                                                                      
                                                                }
                                                
                                                                delay(1000);
                                                            }
                                                        }
                                                
                                                 //        Timer and count down end
 // Delay for connection

  if (wifiConnected)
  {

    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(Device_4_Name, fourthLightChanged);
    espalexa.addDevice(Device_5_Name, fifthLightChanged);



    espalexa.begin();

  }

  else
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
      wifiConnected = connectWifi();

    }
  }

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
// first device call back function
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R1, LOW);
      Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R1, HIGH);
    Serial.println("Device1 OFF");
  }
}

// Second device call back function
void secondLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, LOW);
      Serial.println("Device2 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R2, HIGH);
    Serial.println("Device2 OFF");
  }
}

// Third device call back function
void thirdLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R3, LOW);
      Serial.println("Device3 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R3, HIGH);
    Serial.println("Device3 OFF");
  }
}

// Fourth device call back function
void fourthLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R4, LOW);
      Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R4, HIGH);
    Serial.println("Device1 OFF");
  }
}

// fifth device call back function
void fifthLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R5, LOW);
      Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R5, HIGH);
    Serial.println("Device1 OFF");
  }
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
