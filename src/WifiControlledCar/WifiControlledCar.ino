#include <WiFi.h>

int enA = 22;
int enB = 23;
int In1 = 5;
int In2 = 18;
int In3 = 19;
int In4 = 21;
int speed = 255;

const char* ssid = "<YourWiFiSSID>";
const char* password = "<YourWiFiPassword>";
//const char* serverIP = "url of your website";  // Server IP address
const int serverPort = 5001;  // Server port

WiFiServer server(serverPort);
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);

  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Local IP Address: ");
  Serial.println(WiFi.localIP());
  // Start the server
  server.begin();
  Serial.printf("Server listening on port %d\n", serverPort);
}
void loop() {
  // Check for an incoming client
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {

      if (client.available()) {
        client.write("ESP32 has Connected!");
        uint8_t buffer[256];
        int len = client.read(buffer, sizeof(buffer) - 1);  // Read data, leave space for null terminator

        if (len > 0) {

          buffer[len] = '\0';  // Null-terminate the string
          Serial.print("Received: ");
          Serial.println((char*)buffer);

          int command = -1;

          if (strcmp((char*)buffer, "up") == 0) {
            command = 1;
          } else if (strcmp((char*)buffer, "down") == 0) {
            command = 2;
          } else if (strcmp((char*)buffer, "left") == 0) {
            command = 3;
          } else if (strcmp((char*)buffer, "right") == 0) {
            command = 4;
          } else if (strcmp((char*)buffer, "stop") == 0) {
            command = 0;
          } else {
            command = 0;  // Default to stop if command is unrecognized
          }

          switch (command) {
            case 1:
              controlCar(1);
              break;
            case 2:
              controlCar(2);
              break;
            case 3:
              controlCar(3);
              break;
            case 4:
              controlCar(4);
              break;
            case 0:
            default:
              controlCar(0);
              break;
          }
          client.write("Data Recieved by SmartCar!");
        } else {
          client.write("Error in recieving data");
        }
      }
    }
  }
}




void controlCar(int value) {
  switch (value) {
    case (1):
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
    case (2):
      digitalWrite(In1, LOW);
      digitalWrite(In2, HIGH);
      digitalWrite(In3, LOW);
      digitalWrite(In4, HIGH);
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
    case (3):
      digitalWrite(In1, HIGH);
      digitalWrite(In2, LOW);
      digitalWrite(In3, LOW);
      digitalWrite(In4, HIGH);
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
    case (4):
      digitalWrite(In1, LOW);
      digitalWrite(In2, HIGH);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
    case (0):
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      digitalWrite(In3, LOW);
      digitalWrite(In4, LOW);
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
    default:
      digitalWrite(In1, LOW);
      digitalWrite(In2, LOW);
      digitalWrite(In3, LOW);
      digitalWrite(In4, LOW);
      analogWrite(enA, speed);
      analogWrite(enB, speed);
      break;
  }
}