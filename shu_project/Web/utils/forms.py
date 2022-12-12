from wtforms import Form
from wtforms.fields import simple,EmailField
from wtforms import validators
from wtforms import widgets

class LoginForm(Form):
    username = simple.StringField(
        validators=[
            validators.DataRequired(message='用户名不能为空.')
        ],
        widget=widgets.TextInput(),

    )
    password = simple.PasswordField(
        validators=[
            validators.DataRequired(message='密码不能为空.'),
            validators.Length(min=8, message='密码长度必须大于%(min)d'),

        ],
        widget=widgets.PasswordInput(),
    )

class RegisterForm(Form):
    username = simple.StringField(
        validators=[
            validators.DataRequired(message='用户名不能为空.')
        ],
        widget=widgets.TextInput(),

    )
    password = simple.PasswordField(
        validators=[
            validators.DataRequired(message='密码不能为空.'),
            validators.Length(min=8, message='密码长度必须大于%(min)d'),
        ],
        widget=widgets.PasswordInput(),
    )
    email = EmailField(
        label='邮箱',
        validators=[
            validators.DataRequired(message='邮箱不能为空.'),
            validators.Email(message='邮箱格式错误')
        ],
        widget=widgets.TextInput(input_type='email'),
    )

class EditProfileForm(Form):
	name = simple.StringField('Real name', validators=[validators.Length(0, 64)])
	location = simple.StringField('Location', validators=[validators.Length(0, 64)])
	about_me = simple.TextAreaField('About me')
	submit = simple.SubmitField('Submit')