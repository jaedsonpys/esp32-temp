#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <DHT.h>

char *ssid = "....";
char *password = "....";
const int dhtPin = 25;

DHT dht(dhtPin, DHT11);

void setup() {
    Serial.begin(9600);

    Serial.println("Starting WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    Serial.print("WiFI connected: ");
    Serial.println(WiFi.localIP());

    if(MDNS.begin("esp32")) {
        Serial.println("MDNS Started");
    }

    // dht sensor
    dht.begin();
}

void loop() {
    // put your main code here, to run repeatedly:
}