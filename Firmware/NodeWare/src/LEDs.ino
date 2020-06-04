/* LEDS.h
 * Contains RGB values, animations, and various methods relating to LED operation
 */

/*
 * RGB/Colour Definitions
 */

/*
 * LED Methods
 */


void LEDWifiConnecting() {
  // Blink red until connected to wifi
  int blink = 3;
  int count = 0;
  while (count < blink) {
    pixels.SetPixelColor(0, red);
    pixels.Show();
    delay(200);
    Serial.print(".");
    pixels.SetPixelColor(0, off);
    pixels.Show();
    delay(200);
    count++;
  }
  pixels.SetPixelColor(0, red);
  pixels.Show();
  delay(1000);
  pixels.SetPixelColor(0, off);
  delay(500);
}

