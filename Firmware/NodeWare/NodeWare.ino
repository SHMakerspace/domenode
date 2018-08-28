/*
   NodeWare.ino
   DomeNode Firmware
   JagDav, Andrew Patience, inversesandwich, macaba
   v0.1
*/

// Include the libraries we require
#include <Preferences.h>
#include <Ticker.h>
#include <CAN.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

// Define pin numbers
#define pin_heartbeat 22
#define pin_touch 14
#define pin_pixels 16

// Debug variables
bool node_debug = true; // Enable this to prevent the ESP from restarting on an error to aid debugging

// Set variables
// * Node variables
int node_id; // Leave this varible empty to read from EEPROM at boot, or set a value and it'll be written to the EEPROM
uint64_t node_mac;
int node_fwversion ;
// * WiFi variables
/*** PLEASE DOUBLE CHECK CREDENTIALS BEFORE UPLOADING, IF THEY ARE INCORRECT OTA UPDATES WILL BE IMPOSSIBLE AND YOU'LL HAVE TO MANUALLY REPROGRAM ALL THE NODES VIA SERIAL. YOU HAVE BEEN WARNED! ***
 *** IF COMMITING TO A GIT REPO, PLEASE REMOVE CREDENTIALS BEFORE DOING SO! ***/
char* wifi_ssid     = "SHM";
char* wifi_password = "hackmeplease";
// * mDNS variables
String mdns_hostname = "shm-domenode-";
char mdns_hostnamebuffer[32];
// * OTA variables
String ota_server = "http://firmware.shmakerspace.org";
int ota_port = 80;
String ota_location = "/domenode/update/ota.php";
String ota_fwversion = "";
// * Heartbeat variables
Ticker heartbeat_blinker;
Ticker heartbeat_toggler;
float heartbeat_pace = 0.05;  //seconds
const float heartbeat_period = 2; //seconds
// * Touch variables
bool touch_detected = false;
int touch_threshold = 25;
// * Pixel variable
const uint16_t pixels_quantity = 9;


// Define non-volatile storage
Preferences preferences;

// Define pixels and colours
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> pixels(pixels_quantity, pin_pixels);
NeoGamma<NeoGammaTableMethod> pixels_gamma;
RgbColor red(127, 0, 0);
RgbColor green(0, 127, 0);
RgbColor blue(0, 0, 127);
RgbColor white(127);
RgbColor inactive(70, 0, 0);
RgbColor off(0);
RgbColor shm(98, 0, 116);

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

int node_printmac(uint64_t mac) {
  Serial.printf("[node] MAC Address: %04X", (uint16_t)(mac >> 32)); // Print high 2 bytes
  Serial.printf("%08X\n", (uint32_t)mac); // Print low 4 bytes.
  return 1;
}

int heartbeat_start() {
  pinMode(pin_heartbeat, OUTPUT);
  heartbeat_toggler.attach(heartbeat_period, heartbeat_toggle);
  return 1;
}

void heartbeat_blink() {
  digitalWrite(pin_heartbeat, !digitalRead(pin_heartbeat));
}

void heartbeat_toggle() {
  static bool heartbeat_blinkingstatus = false;
  if (heartbeat_blinkingstatus) {
    heartbeat_blinker.detach();
    heartbeat_blinkingstatus = false;
  }
  else {
    heartbeat_blinker.attach(heartbeat_pace, heartbeat_blink);
    heartbeat_blinkingstatus = true;
  }
  digitalWrite(pin_heartbeat, LOW);  //make sure LED on on after toggling (pin LOW = led ON)
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
  // TODO
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
  Serial.print("[wifi] Attemping to connection to network");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("[wifi] Successfully connected to network!");
  Serial.print("[wifi] IP address: ");
  Serial.println(WiFi.localIP());
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

int ota_arduino_start() {
  mdns_hostname.toCharArray(mdns_hostnamebuffer, 32);
  ArduinoOTA.setHostname(mdns_hostnamebuffer);
  ArduinoOTA.setPasswordHash("b413dd8e153df6ad2938814c7858860c"); //hackmeplease
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    CAN.sleep();
    
    Serial.println("[ota] Update invitation recieved, update type is " + type + "!");
  })
  .onEnd([]() {
    Serial.println("\n [ota] Update download finished!");
  })
  .onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("[ota] Update progress: %u%%\r", (progress / (total / 100)));
  })
  .onError([](ota_error_t error) {
    Serial.printf("[ota] Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Authentication failed!");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Couldn't start!");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connection failed!");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Download failed!");
    else if (error == OTA_END_ERROR) Serial.println("Couldn't finish!");
  });
  ArduinoOTA.begin();
}

/* Commented out to compile
  int ota_http_start(String server, String port, String location, String fwversion) {
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

int pixels_start() {
  // Initilise pixels
  pixels.Begin();
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

  // Start heartbeat
  Serial.println("[heartbeat] Starting heartbeat...");
  heartbeat_start();

  // Print MAC address of the ESP32
  node_printmac(ESP.getEfuseMac());

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
  // Append node ID to hostname
  Serial.println("[mdns] Setting node hostname...");
  mdns_hostname += String(node_id);

  // Start CAN communication
  if (!can_start()) {
    node_restart();
  }

  // Start WiFi communication
  wifi_start(wifi_ssid, wifi_password);

  // Setup OTA updating (via IDE) and advertise service over network
  ota_arduino_start();

  // Attach capative ring sense to an interrupt
  Serial.println("[touch] Attaching interrupt to capacitive sensor...");
  touchAttachInterrupt(pin_touch, touch_interrupt, touch_threshold);

  // Setup pixels and correct color gamma
  pixels_start();
  shm = pixels_gamma.Correct(shm);
  inactive = pixels_gamma.Correct(inactive);
  red = pixels_gamma.Correct(red);
  green = pixels_gamma.Correct(green);
  blue = pixels_gamma.Correct(blue);
  white = pixels_gamma.Correct(white);

}

void loop() {
  // Check if OTA invitation has been recieved
  ArduinoOTA.handle();

  // Check if touch interrupt has been triggered
  if (touch_detected) {
    touch_detected = false;
    Serial.println("[touch] Interrupt triggered!");
    /*
      Serial.println("[can] Sending CAN packet with node ID 0000001, function code 0001...");
      CAN.beginPacket(0x81); // Node ID 000001, Function code 0001 (testing only)
      CAN.write(true);
      CAN.endPacket();
    */
    for (int pixel_number = 0; pixel_number < 9; pixel_number++) {
      pixels.SetPixelColor(pixel_number, shm);
    }
  } else {
    for (int pixel_number = 0; pixel_number < 9; pixel_number++) {
      pixels.SetPixelColor(pixel_number, inactive);
    }
  }

  // Update pixels
  pixels.Show();
  delay(100);
}
