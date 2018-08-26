/*
   NodeWare.ino
   DomeNode Firmware
   JagDav, Andrew Patience, inversesandwich, macaba
   v0.1
*/

// Include the libraries we require
#include <Preferences.h>
#include <CAN.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <NeoPixelBus.h>

// Debug variables
bool node_debug = true; // Enable this to prevent the ESP from restarting on an error to aid debugging

// Set variables
int node_id = 1; // Leave this varible empty to read from EEPROM at boot, or set a value and it'll be written to the EEPROM
uint64_t node_mac;
int node_fwversion ;
const char* wifi_ssid     = "emfcamp-insecure18";
const char* wifi_password = "";
String mdns_hostname = "shm-domenode-";
String ota_server = "http://firmware.shmakerspace.org";
int ota_port = 80;
String ota_location = "/domenode/update/ota.php";
String ota_fwversion = "";

bool touch_detected = false;
int touch_threshold = 40;

// Define non-volatile storage
Preferences preferences;

void node_restart() {
  // Restart gracefully
  if (node_debug) {
    Serial.println("[node] Debug mode enabled, ESP will not restart!");
    while (true);
  }
  else {
    Serial.println("[node] Restarting in 5 seconds...");
    delay(5000);
    ESP.restart();
  }
  return;
}

int node_printmac() {
  node_mac = ESP.getEfuseMac();
  Serial.printf("[node] MAC Address: %04X", (uint16_t)(node_mac >> 32)); // Print high 2 bytes
  Serial.printf("%08X\n", (uint32_t)node_mac); // Print low 4 bytes.
  return 1;
}

int nvs_start() {
  // Mount DomeNode namespace and RW permissions
  Serial.println("[nvs] Mounting DomeNode RW namespace...");
  preferences.begin("DomeNode", false);
  return 1;
}

int nvs_stop() {
  // Unmount NVS if mounted to a namespace
  Serial.println("[nvs] Unmounting NVS...");
  preferences.end();
  return 1;
}

int nvs_checkid() {
  // Check NVS for a node ID
  node_id = preferences.getUInt("id", 0);
  if (!node_id) {
    Serial.println("[nvs] Failed finding node ID in NVS!");
    return 0;
  }
  else {
    Serial.println("[nvs] Found node ID in NVS!");
    return 1;
  }
}

int nvs_writeid() {
  // Write node ID to NVS
  preferences.putUInt("id", node_id);
  Serial.println("[nvs] Sucessfully wrote node ID to NVS");
  return 1;
}

int nvs_prepid() {
  // Check to see if node ID has been hard-coded otherwise check NVS
  if (node_id) {
    Serial.print("[node] Node ID ");
    Serial.print(node_id);
    Serial.println(" set in firmware, writing to NVS...");
    nvs_writeid();
    return 1;
  } else {
    Serial.println("[node] Node ID not set in firmware, attempting to load from NVS...");
    if (nvs_checkid()) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int can_start() {
  // Start the CAN peripheral at 500 kbps
  if (CAN.begin(500E3)) {
    Serial.println("[can] CAN started successfully at 500kbps!");
    CAN.onReceive(can_recievecallback);
    return 1;
  }
  else {
    Serial.println("[can] Starting CAN failed!");
    return 0;
  }
}

int can_sendpacket(byte function, char message) {
  byte frameid;
  // TODO
  CAN.beginPacket(frameid);
  CAN.endPacket();
  return 1;
}

void can_recievecallback(int packetSize) {
  // received a packet
  Serial.print("[can] Received ");
  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }
  if (CAN.packetRtr()) {
    // Remote transmission request, packet contains no data
    Serial.print("RTR ");
  }
  Serial.print("packet with id 0x");
  Serial.print(CAN.packetId(), HEX);
  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  }
  else {
    Serial.print(" and length ");
    Serial.println(packetSize);
    // only print packet data for non-RTR packets
    while (CAN.available()) {
      Serial.println((char)CAN.read());
    }
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

void touch_interrupt() {
  touch_detected = true;
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

int pixels_start(int count, int pin) {
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

  // Print MAC address of the ESP32
  node_printmac();

  // Start NVS filesystem and prep ID
  nvs_start();
  if (nvs_prepid()) {
    nvs_stop();
    Serial.print("[node] This is node ");
    Serial.println(node_id);
  } else {
    nvs_stop();
    Serial.println("[node] Please set ID in firmware!");
    node_restart();
  }

  // Start CAN communication
  if (!can_start()) {
    node_restart();
  }

  // Attach capative ring sense to an interrupt
  Serial.println("[touch] Attaching interrupt to capacitive sensor 8...");
  touchAttachInterrupt(T8, touch_interrupt, touch_threshold);

  // Initialise pixels and specify total number and GPIO pin
  //pixels_start(9, 17);
}

void loop() {
  if (touch_detected) {
    touch_detected = false;
    Serial.println("[touch] Ring touched!");
    Serial.println("[can] Sending CAN packet with node ID 0000001, function code 0000...");
    CAN.beginPacket(0x01); // Node ID 000001, Function code 0000 (testing only)
    CAN.write(1);
    CAN.endPacket();
  }
}
