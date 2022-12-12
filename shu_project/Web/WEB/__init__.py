from flask import Flask,redirect,url_for
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager

db = SQLAlchemy()

login_manager = LoginManager()


from WEB.auth import auth
from WEB.chatroom import chatroom
from WEB.main_page import main_page
from WEB.userinfo import userinfo
# from WEB import models
from WEB.models import User
from flask_wtf.csrf import CSRFProtect



def creat_app():
    app = Flask(__name__)
    app.debug = True
    app.register_blueprint(auth)
    app.register_blueprint(chatroom)
    app.register_blueprint(main_page)
    # 个人资料页
    app.register_blueprint(userinfo)
    # 添加配置
    app.config.from_object('WEB.settings.DebugConfig')
    # 读取配置
    db.init_app(app=app)
    # 为app添加login管理
    login_manager.init_app(app=app)
    # 为app添加保护
    CSRFProtect(app=app)
    return app

# 辅助对象存储到session
@login_manager.user_loader
def load_user(user_id):
    # 当浏览器第一次访问服务器时，服务器创建一个session对象(该对象有一个唯一的id,一般称之为sessionId),服务器会将sessionId以cookie的方式发送给浏览器。
    return db.session.query(User).filter(User.id==user_id).first()

# 自定义login_request拦截后函数
@login_manager.unauthorized_handler
def unauthorized():
    return redirect(url_for('auth.login'))


