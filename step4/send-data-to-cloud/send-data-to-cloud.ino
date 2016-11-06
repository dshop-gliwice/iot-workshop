#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>

const char* ssid = "SAP-Guest";
const char* password = ""; // should be empty for guest network

String client_id = "";
String client_secret = "";

#define DHTPIN D5 //TODO: change to NodeMCU pin
#define DHTTYPE DHT22 //TODO: test with DTH11
DHT dht(DHTPIN, DHTTYPE);

String accessToken = "";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  //start DTH
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getAccessToken();

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    saveDTH(t, h);
  }
  delay(30000);
}

//check fingerprint with
//echo | openssl s_client -connect api.yaas.io:443 |& openssl x509 -fingerprint -noout

void saveDTH(float t, float h) {
  HTTPClient http;
  http.begin("https://api.yaas.io/hybris/document/v1/iotexp/iotexp.demoapp/data/test", "DC B1 97 59 84 9D DB 76 F0 ED 7F 40 FC 0E 32 59 4F C3 AA 66");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", accessToken);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["t"] = t;
  root["h"] = h;

  String json;
  root.printTo(json);
  int httpCode = http.POST(json);
  if (httpCode > 0) {
    Serial.println("POST request succeeded");
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  Serial.flush();
  http.end();
}

void getAccessToken() {     //because of https://github.com/esp8266/Arduino/issues/2335
  HTTPClient http;
  http.begin("https://api.yaas.io/hybris/oauth2/v1/token", "DC B1 97 59 84 9D DB 76 F0 ED 7F 40 FC 0E 32 59 4F C3 AA 66");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST("client_id=" + client_id + "&client_secret=" + client_secret + "&grant_type=client_credentials&scope=hybris.document_view%20hybris.document_manage");

  if (httpCode > 0) {
    String json = http.getString();
    StaticJsonBuffer<300> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    String token_type = root["token_type"];
    String token = root["access_token"];
    accessToken = token_type + " " + token;
  } else {
    Serial.printf("Token request failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  Serial.flush();
  http.end();
}
