#Simply run using "py testconnectivity.py" in terminal to check connection with the esp32

import socket

def test_connection(data):
    while data:
        try:
        # Connect to the ESP32 server
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect(('192.168.29.117', 5001))  # ESP32 IP and port                
                print("Connected to ESP32")
                s.sendall(data.encode('utf-8'))  # Send data
                response = s.recv(1024).decode('utf-8')  # Receive response
                print( response)
        except Exception as e:
            print (f"Error: {str(e)}")

data =str(input("Enter Command: "))

test_connection(data)
