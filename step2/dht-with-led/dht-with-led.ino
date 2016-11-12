#include <Arduino.h>
#include <DHT.h>

#define DHTPIN            D4         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11

DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS = 10000;

void setup() {
  Serial.begin(115200);
  dht.begin(); // Initialize device.
  Serial.println("DHT1 Example");

  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
  
  if(t<28.0){
    digitalWrite(BUILTIN_LED, HIGH);      
  }else{
    digitalWrite(BUILTIN_LED, LOW); 
  }

  delay(delayMS);
}
