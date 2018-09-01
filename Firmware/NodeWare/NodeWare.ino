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
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <NeoPixelBrightnessBus.h>

// Define pin numbers
#define pin_heartbeat 22
#define pin_touch 14
#define pin_pixels 16

// Debug variables
bool node_debug = true; // Enable this to prevent the ESP from restarting on an error to aid debugging

// Set variables
// * Node variables
int node_id = 11; // Leave this varible empty to read from EEPROM at boot, or set a value and it'll be written to the EEPROM
uint64_t node_mac;
int node_fwversion ;
// * mDNS variables
String mdns_hostname = "shm-domenode-";
char mdns_hostnamebuffer[32];
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
const uint8_t pixels_brightness = 255;

WiFiMulti wifi_multi;

// Define non-volatile storage
Preferences preferences;

// Define pixels, colours and effects
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> pixels(pixels_quantity, pin_pixels);
RgbColor red(127, 0, 0);
RgbColor green(0, 127, 0);
RgbColor blue(0, 0, 127);
RgbColor yellow(255, 255, 0);
RgbColor white(127);
RgbColor inactive(70, 0, 0);
RgbColor off(0);
RgbColor shm(98, 0, 116);
RgbColor rainbow_color;
uint8_t rainbow_pos;
RgbColor rainbow_wheel(uint8_t rainbow_wheelpos)
{
  rainbow_wheelpos = 255 - rainbow_wheelpos;
  if (rainbow_wheelpos < 85)
  {
    return RgbColor(255 - rainbow_wheelpos * 3, 0, rainbow_wheelpos * 3);
  } else if (rainbow_wheelpos < 170)
  {
    rainbow_wheelpos -= 85;
    return RgbColor(0, rainbow_wheelpos * 3, 255 - rainbow_wheelpos * 3);
  } else
  {
    rainbow_wheelpos -= 170;
    return RgbColor(rainbow_wheelpos * 3, 255 - rainbow_wheelpos * 3, 0);
  }
}

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

int can_sendpacket(char message) {
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

int wifi_start() {
  // Start WiFi client and connect to predefined SSIDs
  wifi_multi.addAP("SHM", "hackmeplease");
  wifi_multi.addAP("emfcamp-insecure18", "");
  
  Serial.print("[wifi] Attemping to connection to a network");
  while (wifi_multi.run() != WL_CONNECTED) {
    pixels.setColor(0, red);
    pixels.Show();
    delay(500);
    Serial.print(".");
    pixels.setColor(0, off);
    pixels.Show();
    delay(500);
  }
  pixels.setColor(1, green);
  Serial.println("");
  Serial.println("[wifi] Successfully connected to network!");
  Serial.print("[wifi] IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
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
	pixels.setColor(0, green);
	pixels.show();
	delay(500);
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

  // Middle pixel yellow on OTA update
  pixels.setColor(0, yellow);
  pixels.show();
  ArduinoOTA.begin();
}

int pixels_start() {
  // Initilise pixels
  pixels.Begin();
  pixels.SetBrightness(pixels_brightness);
  for (int pixel = 0; pixel < 9; pixel++) {
    pixels.SetPixelColor(pixel, inactive);
  }
  pixels.Show();
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
  // Setup pixels and correct color gamma
  pixels_start();
  pixels.Show();
  
  // Start WiFi communication
  wifi_start();
  
  // Setup OTA updating (via IDE) and advertise service over network
  ota_arduino_start();

  // Attach capative ring sense to an interrupt
  Serial.println("[touch] Attaching interrupt to capacitive sensor...");
  touchAttachInterrupt(pin_touch, touch_interrupt, touch_threshold);
}

void loop() {
  // Rainbow!
  for (uint16_t j = 0; j < 256; j++) {
    if (touch_detected) {
      for (int pixel = 0; pixel < 9; pixel++) {
        pixels.SetPixelColor(pixel, shm);
      }
      pixels.Show();
      delay(50);
      touch_detected = false;
    }
    else {
      for (uint16_t i = 0; i < pixels_quantity; i++) {
        // generate a value between 0~255 according to the position of the pixel
        // along the pixels
        rainbow_pos = ((i * 256 / pixels_quantity) + j) & 0xFF;
        // calculate the color for the ith pixel
        rainbow_color = rainbow_wheel( rainbow_pos );
        // set the color of the ith pixel
        pixels.SetPixelColor(i, rainbow_color);
      }
    }
    // Check if OTA invitation has been recieved
    ArduinoOTA.handle();
    pixels.Show();
    delay(50);
  }
}
