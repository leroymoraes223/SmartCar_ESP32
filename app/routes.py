from flask import Blueprint, render_template, request, redirect, url_for, flash
from app import bcrypt, mail
from .forms import LoginForm, SignupForm
from flask_mail import Message

main_routes = Blueprint('main_routes', __name__)

# Simulated database (replace with actual database model)
users_db = {}

@main_routes.route('/')
def index():
    return render_template('index.html')

# Route for the login page
@main_routes.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        email = form.email.data
        password = form.password.data
        user = users_db.get(email)
        if user and bcrypt.check_password_hash(user['password'], password):
            flash('Login successful!', 'success')
            return redirect(url_for('main_routes.index'))  # Use main_routes.index instead of index
        else:
            flash('Login failed. Check your email and/or password.', 'danger')
    return render_template('login.html', form=form)

# Route for the signup page
@main_routes.route('/signup', methods=['GET', 'POST'])
def signup():
    form = SignupForm()
    if form.validate_on_submit():
        email = form.email.data
        password = form.password.data
        if email in users_db:
            flash('Email already registered. Please log in.', 'warning')
            return redirect(url_for('main_routes.login'))  # Use main_routes.login instead of login
        hashed_password = bcrypt.generate_password_hash(password).decode('utf-8')
        users_db[email] = {'password': hashed_password}
        msg = Message('Welcome to Smart Car Control System', sender='leroysemailfortesting@email.com', recipients=[email])
        msg.body = 'Thank you for signing up!'
        mail.send(msg)
        flash('Account created successfully! You can now log in.', 'success')
        return redirect(url_for('main_routes.login'))  # Use main_routes.login instead of login
    return render_template('signup.html', form=form)

@main_routes.route('/control')
def control():
    return render_template('control.html')