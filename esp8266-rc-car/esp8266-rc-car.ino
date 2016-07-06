#include <ESP8266WiFi.h>

const char* ssid = "joosep112";
const char* password = "BCCD51AA63";

const int FORWARDS = 5;
const int BACKWARDS = 0;
const int RIGHT = 4;
const int LEFT = 13;

const int SERVER_PORT = 1111;
const int BAUD_RATE = 9600;

int incomingByte = 0;

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

WiFiServer server(SERVER_PORT);

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
}

void startServer() {
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
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
  startServer();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  incomingByte = client.read();
  detectKeyPresses();
  handlePinOutputs();

  Serial.println(incomingByte);
  client.flush();
  Serial.println("Client disonnected");
}
