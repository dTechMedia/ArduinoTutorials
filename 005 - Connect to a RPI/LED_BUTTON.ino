const unsigned int LED_PIN = 13;
const unsigned int ON_BUTTON_PIN = 8;
const unsigned int OFF_BUTTON_PIN = 7;
bool isLedOn = false;
int incomingByte = 0;



void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(ON_BUTTON_PIN, INPUT);
  pinMode(OFF_BUTTON_PIN, INPUT);

  Serial.begin(9600);
}


void loop() {
  checkButtonInput();
  checkSerialInput();
  
  if(isLedOn) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);  
  }
}


void checkButtonInput() {
  if(digitalRead(ON_BUTTON_PIN) == LOW) {
    isLedOn = true;
  } else if (digitalRead(OFF_BUTTON_PIN) == LOW) {
    isLedOn = false;
  }
}

void checkSerialInput() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte);
    if(incomingByte == 49) {
      isLedOn = true;  
    } else if(incomingByte == 48) {
      isLedOn = false;
    }
  }
}

void serialTest() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
  }
}
