
int redPin = 17;
int greenPin = 18;
int bluePin = 19;


void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}


void SetColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
   red = 255 - red;
   green = 255 - green;
   blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void loop() {
  // put your main code here, to run repeatedly:
  setColor(255, 0, 0); // RED
  delay(1000);
  setColor(0, 255, 0); // GREEN
  delay(1000);
  setColor(0, 0, 255); // BLUE
  delay(1000);
  setColor(80, 0, 80); // PURPLE
  delay(2000);

}

