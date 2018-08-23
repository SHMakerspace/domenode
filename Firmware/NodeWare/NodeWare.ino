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
int nodeid;
const char* wifi_ssid     = "emfcamp-insecure18";
const char* wifi_password = "";
String mdns_hostname = "";
String ota_server = "http://firmware.shmakerspace.org";
int ota_port = 80;
String ota_location = "/esp/update/arduino.php";
String ota_fwversion = "v0.1";

// Set EEPROM location in filesystem
EEPROMClass  NODEDATA("eeprom", 0x1000);

void node_restart() {
  // Snippet to restart gracefully
  Serial.println("[node] Restarting!");
  delay(5000);
  ESP.restart();
}

int eeprom_start() {
  // Start EEPROM and attempt to initialise
  if (NODEDATA.begin(NODEDATA.length())) {
    Serial.println("[eeprom] NODEDATA succesfully initialised!");
    return 1;
  }
  else {
    Serial.println("[eeprom] Failed to initialise NODEDATA partition!");
    return 0;
  }
}

int eeprom_checkid() {
  // Check EEPROM for a node ID
  NODEDATA.get(0, nodeid);
  if (nodeid == -1) {
    return 0;
  }
  else {
    return 1;
  }
}

int eeprom_setid() {
  // Set a node ID in the EEPROM if one doesn't exist

}

int can_start() {
  // Start the CAN peripheral at 500 kbps
  if (CAN.begin(500E3)) {
    Serial.println("[can] CAN started successfully at 500kbps!");
    return 1;
  }
  else {
    Serial.println("[can] Starting CAN failed!");
    return 0;
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
  return 1;
}

int mdns_start(const char* hostname) {
  // Start mDNS responder
  if (MDNS.begin(hostname)) {
    Serial.println("[mdns] mDNS responder started");
    return 1;
  }
  else {
    Serial.println("[mdns] Starting MDNS responder failed!");
    return 0;
  }
}

/* Commented out to compile
  int ota_start(String server, String port, String location, String fwversion) {
  // Check for firmware updates
  //t_httpUpdate_return ret = ESPhttpUpdate.update(server, port, location, fwversion);
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
*/

void setup() {
  // Start serial communication for debug
  Serial.begin(115200);
  Serial.println("[node] Booting...");

  // Start EEPROM
  if (!eeprom_start()) {
    node_restart();
  }

  if (eeprom_checkid()) {
    Serial.println("[eeprom] Found node ID in EEPROM!");
    Serial.print("[node] This is node ");
    Serial.println(nodeid);
  }
  else {
    Serial.println("[eeprom] Failed finding node ID in EEPROM!");
    Serial.println("[node] Please set node ID!");
    node_restart();
  }

  Serial.println(nodeid);

  // Start CAN communication
  if (!can_start()) {
    node_restart();
  }

  //
}

void loop() {

}
