// RGB LED
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

// Rotary Encoder
const int PinCLK = 2;
const int PinDT = 3;
const int PinSW = 4;

// Global Variables (we'll talk about this in another tutorial)
volatile boolean TurnDetected;
volatile boolean up;
long blueVal = 0;
long greenVal = 0;
long redVal = 0;
long virtualPosition = 0;
long previousPosition = 0;
int curPin = 9;

// Functions
void isr() {
  if(digitalRead(PinCLK))
    up = digitalRead(PinDT);
  else
    up = !digitalRead(PinDT);

  TurnDetected = true;
}

// Declarations
long readRotaryEncoder();
void setPinValue(int value, int pin);
void displayChange();
void autoCycleColors();

void setup() {
  // Setup RGB LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Setup Rotary Encoder
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);
  attachInterrupt (0, isr, FALLING);

  // Start serial monitor
  Serial.begin(9600);
  Serial.println("Serial Monitor Started...");

}

void loop() {
  virtualPosition += readRotaryEncoder();
  if(!(digitalRead(PinSW))) { // check if push button is pressed
    setPin();
    delay(500); // make sure we aren't double reading a switch...
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
      Serial.println("Pin set to Red");
    } else if (curPin == redPin) {
      curPin = bluePin;
      redVal = virtualPosition;
      virtualPosition = blueVal;
      Serial.println("Pin set to Blue");
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
  long virtualPosition = 0;
  if (TurnDetected) {
    if(up)
      virtualPosition--; // Mine is backwards from the original example....
    else
      virtualPosition++;

    TurnDetected = false;
  }

  return virtualPosition;
}

void autoCycleColors() {
  for(int i = 0; i < 256; i++)
  {
    analogWrite(redPin, i);
    delay(10);
  }
  for(int i = 0; i < 256; i++)
  {
    analogWrite(bluePin, i);
    delay(10);
  }
  for(int i = 0; i < 256; i++)
  {
    analogWrite(greenPin, i);
    delay(10);
  }
    for(int i = 256; i >= 0; i--)
  {
    analogWrite(redPin, i);
    delay(10);
  }
      for(int i = 256; i >= 0; i--)
  {
    analogWrite(greenPin, i);
    delay(10);
  }
      for(int i = 256; i >= 0; i--)
  {
    analogWrite(bluePin, i);
    delay(10);
  }  
}
