const socket = io('http://192.168.50.151:5000');  // Adjust the port as needed, IP address of the server

function sendButtonInput(directionValue) {
    console.log('Sending Direction: ' + directionValue);
    socket.emit("direction", directionValue);
}

socket.on('response', function(message) {
    console.log('Received response from server: ' + message);
});

socket.on('connect', function() {
    console.log('WebSocket connection established');
});

socket.on('disconnect', function() {
    console.log('WebSocket connection closed');
});

socket.on('error', function(error) {
    console.error('WebSocket error:', error);
});
