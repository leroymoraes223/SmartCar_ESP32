var websocketCarInput;
var webSocketCarInputUrl = "ws://192.168.4.1:80/ws";

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
  console.log("Sending: " + data);
  if (websocketCarInput && websocketCarInput.readyState === WebSocket.OPEN) {
    websocketCarInput.send(data);
  } else {
    console.error("WebSocket is not open. ReadyState: " + websocketCarInput.readyState);
  }
}

function speedValueDisplay(value){
  document.getElementById("speedVal").innerText = Math.round((value/255)*100);
}

window.onload = function (){
initCarInputWebSocket();
};
