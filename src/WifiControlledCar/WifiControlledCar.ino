#include <Arduino.h> 
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
#include <SPIFFS.h>

int enA = 22;
int enB = 23;
int In1 = 5;
int In2 = 18;
int In3 = 19;
int In4 = 21;

String recvKey;
String recvValue;
int value;
int speed;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

const char* ssid     = "WiFi_Car";
const char* password = "123456789";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket disconnected");
  } else if (type == WS_EVT_DATA) {
    data[len] = '\0';
    String recvData = String((char*)data);
    Serial.println("Received data: ");

    int commaIndex = recvData.indexOf(',');
    if (commaIndex != -1){
      recvKey = recvData.substring(0, commaIndex);
      recvValue = recvData.substring(commaIndex + 1);
      value = recvValue.toInt();
      if (recvKey == "Speed"){
        speed = value;
      }
    }
    Serial.print("Key: ");
    Serial.println(recvKey);
    Serial.print("Value: ");
    Serial.println(value);
    Serial.print("Speed: ");
    Serial.println(speed);
  }
};

void setup()
{
Serial.begin(115200);
if (!WiFi.softAP(ssid, password)) 
{
  Serial.println("Soft AP creation failed.");
  while (true);
}

if (!SPIFFS.begin(true)) {
  Serial.println("An error has occurred while mounting SPIFFS");
  return;
}
Serial.println("SPIFFS mounted successfully");

IPAddress myIP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(myIP);

ws.onEvent(onWebSocketEvent); // Set up WebSocket event handler
server.addHandler(&ws);

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
});

server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(204);
});


server.begin();
Serial.println("HTTP server started");
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(In1, OUTPUT);
pinMode(In2, OUTPUT);
pinMode(In3, OUTPUT);
pinMode(In4, OUTPUT);

}

void loop()
{
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  while (value != 0){
    if (recvKey=="MoveCar"){
      switch (value){
        case 1:
          digitalWrite(In1, HIGH);
          digitalWrite(In2, LOW);

          digitalWrite(In3, HIGH);
          digitalWrite(In4, LOW);

        case 2:
          digitalWrite(In1, LOW);
          digitalWrite(In2, HIGH);

          digitalWrite(In3, LOW);
          digitalWrite(In4, HIGH);

        case 3: 
          digitalWrite(In1, HIGH);
          digitalWrite(In2, LOW);

          digitalWrite(In3, LOW);
          digitalWrite(In4, HIGH);
        
        case 4:
          digitalWrite(In1, LOW);
          digitalWrite(In2, HIGH);

          digitalWrite(In3, HIGH);
          digitalWrite(In4, LOW);
      }
    }
  }
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);

  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}