from flask_socketio import SocketIO, emit
import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print(s.connect(('192.168.29.117', 5001)))  # ESP32 IP and port
print("Connection initiated with SmartCar...")


def send_Data(data):
    try:
        s.sendall(data.encode('utf-8'))  # Send data
        print("Data Sent!")
        response = s.recv(1024).decode('utf-8')  # Receive response
        return response
    except Exception as e:
        print(f"Error: {str(e)}")
        return f"Error: {str(e)}"

socketio = SocketIO()

@socketio.on('connect')
def handle_connect():
    print('WebSocket connected')

@socketio.on('disconnect')
def handle_disconnect():
    print('WebSocket disconnected')

@socketio.on('direction')
def handle_direction(data):
    print(f'Received direction from website: {data}')
    response = send_Data(data)
    print(f"Server response: {response}")
    emit('response', response)

@socketio.on('Ping')
def handle_ping(ping):
    print("Sending Ping to maintain connection")
    response = send_Data(ping)
    print(f'Server response: {response}')
    emit('response', response)
