#include <NeoPixelBus.h>
// ESP32 Touch Test
// Lights up all LEDs in purple when cap ring is touched
// Touch Pin = Touch5 = T5 =GPIO14
// Pixels Pin = GPIO16

#define PIXELS_PIN 16
#define PIXELS_COUNT 9

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> pixels(PIXELS_COUNT, PIXELS_PIN);
int threshold = 25;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  printf("\n ESP32 Touch Light\n");
  touchAttachInterrupt(14, gotTouch, threshold);

  pixels.Begin();

}

void loop() {

  // Touch is GPIO14
  Serial.println(touchRead(14)); // get value using GPIO
  //Serial.println(touchRead(T5)); //get value using Touch5

  Serial.println("");
  delay(1000);
  // Turn pixels off
  for (int i=0; i<PIXELS_COUNT; i++) {
    pixels.SetPixelColor(i, RgbColor(0, 0, 0));
  }
  pixels.Show();
}

void gotTouch(){
  Serial.println("Touched!\n");
  // Do a pixel thing
  // Make pixels purple
  for (int i=0; i<PIXELS_COUNT; i++) {
    pixels.SetPixelColor(i, RgbColor(128, 0, 127));
  }
  pixels.Show();
}
