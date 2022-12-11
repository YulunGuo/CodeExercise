from flask import Blueprint,request,render_template
from flask_login import login_required
from WEB import models
from WEB import db

chatroom = Blueprint('chatroom',__name__)


@chatroom.route('/chat',methods=['POST','GET'],endpoint='chat')
@login_required
def chat():
    if request.method == 'GET':
        print("--------------------------------------------")
        message_list = db.session.query(models.Message).order_by(models.Message.id).all()
        message_list.reverse()
        message_list = message_list[:9]
        message_list.reverse()
        return render_template('chat.html',message_list=message_list)

