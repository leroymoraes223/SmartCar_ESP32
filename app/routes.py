from flask import Blueprint, render_template, redirect, url_for, flash, session
from app import bcrypt, db
from app.models import User
from app.forms import LoginForm, SignupForm
from app.decorators import login_required
from .sockets import connect_to_esp

main_routes = Blueprint('main_routes', __name__)

@main_routes.route('/')
def index():
    return render_template('index.html')

@main_routes.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        email = form.email.data
        password = form.password.data
        user = User.query.filter_by(email=email).first()
        if user and user.check_password(password):
            session['user_id'] = user.id  # Set user ID in session
            flash('Login successful', 'success')
            return redirect(url_for('main_routes.index'))  # Redirect to a protected page
        else:
            flash('Invalid email or password', 'danger')
    return render_template('login.html', form=form)

@main_routes.route('/signup', methods=['GET', 'POST'])
def signup():
    form = SignupForm()
    if form.validate_on_submit():
        email = form.email.data
        password = form.password.data
        confirm_password = form.confirm_password.data
        
        if password != confirm_password:
            flash('Passwords do not match', 'danger')
            return redirect(url_for('main_routes.signup'))

        # Check if email already exists
        existing_user = User.query.filter_by(email=email).first()
        if existing_user:
            flash('Email already exists', 'danger')
            return redirect(url_for('main_routes.signup'))

        hashed_password = bcrypt.generate_password_hash(password).decode('utf-8')
        user = User(email=email, password=hashed_password)
        db.session.add(user)
        db.session.commit()
        flash('Account created successfully', 'success')
        return redirect(url_for('main_routes.login'))
    
    return render_template('signup.html', form=form)

@main_routes.route('/control', methods=['GET'])
@login_required
def control():
    connect_to_esp()
    return render_template('control.html')


@main_routes.route('/logout')
def logout():
    session.pop('user_id', None)
    flash('you have been logged out.', 'info')
    return redirect(url_for('main_routes.login'))

@main_routes.route('/dashboard')
@login_required
def dashboard():
    user = User.query.get(session['user_id'])
    return render_template('dashboard.html', user=user)