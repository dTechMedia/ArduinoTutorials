int redPin = 11;
int greenPin = 10;
int bluePin = 9;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

}

void loop() {
  // Increase the brightness
  for(int i = 0; i < 256; i++) {
    analogWrite(redPin, i);
    delay(10); //Added so you can see the lights adjusting
  }
  for(int i = 0; i < 256; i++) {
    analogWrite(bluePin, i);
    delay(10); //Added so you can see the lights adjusting
  }
  for(int i = 0; i < 256; i++) {
    analogWrite(greenPin, i);
    delay(10); //Added so you can see the lights adjusting
  }
  // Decrease the brightness
  for(int i = 255; i > 0; i--) {
    analogWrite(redPin, i);
    delay(10); //Added so you can see the lights adjusting
  }
  for(int i = 255; i > 0; i--) {
    analogWrite(bluePin, i);
    delay(10); //Added so you can see the lights adjusting
  }
  for(int i = 255; i > 0; i--) {
    analogWrite(greenPin, i);
    delay(10); //Added so you can see the lights adjusting
  }
}
