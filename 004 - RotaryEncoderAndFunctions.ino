// RGB LED
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

// Rotary encoder
const int PinCLK = 2;
const int PinDT = 3;
const int PinSW = 4;

// global variables (we'll talk about this in another tutorial)
volatile boolean TurnDetected;
volatile boolean up;
long blueVal = 0;
long greenVal = 0;
long redVal = 0;
long virtualPosition = 0;
long previousPosition = 0;
int curPin = bluePin; //First pin is blue pin.

// isr function
void isr() {
  if(digitalRead(PinCLK))
    up = digitalRead(PinDT);
  else
    up = !digitalRead(PinDT);

  TurnDetected = true;
}


// Declarations
void cycleColors();
long readRotaryEncoder();
void setPinValue(int value, int pin);
void displayChange();

void setup() {
  // Setup RGB LED
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Setup Rotary Encoder
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);
  attachInterrupt (0, isr, FALLING);

  // Start serial monitor
  Serial.begin(9600);
  Serial.println("serial monitor started...");

}

void loop() {
  //cycleColors(); We may bring this back later...
  virtualPosition += readRotaryEncoder();
  if(!(digitalRead(PinSW))) { // Check if push button is pressed
    setPin();
    delay(500);
  }
  setPinValue(virtualPosition, curPin);
  displayChange();
}


void setPin() {
  if(curPin == bluePin) {
    curPin = greenPin;
    blueVal = virtualPosition;
    virtualPosition = greenVal;
    Serial.println("Pin set to green...");
  } else if (curPin == greenPin) {
    curPin = redPin;
    greenVal = virtualPosition;
    virtualPosition = redVal;
    Serial.println("pin set to red...");
  } else if (curPin == redPin) {
    curPin = bluePin;
    redVal = virtualPosition;
    virtualPosition = blueVal;
    Serial.println("pin set to blue...");
  }
}


void setPinValue(int value, int pin) {
  if(value >= 0 && value <= 255) {
    analogWrite(pin, value);
  } else if(value < 0) {
    analogWrite(pin, 0);
  } else if(value > 255) {
    analogWrite(pin, 255);
  } else {
    Serial.println("error setting pin value...");
  }
}


void displayChange() {
  if(virtualPosition != previousPosition) {
    previousPosition = virtualPosition;
    Serial.print("Position @: ");
    Serial.println(virtualPosition);
  }
}


long readRotaryEncoder() {
  long virtualpos = 0;
  if(TurnDetected) {
    if(up) {
      virtualPosition--; // My rotary encoder turns the oposite way of the form code...
    } else {
      virtualPosition++;
    }
  }
}


void cycleColors() {
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
