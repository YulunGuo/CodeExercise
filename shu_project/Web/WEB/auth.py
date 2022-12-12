from flask import Blueprint,redirect,url_for,flash
from flask import render_template
from flask import request
from WEB import models
from WEB import db

import hashlib
from utils import forms

from flask_login import login_user,login_required,logout_user

auth = Blueprint('auth', __name__)

# 登录
@auth.route('/login', methods=['GET', "POST"],endpoint='login')
def login():
    if request.method == 'GET':
        return render_template('login.html')
    elif request.method == 'POST':
        # 传入表单数据
        form = forms.LoginForm(formdata=request.form)
        if form.validate():
            password_hash = hashlib.md5(form.data['password'].encode('utf-8')).hexdigest()
            user_obj = db.session.query(models.User).filter(db.and_(models.User.username == form.data['username'],models.User.password_hash == password_hash)).first()
            if user_obj:
                # 进入聊天室
                print("进入聊天室")
                login_user(user_obj)
                return redirect(url_for('chatroom.chat'))
            else:
                flash('用户名或密码错误')
                # 重定向登录界面
                return redirect(url_for('auth.login'))
        else:
            for error in form.errors:
                flash(form.errors[error][0])
            return redirect(url_for('auth.login'))

# 注册
@auth.route('/register', methods=['GET', "POST"],endpoint='register')
def register():
    if request.method == 'GET':
        return render_template('register.html')
    elif request.method == 'POST':
        # 传入表单数据
        form = forms.RegisterForm(formdata=request.form)
        if form.validate():
            count = db.session.query(models.User).filter(db.or_(models.User.username == form.data['username'],models.User.email == form.data['email'])).count()
            if count:
                flash('用户名或邮箱已存在')
                return redirect(url_for('auth.register'))
            else:
                password_hash = hashlib.md5(form.data['password'].encode('utf-8')).hexdigest()
                db.session.add(models.User(username=form.data['username'],email=form.data['email'],password_hash=password_hash))
                db.session.commit()
                db.session.close()
                flash('注册成功')
                return redirect(url_for('auth.login'))
        else:
            for error in form.errors:
                flash(form.errors[error][0])
            return redirect(url_for('auth.register'))



# 登出
@login_required
@auth.route('/logout',methods=['GET','POST'],endpoint='logout')
def logout():
    logout_user()
    return redirect(url_for('auth.login'))