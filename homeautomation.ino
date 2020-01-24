/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "mBh3nKXXTxJVZj84zgiZUW_m-XyBleNH";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "GITS";
char pass[] = "";


// Mac address should be different for each device in your LAN
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress device_ip  (172, 16,   6,  8);
IPAddress dns_ip     (  8,   8,   8,   8);
IPAddress gateway_ip (172, 16,   17,   1);
IPAddress subnet_mask(255, 255, 0,   0);
void turnoffall(int deviceno)
  {
    HTTPClient http;
    char offcommand[] = "[\"1\"]";
    if (deviceno==1)
    {
      http.begin("http://188.166.206.43/mBh3nKXXTxJVZj84zgiZUW_m-XyBleNH/update/D4");
    }
    else{
      http.begin("http://188.166.206.43/mBh3nKXXTxJVZj84zgiZUW_m-XyBleNH/update/D0");
    }
     http.addHeader("Content-Type", "application/json"); 
    int httpResponseCode = http.PUT(offcommand);
    if(httpResponseCode>0){
 
    String response = http.getString();   
 
    Serial.println(httpResponseCode);
    Serial.println(response);          
 
   }else{
 
    Serial.print("Error on sending PUT Request: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();
  }

void setup()
{

  // Debug console
  Serial.begin(9600);

  // Setup WiFi network
  WiFi.config(device_ip, dns_ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, pass);

  // Setup Blynk
  Blynk.config(auth);
  while (Blynk.connect() == false) {
  }
  turnoffall(1);
  turnoffall(2);
}

void loop()
{
  Blynk.run();
}
