from flask_socketio import SocketIO, emit
import socket, time, threading

# Initial setup of the socket
s = None

def connect_to_esp():
    global s
    while True:
        try:
            # Create a new socket instance
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect(('192.168.50.178', 5001))  # ESP32 IP and port
            print("Connection successfully established with SmartCar...")
            return
        except Exception as e:
            print(f"Connection failed: {str(e)}. Retrying in 5 seconds...")
            time.sleep(5)  # Wait before retrying

def ensure_connection():
    global s
    while True:
        try:
            # Check if the socket is closed
            s.sendall(b'ping')  # Sending a simple ping message
        except Exception:
            print("Connection lost. Reconnecting...")
            connect_to_esp()  # Re-establish the connection
        time.sleep(10)  # Check the connection every 10 seconds

# Start the connection thread
connection_thread = threading.Thread(target=ensure_connection)
connection_thread.daemon = True  # Daemonize the thread so it exits with the main program
connection_thread.start()

def send_Data(data):
    try:
        s.sendall(data.encode('utf-8'))  # Send data
        response = s.recv(1024).decode('utf-8')  # Receive response
        print("Data Sent!")
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
