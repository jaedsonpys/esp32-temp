#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <DHT.h>

char *ssid = "Jarmeson";
char *password = "wet20110";

const int dhtPin = 25;
float temperature, humidity;

DHT dht(dhtPin, DHT11);
WiFiServer server(80);

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

    server.begin();

    // dht sensor
    dht.begin();
}

void loop() {
    WiFiClient client = server.available();

    if(client.connected()) {
        while(client.connected()) {
            if(client.available() > 0) {
                char signal = client.read();

                if(signal == 's') {
                    temperature = dht.readTemperature();
                    humidity = dht.readHumidity();

                    String data = String(temperature) + "," + String(humidity);
                    client.println(data);
                }
            }
        }
        client.stop();
    }

    delay(1000);
}