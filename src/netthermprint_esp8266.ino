#include "config.h"
#include "src/libescpos/libescpos.h"
#include "src/libnetthermprint/libnetthermprint.h"
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

/* Create config.h file such as below
#ifndef CONFIG_H
#define CONFIG_H
#define WIFI_SSID "changeme"
#define WIFI_PASSWD "changeme"

const uint8_t SERVER_IP[4] = {8, 8, 4, 4}; // change to your server ip

#endif
*/

ESP8266WiFiMulti wifiMulti;
EscPos printer;
WiFiUDP UDP;
NetThermPrint netprint;

int port = 41230;
IPAddress serverIp(SERVER_IP[0], SERVER_IP[1], SERVER_IP[2], SERVER_IP[3]);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWD);
  wifiMulti.addAP(WIFI_SSID2, WIFI_PASSWD2);
  // wifiMulti.addAP(WIFI_SSID3, WIFI_PASSWD3);

  Serial.println("Connecting to Wifi...");

  uint8_t try_count = 0;

  while (wifiMulti.run() != WL_CONNECTED) {
    if (try_count > 5) {
      Serial.println("Cannot connect to WiFi, rebooting!");
      ESP.restart();
    }
    Serial.println("WiFi not connected!");
    delay(1000);
    ++try_count;
  }

  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  ArduinoOTA.setHostname("netthermprint-8266");
  ArduinoOTA.begin();

  pinMode(0, INPUT_PULLUP);
  Serial1.begin(9600);
  UDP.begin(port);
}

void EscPos_sendCh(char a) { Serial1.write(a); }

void loop() {
  ArduinoOTA.handle();
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    char *packet = new char[packetSize];
    int len = UDP.read(packet, packetSize);
    if (len > 0) {
      netprint.processData(packet);
    }
    delete[] packet;
  }
  netprint.timerLoop();
}
void NetThermPrint_sendUdpResponse(const char *data, size_t len) {
  UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
  UDP.write(data, len);
  UDP.endPacket();
}

void NetThermPrint_sendUdp(const char *data, size_t len) {
  UDP.beginPacket(serverIp, port);
  UDP.write(data, len);
  UDP.endPacket();
}

time_t NetThermPrint_getTime() { return millis(); }

void NetThermPrint_systemReset() { ESP.restart(); }
