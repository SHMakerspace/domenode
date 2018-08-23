/*
   NodeWare.ino
   DomeNode Firmware
   JagDav, inversesandwich, macaba
   v0.1
*/

// Include the libraries we require
#include "EEPROM.h"
#include <CAN.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>

// Set variables
const char* wifi_ssid     = "emfcamp-insecure18";
const char* wifi_password = "";
String mdns_hostname = "";
String ota_server = "firmware.shmakerspace.org";
int ota_port = 80;
String ota_location = "/esp/update/arduino.php";
String ota_fwversion = "v0.1";

int can_start() {
  // Start the CAN bus at 500 kbps
  if (CAN.begin(500E3)) {
    Serial.println("[can] CAN started successfully at 500kbps!");
    return 0;
  }
  else {
    Serial.println("[can] Starting CAN failed!");
    return 1;
  }
}

int wifi_start(char* ssid, char* password) {
  // Start WiFi client and connect to predefined SSID
  Serial.println("[wifi] Attemping to connection to network");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("[wifi] Successfully connectected to network!");
  return 0;
}

int mdns_start(hostname) {
  // Start mDNS responder
  if (MDNS.begin(hostname)) {
    Serial.println("[mdns] mDNS responder started");
    return 0;
  }
  else {
    Serial.println("[mdns] Starting MDNS responder failed!");
    return 1;
  }
}

int ota_start(server, port, location, fwversion) {
  // Check for firmware updates
  t_httpUpdate_return ret = ESPhttpUpdate.update(server, port, location, fwversion);
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.println("[ota] Update failed!");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("[ota] No update required.");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("[ota] Update found! Starting firmware update ");
      break;
  }
}

void setup() {
  // Start serial communication for debug
  Serial.begin(115200);
  Serial.println("[node] DomeNode #01 running v0.1");

}

void loop() {

}
