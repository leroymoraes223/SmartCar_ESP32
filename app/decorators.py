from functools import wraps
from flask import redirect, url_for, session

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'user_id' not in session:
            print("User not logged in, redirecting to login.")  # Debugging
            return redirect(url_for('main_routes.login'))
        print(f"User logged in. User ID: {session['user_id']}")  # Debugging
        return f(*args, **kwargs)
    return decorated_function
