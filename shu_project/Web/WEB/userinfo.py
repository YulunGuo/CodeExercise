from flask import Blueprint,render_template,request,flash,redirect,url_for,abort
from flask_login import login_required,current_user
from WEB import models,db
from utils import forms

userinfo = Blueprint('userinfo',__name__)

# 用户资料
@userinfo.route('/userinfo/<username>',methods=['POST','GET'],endpoint='userinfo')
@login_required
def User_Info(username):
    user = models.User.query.filter_by(username=username).first_or_404()
    if request.method == 'GET':
        return render_template('userinfo.html',user=user)

# 编辑个人资料
@userinfo.route('/editinfo/<username>',methods=['GET','POST'],endpoint='editinfo')
@login_required
def Edit_User_Info(username):
    if request.method == 'GET':
        return render_template('editinfo.html')
    elif request.method == 'POST':
        # 传入表单数据
        form = forms.EditProfileForm(formdata=request.form)
        if form.validate():
            current_user.name = form.data['name']
            current_user.location = form.data['location']
            current_user.about_me = form.data['about_me']
            db.session.commit()
            flash('Your profile has been updated.')
            return redirect(url_for('userinfo.userinfo', username=current_user.username))
        else:
            for error in form.errors:
                flash(form.errors[error][0])
            return render_template('editinfo.html')

# 网站简介
@userinfo.route('/webinfo',methods=['GET','POST'],endpoint='webinfo')
@login_required
def Web_Info():
    return render_template('webinfo.html')