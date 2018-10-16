WiFiClient client;

void openTcpConnection(){
  const uint16_t port = 8910;
  const char * host = "94.45.255.138"; // ip or dns

  if (!client.connect(host, port)) {
      Serial.println("connection failed");
      Serial.println("wait 5 sec...");
      delay(5000);
      return;
  }
}

void checkTcpConnection(){
  if(client.available()) {
      const char* line = client.readStringUntil('\r').c_str();
      int r, g, b;
      sscanf(line, "%d;%d;%d", &r, &g, &b);
  }
}

