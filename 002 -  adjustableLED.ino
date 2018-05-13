int sensorPin = 0;
int ledPin = 11;


void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  analogWrite(ledPin, sensorValue);

}
