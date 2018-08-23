/*
   NodeWare.ino
   DomeNode Firmware
   JagDav, Andrew Patience, inversesandwich, macaba
   v0.1
*/

// Include the libraries we require
#include "EEPROM.h"
#include <CAN.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <NeoPixelBus.h>

// Debug variables
bool node_debug = true; // Enable this to prevent the ESP from restarting on an error to aid debugging

// Set variables
int node_id;
int node_fwversion;
const char* wifi_ssid     = "emfcamp-insecure18";
const char* wifi_password = "";
String mdns_hostname = "shm-domenode-";
String ota_server = "http://firmware.shmakerspace.org";
int ota_port = 80;
String ota_location = "/domenode/update/ota.php";
String ota_fwversion = "v0.1";

// Set EEPROM location in filesystem
EEPROMClass NODEDATA("eeprom", 0x1000);

void node_restart() {
  // Snippet to restart gracefully
  if (node_debug) {
    Serial.println("[node] Debug mode enabled, ESP will not restart!");
    while (true);
  }
  else {
    Serial.println("[node] Restarting in 5 seconds...");
    delay(5000);
    ESP.restart();
  }
}

int eeprom_start() {
  // Start EEPROM and attempt to initialise
  if (NODEDATA.begin(NODEDATA.length())) {
    Serial.println("[eeprom] NODEDATA successfully initialised!");
    return 1;
  }
  else {
    Serial.println("[eeprom] Failed to initialise NODEDATA partition!");
    return 0;
  }
}

int eeprom_checkid() {
  // Check EEPROM for a node ID
  NODEDATA.get(0, node_id);
  if (node_id == -1) {
    Serial.println("[eeprom] Failed finding node ID in NODEDATA!");
    return 0;
  }
  else {
    Serial.println("[eeprom] Found node ID in NODEDATA!");
    return 1;
  }
}

/* int eeprom_setid() {
  // Set a node ID in the EEPROM if one doesn't exist
  Serial.println("[node] Please enter the 2 digit node ID written on PCB:");
  while (Serial.available()) {
    // TODO: Accept an input via serial
  }
  //TODO: Write serial value to EEPROM
  node_restart();
  }
*/

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

int pixels_start(int count, int pin){
  // Initilise pixels
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> pixels(count, pin);
  Serial.println("[pixels] Successfully initialised pixels!");
  return 1;
}

void setup() {
  // Start serial communication for debug
  Serial.begin(115200);
  Serial.println("[node] Booting...");
  if (node_debug) {
    Serial.println("[node] DEBUG MODE ENABLED!");
  }

  // Start EEPROM and check if ID has been written
  if (!eeprom_start()) {
    node_restart();
  }
  if (eeprom_checkid()) {
    Serial.print("[node] This is node ");
    Serial.println(node_id);
  }
  else {
    Serial.println("[node] Please set node ID!");
    //eeprom_setid();
  }

  // Start CAN communication
  if (!can_start()) {
    node_restart();
  }

  // Initialise pixels and specify total number and GPIO pin
  //pixels_start(9, 17);
}

void loop() {

}
