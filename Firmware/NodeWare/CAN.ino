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

