#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SAP-Guest";
const char* password = ""; // should be empty for guest network

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    sendGETRequest();
    delay(5000);
    sendPOSTRequest();
  }
  delay(5000);
}

void sendGETRequest() {
  HTTPClient client;
  client.begin("https://api.yaas.io/dshop/hello-iot/v1/hello", "DC B1 97 59 84 9D DB 76 F0 ED 7F 40 FC 0E 32 59 4F C3 AA 66");
  int httpCode = client.GET();
  Serial.println("Request sent");
  if (httpCode == 200) {
    Serial.print("Reqeuest response: ");
    Serial.println(client.getString());
  } else {
    Serial.printf("Request failed, error: %s\n", client.errorToString(httpCode).c_str());
  }
  Serial.flush();
  client.end();
}

void sendPOSTRequest() {
  HTTPClient client;
  client.begin("https://api.yaas.io/dshop/hello-iot/v1/ranking", "DC B1 97 59 84 9D DB 76 F0 ED 7F 40 FC 0E 32 59 4F C3 AA 66");
  client.addHeader("Content-Type", "application/json");

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["name"] = "Adam";
  
  String json;
  root.printTo(json);
  int httpCode = client.POST(json);
  Serial.println("Request sent");
  if (httpCode == 200) {
    Serial.print("Reqeuest response: ");
    Serial.println(client.getString());
  } else {
    Serial.printf("Request failed, error: %s\n", client.errorToString(httpCode).c_str());
  }
  Serial.flush();
  client.end();
}

