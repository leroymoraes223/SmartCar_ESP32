# Smart Car Control System

This project is a Smart Car Control System using an **ESP32** microcontroller. The smart car is controlled through WiFi using both a **Flask** web server and WebSockets for real-time communication between a web interface and the car. The project allows the user to control the car's movements, including forward, backward, left, right, and stop commands, using direction buttons on the web page.

## Project Overview

The project consists of two major components:

- **ESP32 microcontroller** acting as the server that controls the smart car.
- **Flask web server** and client to send control commands and interact with the car in real-time through WebSocket connections.

### Key Features

- **Control Car Movement:** The web interface allows the user to control the smart car by sending directional commands (up, down, left, right, stop).
- **Two-way Communication:** The system uses WebSockets to maintain real-time bidirectional communication between the car and the web client.
- **Car Status and Response:** The ESP32 sends status updates back to the Flask server, which are then displayed on the web client for real-time feedback.

## Technology Stack

- **Hardware:**
  - ESP32 Microcontroller (acting as a server for handling movement commands)
  
- **Software:**
  - Python (Flask, Flask-SocketIO)
  - JavaScript (WebSocket communication)
  - C++/Arduino for programming the ESP32
  - HTML/CSS for the web interface

## Setup Instructions

### Prerequisites

- ESP32 microcontroller with WiFi capabilities.
- Python 3.x installed on your machine.
- Arduino IDE installed for ESP32 programming.
- Flask and necessary Python libraries installed. Run the following command:

  ```cmd
  pip install -r requirements.txt
