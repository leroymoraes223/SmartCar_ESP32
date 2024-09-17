import eventlet
eventlet.monkey_patch()
from app import create_app, db, socketio

app = create_app()
    
def init_db():
    with app.app_context():
        db.create_all()  # Create database tables

if __name__ == '__main__': 
    init_db()
    print("Server is running")
    socketio.run(app, host='0.0.0.0', port=5000, debug=False) # Flask server will run on localhost and on the local ip address of your device for LAN hosting