#include <Arduino.h> 
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

int enA = 22;
int enB = 23;
int In1 = 5;
int In2 = 18;
int In3 = 19;
int In4 = 21;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

const char* ssid     = "WiFi_Car";
const char* password = "123456789";

AsyncWebServer server(80);

const char* htmlContent PROGMEM = R"rawliteral(
  <!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
      .arrows { font-size:40px; color:blue; }
      td.button { background-color:lightgray; border-radius:25%; box-shadow: 5px 5px #aaaaaa; }
      td.button:active { transform: translate(5px,5px); box-shadow: none; }
      .noselect { user-select: none; }
      .slidecontainer { width: 100%; }
      .slider { width: 100%; height: 20px; border-radius: 5px; background: #d3d3d3; outline: none; opacity: 0.7; transition: opacity .2s; }
      .slider:hover { opacity: 1; }
      .slider::-webkit-slider-thumb { width: 40px; height: 40px; border-radius: 50%; background: red; cursor: pointer; }
      .slider::-moz-range-thumb { width: 40px; height: 40px; border-radius: 50%; background: red; cursor: pointer; }
    </style>
  </head>
  <body class="noselect" align="center" style="background-color:white">
    <h2 style="color: teal;text-align:center;">WiFi Robot Control</h2>
    <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" cellspacing=10>
      <tr>
        <td></td>
        <td class="button" ontouchstart='sendButtonInput("MoveCar","1")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">⇧</span></td>
        <td></td>
      </tr>
      <tr>
        <td class="button" ontouchstart='sendButtonInput("MoveCar","3")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">⇦</span></td>
        <td class="button-hidden"></td>    
        <td class="button" ontouchstart='sendButtonInput("MoveCar","4")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">⇨</span></td>
      </tr>
      <tr>
        <td></td>
        <td class="button" ontouchstart='sendButtonInput("MoveCar","2")' ontouchend='sendButtonInput("MoveCar","0")'><span class="arrows">⇩</span></td>
        <td></td>
      </tr>
      <tr>
        <td style="text-align:left;font-size:25px"><b>Speed:</b></td>
        <td colspan=2>
          <div class="slidecontainer">
            <input type="range" min="0" max="255" value="150" class="slider" id="Speed" oninput='sendButtonInput("Speed",value)'>
          </div>
        </td>
      </tr>       
    </table>
    <script>
      var webSocketCarInputUrl = "ws://" + window.location.hostname + "/CarInput"; 
      console.log(window.location.hostname);
      var websocketCarInput;
      
      function initCarInputWebSocket() {
        websocketCarInput = new WebSocket(webSocketCarInputUrl);
        websocketCarInput.onopen = function(event) {
          var speedButton = document.getElementById("Speed");
          sendButtonInput("Speed", speedButton.value);
        };
        websocketCarInput.onclose = function(event) {
          setTimeout(initCarInputWebSocket, 2000);
        };
        websocketCarInput.onmessage = function(event) {};
      }
      
      function sendButtonInput(key, value) {
        var data = key + "," + value;
        websocketCarInput.send(data);
      }
    
      window.onload = initCarInputWebSocket;
      document.getElementById("mainTable").addEventListener("touchend", function(event) {
        event.preventDefault()
      });
    </script>
  </body>    
</html>
  )rawliteral";

void handleRoot(AsyncWebServerRequest *request){
  Serial.println("Received request for root");
  request->send_P(200, "text/html", htmlContent);
}


void setup()
{
Serial.begin(115200);
WiFi.softAP(ssid, password);

IPAddress IP = WiFi.softAPIP();
//Serial.println("AP IP Address: " + IP);

//WiFi.begin(ssid, password);

if(WiFi.status() != WL_CONNECTED){
  Serial.println("Connecting to WiFi......");
}
Serial.println("Connected to WiFi");

server.on("/", HTTP_GET, handleRoot);

server.begin();
Serial.println("HTTP server is started");

pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(In1, OUTPUT);
pinMode(In2, OUTPUT);
pinMode(In3, OUTPUT);
pinMode(In4, OUTPUT);

}

void loop()
{

}