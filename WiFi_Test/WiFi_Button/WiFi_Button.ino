#include <WiFiS3.h>
#include <WebSocketsServer.h>

const char* ssid = "Mohammed";        // Your hotspot name
const char* password = "123abc456";   // Your hotspot password

WebSocketsServer webSocket = WebSocketsServer(81);
const int buttonPin = 7;
const int ledPin = 3;
int lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  while (!Serial);        // Wait for Serial Monitor to be ready
  delay(1000);            // Give time to open

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent([](uint8_t num, WStype_t type, uint8_t *payload, size_t length) {});
}

void loop() {
  webSocket.loop();

  int state = digitalRead(buttonPin);
  if (state == LOW && lastState == HIGH) {
    digitalWrite(ledPin, HIGH);
    webSocket.broadcastTXT("The button is being pressed");
    Serial.println("The button is being pressed");  // Also show in Serial Monitor
    delay(300);
    digitalWrite(ledPin, LOW);
  }

  lastState = state;
}
