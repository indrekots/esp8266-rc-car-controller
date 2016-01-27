int backwardsPin = 2;
int forwardsPin = 3;
int leftPin = 4;
int rightPin = 5;

int incomingByte = 0;

bool forwardsPressed = false;
bool backwardsPressed = false;
bool rightPressed = false;
bool leftPressed = false;

const int FORWARDS_PRESSED = 1;
const int FORWARDS_RELEASED = 2;
const int BACKWARDS_PRESSED = 131;
const int BACKWARDS_RELEASED = 4;
const int RIGHT_PRESSED = 133;
const int RIGHT_RELEASED = 134;
const int LEFT_PRESSED = 7;
const int LEFT_RELEASED = 8;

void setup() {
  pinMode(backwardsPin, OUTPUT);
  pinMode(forwardsPin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    

  }
}

void detectKeyPresses() {
  if (incomingByte == FORWARDS_PRESSED) {
      forwardsPressed = true;
    }
    else if (incomingByte == BACKWARDS_PRESSED) {
      backwardsPressed = true;
    }

    if (incomingByte == FORWARDS_RELEASED) {
      forwardsPressed = false;
    }
    else if (incomingByte == BACKWARDS_RELEASED) {
      backwardsPressed = false;
    }

    if (incomingByte == RIGHT_PRESSED) {
      rightPressed = true;
    }
    else if (incomingByte == LEFT_PRESSED) {
      leftPressed = true;  
    }

    if (incomingByte == RIGHT_RELEASED) {
      rightPressed = false;
    }
    else if (incomingByte == LEFT_RELEASED) {
      leftPressed = false;
    }
}

void handlePinOutputs() {
  if (forwardsPressed == true) {
    digitalWrite(forwardsPin, HIGH);
  }
  else {
    digitalWrite(forwardsPin, LOW);
  }

  if (backwardsPressed == true) {
    digitalWrite(backwardsPin, HIGH);
  }
  else {
    digitalWrite(backwardsPin, LOW);
  }

  if (rightPressed == true) {
    digitalWrite(rightPin, HIGH);
  }
  else {
    digitalWrite(rightPin, LOW);
  }

  if (leftPressed == true) {
    digitalWrite(leftPin, HIGH);
  }
  else {
    digitalWrite(leftPin, LOW);
  }
}

