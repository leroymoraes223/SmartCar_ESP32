from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired, Email, EqualTo, Length
from wtforms import ValidationError
from app.models import User
import re

class LoginForm(FlaskForm):
    email = StringField('Email',
        validators=[DataRequired(), Email(message='Invalid email address')])
    password = PasswordField('Password',
        validators=[DataRequired()])
    submit = SubmitField('Login')

    def validate_email(self, email):
        user = User.query.filter_by(email=email.data).first()
        if not user:
            raise ValidationError('No account found with this email.')

class SignupForm(FlaskForm):
    email = StringField('Email',
        validators=[DataRequired(), Email(message='Invalid email address')])
    password = PasswordField('Password',
        validators=[DataRequired(), Length(min=6, message='Password must be at least 6 characters long')])
    confirm_password = PasswordField('Confirm Password',
        validators=[DataRequired(), EqualTo('password', message='Passwords must match')])
    submit = SubmitField('Sign Up')

    def validate_email(self, email):
        user = User.query.filter_by(email=email.data).first()
        if user:
            raise ValidationError('This email is already registered. Please choose a different one.')

    def validate_password(self, password):
        if ' ' in password.data:
            raise ValidationError('Password cannot contain spaces.')
        if not re.search(r'[!@#$%^&*(),.?":{}|<>]', password.data):
            raise ValidationError('Password must contain at least one special character.')
