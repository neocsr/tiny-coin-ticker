#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <heltec.h>

WiFiMulti wifiMulti;

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* url = "https://api.coindesk.com/v1/bpi/currentprice/btc.json";

void setup() {
  Heltec.begin(
    true,  // DisplayEnable
    false, // LoRaEnable
    true   // SerialEnable
  );
  delay(300);

  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Starting...");
  Heltec.display->display();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("Connecting %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  wifiMulti.addAP(ssid, password);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Heltec.display->clear();
  Heltec.display->drawString(0, 10, "HIGH");
  Heltec.display->display();
  delay(2000);

  // Wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {

    Serial.print("[http] begin...\n");
    HTTPClient http;
    http.begin(url);

    Serial.print("[http] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("[http] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        const char* time = doc["time"]["updatedISO"];
        const char* rate = doc["bpi"]["USD"]["rate"];

        Serial.println(time);
        Serial.println(rate);
        Heltec.display->clear();
        Heltec.display->drawString(0, 10, time);
        Heltec.display->drawString(0, 20, rate);
        Heltec.display->display();
        delay(60000);
      }
    } else {
      Serial.printf(
        "[http] GET... failed, error: %s\n",
        http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  digitalWrite(LED_BUILTIN, LOW);
  Heltec.display->clear();
  Heltec.display->drawString(0, 10, "LOW");
  Heltec.display->display();
  delay(2000);
}
