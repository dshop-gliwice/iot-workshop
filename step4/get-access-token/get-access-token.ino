#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SAP-Guest";
const char* password = ""; // should be empty for guest network

String client_id = "";
String client_secret = "";

String accessToken = "";

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
  Serial.println("WIFI connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getAccessToken();
  }
  delay(30000);
}

void getAccessToken() {     //because of https://github.com/esp8266/Arduino/issues/2335
  HTTPClient client;
  client.begin("https://api.yaas.io/hybris/oauth2/v1/token", "DC B1 97 59 84 9D DB 76 F0 ED 7F 40 FC 0E 32 59 4F C3 AA 66");
  client.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = client.POST("client_id=" + client_id + "&client_secret=" + client_secret + "&grant_type=client_credentials&scope=hybris.document_view%20hybris.document_manage");

  if (httpCode == 200) {
    String json = client.getString();
    StaticJsonBuffer<300> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    String token_type = root["token_type"];
    String token = root["access_token"];
    accessToken = token_type + " " + token;
    Serial.printf("Received token %s\n", token.c_str());
  } else {
    Serial.printf("Token request failed, error: %s\n", client.errorToString(httpCode).c_str());
  }
  Serial.flush();
  client.end();
}


