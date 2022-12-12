from main import socketio
from flask_socketio import emit
from flask_login import current_user
from WEB import models
from WEB import db
from lxml.html.clean import clean_html
from flask import render_template

@socketio.on('new_message')
def new_message(content):
    message = models.Message(author=current_user._get_current_object(),content=clean_html(content))
    db.session.add(message)
    db.session.commit()
    emit('new_message',{'message_html':render_template('message.html',message=message)},broadcast=True)
