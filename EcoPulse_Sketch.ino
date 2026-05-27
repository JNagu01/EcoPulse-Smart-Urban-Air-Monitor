#include <WiFi.h>
#include <ThingSpeak.h>
#include "DHT.h"

// WiFi Configuration for Wokwi Simulator
const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";


unsigned long myChannelNumber = 339XXXX;          
const char* myWriteAPIKey = "LBULIXXXXXXXXXXX"; 

// Pin Definitions
#define DHTPIN 15
#define DHTTYPE DHT22
#define GAS_SENSOR_PIN 34
#define LED_ALERT_PIN 2

#define AQI_THRESHOLD 400 

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  dht.begin();
  
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected successfully!");
  
  ThingSpeak.begin(client);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int rawGasValue = analogRead(GAS_SENSOR_PIN);
  
  int simulatedAQI = map(rawGasValue, 0, 4095, 0, 500); 
  int alertTriggered = 0;

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (simulatedAQI > AQI_THRESHOLD) {
    digitalWrite(2, HIGH); 
    alertTriggered = 1;
    Serial.println("⚠️ ALERT: Poor Air Quality Detected!");
  } else {
    digitalWrite(2, LOW); 
    alertTriggered = 0;
  }

  Serial.print("Temp: "); Serial.print(temperature); Serial.print("°C | ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.print("% | ");
  Serial.print("Simulated AQI: "); Serial.println(simulatedAQI);

  ThingSpeak.setField(1, simulatedAQI);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, humidity);
  ThingSpeak.setField(4, alertTriggered);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Dashboard updated successfully.");
  } else {
    Serial.println("Error updating dashboard. Code: " + String(x));
  }

  delay(15000); 
}

