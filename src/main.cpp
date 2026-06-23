#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

unsigned long channelID = 1234567;
const char* writeAPIKey = "ABCD1234EFGH5678";

WiFiClient client;

DHT dht(DHTPIN, DHTTYPE); 

void setup() {

  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  ThingSpeak.begin(client);
}

void loop() {

  float temperature = dht.readTemperature();

  long rssi = WiFi.RSSI();

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, rssi);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if(status == 200){
      Serial.println("Data Uploaded Successfully");
  }
  else{
      Serial.print("Error Code: ");
      Serial.println(status);
  }

  delay(20000); // ThingSpeak requires at least 15 seconds
}