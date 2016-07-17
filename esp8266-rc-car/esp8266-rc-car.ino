#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "SSID"; //Enter your wifi network SSID
const char* password = "PASSWORD"; //Enter your wifi network password

const int FORWARDS = 5;
const int BACKWARDS = 0;
const int RIGHT = 4;
const int LEFT = 13;

const int SERVER_PORT = 1111;
const int BAUD_RATE = 9600;

byte incomingByte = 0;

bool forwardsPressed = false;
bool backwardsPressed = false;
bool rightPressed = false;
bool leftPressed = false;

const int FORWARDS_PRESSED = 1;
const int FORWARDS_RELEASED = 2;
const int BACKWARDS_PRESSED = 3;
const int BACKWARDS_RELEASED = 4;
const int RIGHT_PRESSED = 5;
const int RIGHT_RELEASED = 6;
const int LEFT_PRESSED = 7;
const int LEFT_RELEASED = 8;

byte packetBuffer[512];

WiFiUDP Udp;

void initOutputs() {
  pinMode(FORWARDS, OUTPUT);
  pinMode(BACKWARDS, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);
}

void connectWifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WIFI network");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Udp.begin(SERVER_PORT);
}

void moveForwards() {
  digitalWrite(BACKWARDS, LOW);
  digitalWrite(FORWARDS, HIGH);
}

void moveBackwards() {
  digitalWrite(FORWARDS, LOW);
  digitalWrite(BACKWARDS, HIGH);
}

void turnRight() {
  Serial.println("move right pressed");
  digitalWrite(LEFT, LOW);
  digitalWrite(RIGHT, HIGH);
}

void turnLeft() {
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, HIGH);
}

void resetSteering() {
  digitalWrite(RIGHT, LOW);
  digitalWrite(LEFT, LOW);
}

void resetEngine() {
  digitalWrite(FORWARDS, LOW);
  digitalWrite(BACKWARDS, LOW);
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
    moveForwards();
  }
  else if (backwardsPressed == true) {
    moveBackwards();
  }
  else {
    resetEngine();
  }

  if (rightPressed == true) {
    turnRight();
  }
  else if (leftPressed == true) {
    turnLeft();
  }
  else {
    resetSteering();
  }
}

void setup() {
  Serial.begin(BAUD_RATE);
  delay(10);

  initOutputs();
  connectWifi();
}

void loop() {
  int noBytes = Udp.parsePacket();
  String received_command = "";

  if ( noBytes ) {
    Serial.print(millis() / 1000);
    Serial.print(":Packet of ");
    Serial.print(noBytes);
    Serial.print(" received from ");
    Serial.print(Udp.remoteIP());
    Serial.print(":");
    Serial.println(Udp.remotePort());

    Udp.read(packetBuffer,noBytes);
    Serial.println();

    Serial.println(packetBuffer[0]);
    incomingByte = packetBuffer[0];
    Serial.println();
  }
  detectKeyPresses();
  handlePinOutputs();
}
