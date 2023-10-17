#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>  // Including library for dht
#include <SPI.h>
#define DHTPIN 2          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);

#define BLYNK_TEMPLATE_ID "TMPL3w5ZJluL_"
#define BLYNK_TEMPLATE_NAME "Baby Cradle"
#define BLYNK_AUTH_TOKEN "SgfU0cM6jYCnXuFavKPD2MDz5EkNQuRr"

char auth[] = BLYNK_AUTH_TOKEN;              //Your Project authentication key
char ssid[] = "realme C55";                                       // Name of your network (HotSpot or Router name)
char pass[] = "12345678";

const int Motion = 0;   //you need to replace this value with Value_1
const int Relay = 3;  //you need to replace this value with Value_2
const int SoundPin = A0;
const int moisture = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  dht.begin();
   Blynk.begin(auth, ssid, pass);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("WiFi connected");
    delay(4000);
}  

  // put your main code here, to run repeatedly:
void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float s = analogRead(SoundPin);
  int m = digitalRead(Motion);
  int mois = digitalRead(moisture);
  Blynk.run();
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.println(t);
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V1, h);
  //Blynk.virtualWrite(V2, s); 
  Blynk.virtualWrite(V4, m);
  Blynk.virtualWrite(V6, mois);
  
}

BLYNK_WRITE(V3)
{
  digitalWrite(Relay, param.asInt());
}
