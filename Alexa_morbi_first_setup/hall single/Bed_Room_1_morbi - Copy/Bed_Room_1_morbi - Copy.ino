// Edited by Vijay-Thumar (https://github.com/thumar-vijay/IOT_Codes) --- GOTO Aelexa_Controlling_W_O_Internet

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#define R1 D0


// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);


// Change this!!

// WiFi Credentials
const char* ssid = "Ayaan";
const char* password = "210318@ayaan";

//const char* ssid = "smarthome";
//const char* password = "password@#1";

// device names as per node mcu default is 8 pin
String Device_1_Name = "hall main light";


boolean wifiConnected = false;

Espalexa espalexa;

const int a = D0;

void setup()
{
  Serial.begin(9600); 
  pinMode(R1, OUTPUT);



  
digitalWrite(D0, HIGH);



  // Initialise wifi connection  
  
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off


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
