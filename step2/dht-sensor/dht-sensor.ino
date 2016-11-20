#include <DHT.h>

#define DHTPIN            D4         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11

DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS = 10000;

void setup() {
  Serial.begin(115200);
  dht.begin(); // Initialize device.
  Serial.println("DHT1 Example");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
  }

  delay(delayMS);
}
