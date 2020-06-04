int ota_arduino_start() {
  mdns_hostname.toCharArray(mdns_hostnamebuffer, 32);
  ArduinoOTA.setHostname(mdns_hostnamebuffer);
  ArduinoOTA.setPort(8266);
  ArduinoOTA.setPassword("hackmeplease");
  //ArduinoOTA.setPasswordHash("d78b6f30225cdc811adfe8d4e7c9fd34"); //hack
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
  //pixels.SetPixelColor(0, green);
  //pixels.Show();
  //delay(500);
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
  pixels.SetPixelColor(0, yellow);
  pixels.Show();
  ArduinoOTA.begin();
}
