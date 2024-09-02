from flask import Flask
from flask_mail import Mail
from flask_bcrypt import Bcrypt
from config import Config

bcrypt = Bcrypt()
mail = Mail()

def create_app():
    app = Flask(__name__)
    app.config.from_object(Config)

    bcrypt.init_app(app)
    mail.init_app(app)

    from .routes import main_routes
    app.register_blueprint(main_routes)
    return app
    
